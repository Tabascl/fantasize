#include <exception>
#include <filesystem>
#include <iostream>
#include <memory>
#include <regex>
#include <vector>

#include <sensors/sensors.h>

#include <fan/PwmControl.h>
#include <sensor/HwmonSensor.h>
#include <sensor/NvidiaSensor.h>

#define CONFIG_FILE "/etc/conf.d/sensors"
#define HWMON_BASE_PATH "/sys/class/hwmon"

namespace fs = std::filesystem;

template <sensors_subfeature_type T>
std::vector<std::shared_ptr<Sensor>> sensors() {
  std::vector<std::shared_ptr<Sensor>> sensors;

  int c = 0;
  for (const sensors_chip_name *chipName;
       (chipName = sensors_get_detected_chips(0, &c)) != NULL;) {

    int d = 0;
    for (const sensors_feature *feature;
         (feature = sensors_get_features(chipName, &d)) != NULL;) {
      auto subFeature = sensors_get_subfeature(chipName, feature, T);
      if (subFeature) {
        sensors.push_back(
            std::make_shared<HwmonSensor>(chipName, feature, subFeature));
      }
    }
  }

  return sensors;
}

std::vector<std::shared_ptr<PwmControl>> pwmControls() {
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

int main() {
  auto config = fopen(CONFIG_FILE, "r");
  if (sensors_init(config) != 0) {
    throw std::runtime_error("Config file doesn't exist");
  }

  auto tempSensors = sensors<SENSORS_SUBFEATURE_TEMP_INPUT>();
  tempSensors.push_back(std::make_shared<NvidiaSensor>());

  for (auto s : tempSensors) {
    std::cout << s->name() << ": " << s->value() << std::endl;
  }

  std::cout << "pwm" << std::endl;

  auto pwmSensors = sensors<SENSORS_SUBFEATURE_FAN_INPUT>();
  for (auto s : pwmSensors) {
    std::cout << s->name() << ": " << s->value() << std::endl;
  }

  return 0;
}
