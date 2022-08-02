#include <iostream>

#include <sensors/sensors.h>

#include <Nvidia.h>
#include <Pwm.h>

int main() {
  auto config = std::fopen("/etc/conf.d/sensors", "r");
  if (sensors_init(config) != 0) {
    std::cout << "Fuck" << std::endl;
    return 1;
  }

  int c = 0;
  for (const sensors_chip_name *i;
       (i = sensors_get_detected_chips(0, &c)) != NULL;) {
    std::cout << i->prefix << std::endl;

    int d = 0;
    for (const sensors_feature *j; (j = sensors_get_features(i, &d)) != NULL;) {
      const sensors_subfeature *temp_feature =
          sensors_get_subfeature(i, j, SENSORS_SUBFEATURE_TEMP_INPUT);
      if (temp_feature) {
        std::cout << sensors_get_label(i, j);

        double value;
        if (sensors_get_value(i, temp_feature->number, &value) == 0)
          std::cout << ": " << value << " C" << std::endl;
      }

      const sensors_subfeature *fan_feature =
          sensors_get_subfeature(i, j, SENSORS_SUBFEATURE_FAN_INPUT);

      if (fan_feature) {
        std::cout << sensors_get_label(i, j);

        double value;
        if (sensors_get_value(i, fan_feature->number, &value) == 0)
          std::cout << ": " << value << " RPM" << std::endl;
      }
    }

    std::cout << std::endl;
  }

  Nvidia nv;
  auto temp = nv.get_gpu_temperature();
  std::cout << "\nGPU Temp: " << temp << std::endl;

  class PWM pwm;
  std::cout << '\n';
  pwm.dumpValues();

  auto controls = pwm.getControls();
  std::cout << pwm.readValue(controls[0], PWM_CONTROL_PROPERTY::ENABLE)
            << std::endl;

  return 0;
}
