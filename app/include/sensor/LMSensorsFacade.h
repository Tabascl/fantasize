#ifndef LMSENSORSFACADE_H_
#define LMSENSORSFACADE_H_

#include <memory>
#include <vector>

#include <sensors/sensors.h>

#include <sensor/Sensor.h>

class LMSensorsFacade {
public:
  LMSensorsFacade();
  ~LMSensorsFacade();

  std::vector<std::shared_ptr<Sensor>> TemperatureSensors();
  std::vector<std::shared_ptr<Sensor>> RPMSensors();

private:
  template <sensors_subfeature_type T>
  std::vector<std::shared_ptr<Sensor>> Sensors();

private:
  FILE *mConfigFile;
};

#endif // LMSENSORSFACADE_H_
