#ifndef HWMONTEMPERATURESENSOR_H_
#define HWMONTEMPERATURESENSOR_H_

#include <TemperatureSensor.h>

class HwmonTemperatureSensor : public TemperatureSensor {
public:
  int getTemperature() override;
};

#endif // HWMONTEMPERATURESENSOR_H_
