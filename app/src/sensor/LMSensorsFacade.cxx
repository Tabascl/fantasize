#include <stdexcept>

#include <sensors/sensors.h>

#include <sensor/LMSensorsFacade.h>

#include <sensor/LMSensor.h>
#include <sensor/NvidiaSensor.h>

using namespace std;

#define CONFIG_FILE "/etc/conf.d/sensors"

LMSensorsFacade::LMSensorsFacade() : mConfigFile(fopen(CONFIG_FILE, "r")) {
  if (sensors_init(mConfigFile) != 0) {
    throw runtime_error("Config file doesn't exist");
  }
}

LMSensorsFacade::~LMSensorsFacade() { sensors_cleanup(); }

std::vector<std::shared_ptr<Sensor>> LMSensorsFacade::TemperatureSensors() {
  return Sensors<SENSORS_SUBFEATURE_TEMP_INPUT>();
}

std::vector<std::shared_ptr<Sensor>> LMSensorsFacade::RPMSensors() {
  return Sensors<SENSORS_SUBFEATURE_FAN_INPUT>();
}

template <sensors_subfeature_type T>
std::vector<std::shared_ptr<Sensor>> LMSensorsFacade::Sensors() {
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
            std::make_shared<LMSensor>(chipName, feature, subFeature));
      }
    }
  }

  return sensors;
}
