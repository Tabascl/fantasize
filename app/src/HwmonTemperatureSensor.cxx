#include <sensors/sensors.h>

#include <HwmonTemperatureSensor.h>

using namespace std;

HwmonTemperatureSensor::HwmonTemperatureSensor(sensors_chip_name chipName,
                                               sensors_subfeature subfeature)
    : mChipName(chipName), mSubFeature(subfeature) {}

int HwmonTemperatureSensor::getTemperature() {
  double *value;
  sensors_get_value(&mChipName, mSubFeature.number, value);

  return static_cast<int>(*value);
}
