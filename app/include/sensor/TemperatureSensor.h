#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_

#include <iostream>

class TemperatureSensor {
public:
  virtual int temperature() = 0;
  virtual std::string name() = 0;
};

#endif // TEMPERATURESENSOR_H_
