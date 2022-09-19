#ifndef MAPPING_H_
#define MAPPING_H_

#include <memory>
#include <vector>

#include <fan/Fan.h>
#include <fan/PwmControl.h>
#include <sensor/Sensor.h>

class Mapping {
public:
  std::vector<std::shared_ptr<Fan>>
  createMapping(std::vector<std::shared_ptr<Sensor>> rpmSensors,
                std::vector<std::shared_ptr<PwmControl>> pwmControls);

private:
  template <class Printable>
  void print(std::string listLabel,
             std::vector<std::shared_ptr<Printable>> list);
};

#endif // MAPPING_H_
