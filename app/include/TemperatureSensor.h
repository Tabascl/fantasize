#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_

#include <boost/json.hpp>

#include <iostream>

class TemperatureSensor {
public:
  virtual int getTemperature() = 0;
};

#endif // TEMPERATURESENSOR_H_
