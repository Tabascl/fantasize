#ifndef SENSORSWRAPPER_H_
#define SENSORSWRAPPER_H_

#include <string>
#include <vector>

#include <sensors/sensors.h>

struct Sensor {
  sensors_chip_name chipName;
  sensors_feature feature;
  sensors_subfeature subFeature;
};

class SensorsWrapper {
public:
  SensorsWrapper();
  ~SensorsWrapper();

  std::vector<Sensor> getTemperatureSensors();
  int getValue(Sensor sensor);
  std::string getLabel(Sensor sensor);

private:
  std::vector<Sensor> mTemperatureSensors;
  std::vector<Sensor> mFanSensors;
};

#endif // SENSORSWRAPPER_H_
