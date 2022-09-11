#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#include <sensors/sensors.h>

#include <HwmonTemperatureSensor.h>
#include <NvidiaTemperatureSensor.h>
#include <Pwm.h>

#define CONFIG_FILE "/etc/conf.d/sensors"

std::vector<std::shared_ptr<TemperatureSensor>> sensors() {
  std::vector<std::shared_ptr<TemperatureSensor>> sensors;

  auto config = fopen(CONFIG_FILE, "r");
  if (sensors_init(config) != 0) {
    throw std::runtime_error("Config file doesn't exist");
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
        sensors.push_back(std::make_shared<HwmonTemperatureSensor>(
            chipName, feature, tempFeature));
    }
  }

  sensors.push_back(std::make_shared<NvidiaTemperatureSensor>());

  return sensors;
}

int main() {
  class PWM pwm;
  std::cout << '\n';
  pwm.dumpValues();

  auto controls = pwm.getControls();
  std::cout << pwm.readValue(controls[0], PWM_CONTROL_PROPERTY::ENABLE)
            << std::endl;

  auto tempSensors = sensors();

  for (auto s : tempSensors) {
    std::cout << s->name() << ": " << s->temperature() << std::endl;
  }

  return 0;
}
