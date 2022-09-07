#ifndef HWMONTEMPERATURESENSOR_H_
#define HWMONTEMPERATURESENSOR_H_

#include <sensors/sensors.h>

#include <TemperatureSensor.h>

class HwmonTemperatureSensor : public TemperatureSensor {
public:
  int getTemperature() override;
  std::string toJson() override;

private:
  sensors_chip_name mChipName;
  sensors_subfeature mSubFeature;
};

#endif // HWMONTEMPERATURESENSOR_H_
