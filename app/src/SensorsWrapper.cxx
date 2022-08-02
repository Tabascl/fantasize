#include <exception>
#include <iostream>
#include <stdexcept>

#include <SensorsWrapper.h>

using namespace std;

#define CONFIG_FILE "/etc/conf.d/sensors"

SensorsWrapper::SensorsWrapper() {
  auto config = fopen(CONFIG_FILE, "r");
  if (sensors_init(config) != 0) {
    throw runtime_error("Config file doesn't exist");
  }

  int c = 0;
  for (const sensors_chip_name *chipName;
       (chipName = sensors_get_detected_chips(0, &c)) != NULL;) {

    int d = 0;
    for (const sensors_feature *feature;
         (feature = sensors_get_features(chipName, &d)) != NULL;) {
      auto tempFeature = sensors_get_subfeature(chipName, feature,
                                                SENSORS_SUBFEATURE_TEMP_INPUT);
      if (tempFeature)
        mTemperatureSensors.push_back(tempFeature);

      auto fanFeature = sensors_get_subfeature(chipName, feature,
                                               SENSORS_SUBFEATURE_FAN_INPUT);
      if (fanFeature)
        mFanSensors.push_back(fanFeature);
    }
  }
}
