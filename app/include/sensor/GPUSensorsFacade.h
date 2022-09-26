#ifndef GPUSENSORSFACADE_H_
#define GPUSENSORSFACADE_H_

#include <memory>
#include <vector>

#include <sensor/Sensor.h>

class GPUSensorsFacade {
public:
  std::vector<std::shared_ptr<Sensor>> TemperatureSensors();
};

#endif // GPUSENSORSFACADE_H_
