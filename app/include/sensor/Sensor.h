#ifndef SENSOR_H_
#define SENSOR_H_

#include <iostream>

class Sensor {
public:
  // Read the current value
  virtual int value() = 0;
  // Name for displaying. Should be descriptive, e.g. "GPU" or the label from
  // libsensors.
  virtual std::string name() = 0;
};

#endif // SENSOR_H_
