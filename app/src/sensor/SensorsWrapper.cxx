#include <cstdio>
#include <filesystem>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <type_traits>

#include <sensors/sensors.h>

#include <sensor/SensorsWrapper.h>

#include <sensor/HwmonSensor.h>
#include <sensor/NvidiaSensor.h>

using namespace std;
namespace fs = std::filesystem;

#define CONFIG_FILE "/etc/conf.d/sensors"
#define HWMON_BASE_PATH "/sys/class/hwmon"

SensorsWrapper::SensorsWrapper() : mConfigFile(fopen(CONFIG_FILE, "r")) {
  if (sensors_init(mConfigFile) != 0) {
    throw runtime_error("Config file doesn't exist");
  }
}

SensorsWrapper::~SensorsWrapper() { sensors_cleanup(); }

std::vector<std::shared_ptr<Sensor>>
SensorsWrapper::Sensors(sensors_subfeature_type sensorType) {
  std::vector<std::shared_ptr<Sensor>> sensors;

  int c = 0;
  for (const sensors_chip_name *chipName;
       (chipName = sensors_get_detected_chips(0, &c)) != NULL;) {

    int d = 0;
    for (const sensors_feature *feature;
         (feature = sensors_get_features(chipName, &d)) != NULL;) {
      auto subFeature = sensors_get_subfeature(chipName, feature, sensorType);
      if (subFeature) {
        sensors.push_back(
            std::make_shared<HwmonSensor>(chipName, feature, subFeature));
      }
    }
  }

  return sensors;
}

std::vector<std::shared_ptr<PwmControl>> SensorsWrapper::PwmControls() {
  std::vector<std::shared_ptr<PwmControl>> controls;

  const std::regex re_ctrl_enable("pwm[0-9]_enable");
  const std::regex re_ctrl_mode("pwm[0-9]_mode");
  const std::regex re_ctrl("pwm[0-9]");

  if (!fs::exists(HWMON_BASE_PATH)) {
    std::cout << HWMON_BASE_PATH << " doesn't exist" << std::endl;
  } else {
    for (const fs::directory_entry &hwmon_device :
         fs::directory_iterator{HWMON_BASE_PATH}) {

      for (const fs::directory_entry &control :
           fs::directory_iterator{hwmon_device}) {
        auto filename = control.path().filename().string();

        if (regex_match(filename, re_ctrl)) {
          auto controlPath = control.path().string();

          controls.push_back(std::make_shared<PwmControl>(controlPath));
        }
      }
    }
  }

  return controls;
}
