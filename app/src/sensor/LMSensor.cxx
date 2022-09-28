#include <boost/json/kind.hpp>
#include <sensor/LMSensor.h>
#include <sensors/sensors.h>

using namespace std;

LMSensor::LMSensor(const sensors_chip_name *chipName,
                   const sensors_feature *feature,
                   const sensors_subfeature *subfeature)
    : mChipName(chipName), mFeature(feature), mSubFeature(subfeature) {}

int LMSensor::value() {
  double value;
  sensors_get_value(mChipName, mSubFeature->number, &value);

  return static_cast<int>(value);
}

const string LMSensor::toString() const {
  return sensors_get_label(mChipName, mFeature);
}

json LMSensor::toJson() const {
  json obj = {"LMSensor", toString()};
  return obj;
}
