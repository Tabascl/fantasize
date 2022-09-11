#include <sensors/sensors.h>

#include <HwmonTemperatureSensor.h>

using namespace std;

HwmonTemperatureSensor::HwmonTemperatureSensor(
    const sensors_chip_name *chipName, const sensors_feature *feature,
    const sensors_subfeature *subfeature)
    : mChipName(chipName), mFeature(feature), mSubFeature(subfeature) {}

int HwmonTemperatureSensor::temperature() {
  double *value;
  sensors_get_value(mChipName, mSubFeature->number, value);

  return static_cast<int>(*value);
}

string HwmonTemperatureSensor::name() {
  return sensors_get_label(mChipName, mFeature);
}
