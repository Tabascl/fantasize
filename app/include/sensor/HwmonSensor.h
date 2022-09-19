#ifndef HWMONSENSOR_H_
#define HWMONSENSOR_H_

#include <sensors/sensors.h>

#include <sensor/Sensor.h>

class HwmonSensor : public Sensor {
public:
  HwmonSensor(const sensors_chip_name *chipName, const sensors_feature *feature,
              const sensors_subfeature *subfeature);

  int value() override;
  const std::string toString() const override;

private:
  const sensors_chip_name *mChipName;
  const sensors_feature *mFeature;
  const sensors_subfeature *mSubFeature;
};

#endif // HWMONSENSOR_H_
