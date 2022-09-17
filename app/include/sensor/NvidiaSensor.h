#ifndef NVIDIASENSOR_H_
#define NVIDIASENSOR_H_

#include <sensor/Sensor.h>

class NvidiaSensor : public Sensor {
public:
  NvidiaSensor();
  ~NvidiaSensor();

  int value() override;
  std::string name() override;
};

#endif // NVIDIASENSOR_H_
