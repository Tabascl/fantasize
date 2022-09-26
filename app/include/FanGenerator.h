#ifndef MAPPING_H_
#define MAPPING_H_

#include <memory>
#include <vector>

#include <fan/Fan.h>
#include <pwm/PWMControl.h>
#include <sensor/Sensor.h>

class FanGenerator {
public:
  std::vector<std::shared_ptr<Fan>>
  FindFans(std::vector<std::shared_ptr<Sensor>> rpmSensors,
           std::vector<std::shared_ptr<PWMControl>> pwmControls);

private:
  template <class Printable>
  void print(std::string listLabel,
             std::vector<std::shared_ptr<Printable>> list);
};

#endif // MAPPING_H_
