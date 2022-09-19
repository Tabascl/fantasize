#ifndef SENSORSWRAPPER_H_
#define SENSORSWRAPPER_H_

#include <memory>
#include <vector>

#include <sensors/sensors.h>

#include <fan/PwmControl.h>
#include <sensor/Sensor.h>

class SensorsWrapper {
public:
  SensorsWrapper();
  ~SensorsWrapper();

  std::vector<std::shared_ptr<Sensor>>
  Sensors(sensors_subfeature_type sensorType);

  std::vector<std::shared_ptr<PwmControl>> PwmControls();

private:
  FILE *mConfigFile;
};

#endif // SENSORSWRAPPER_H_
