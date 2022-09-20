#ifndef NVIDIASENSOR_H_
#define NVIDIASENSOR_H_

#include <sensor/Sensor.h>

class NvidiaSensor : public Sensor {
public:
  NvidiaSensor();
  ~NvidiaSensor();

  int value() override;

  const std::string toString() const override;

  json toJson() const override;
};

#endif // NVIDIASENSOR_H_
