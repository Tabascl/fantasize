#include <sensor/HwmonSensor.h>
#include <sensors/sensors.h>

using namespace std;

HwmonSensor::HwmonSensor(const sensors_chip_name *chipName,
                         const sensors_feature *feature,
                         const sensors_subfeature *subfeature)
    : mChipName(chipName), mFeature(feature), mSubFeature(subfeature) {}

int HwmonSensor::value() {
  double value;
  sensors_get_value(mChipName, mSubFeature->number, &value);

  return static_cast<int>(value);
}

const string HwmonSensor::toString() const {
  return sensors_get_label(mChipName, mFeature);
}
