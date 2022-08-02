#ifndef SENSORSWRAPPER_H_
#define SENSORSWRAPPER_H_

#include <vector>

#include <sensors/sensors.h>

class SensorsWrapper {
public:
  SensorsWrapper();

private:
  std::vector<const sensors_subfeature *> mTemperatureSensors;
  std::vector<const sensors_subfeature *> mFanSensors;
};

#endif // SENSORSWRAPPER_H_
