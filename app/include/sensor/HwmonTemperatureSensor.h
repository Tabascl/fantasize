#ifndef HWMONTEMPERATURESENSOR_H_
#define HWMONTEMPERATURESENSOR_H_

#include <sensors/sensors.h>

#include <sensor/TemperatureSensor.h>

class HwmonTemperatureSensor : public TemperatureSensor {
public:
  HwmonTemperatureSensor(const sensors_chip_name *chipName,
                         const sensors_feature *feature,
                         const sensors_subfeature *subfeature);

  int temperature() override;
  std::string name() override;

private:
  const sensors_chip_name *mChipName;
  const sensors_feature *mFeature;
  const sensors_subfeature *mSubFeature;
};

#endif // HWMONTEMPERATURESENSOR_H_
