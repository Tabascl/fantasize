#include <boost/json.hpp>
#include <boost/json/parse.hpp>
#include <sensors/sensors.h>

#include <HwmonTemperatureSensor.h>

using namespace boost::json;

#define SENSOR_TYPE_STRING "HWMON"

int HwmonTemperatureSensor::getTemperature() {
  double *value;
  sensors_get_value(&mChipName, mSubFeature.number, value);

  return static_cast<int>(*value);
}

void tag_invoke(value_from_tag, value &jv, sensors_bus_id &c) {
  jv = {{"type", c.type}, {"nr", c.nr}};
}

void tag_invoke(value_from_tag, value &jv, sensors_chip_name &c) {
  jv = {{"prefix", c.prefix},
        {"sensors_bus_id", value_from(c.bus)},
        {"addr", c.addr},
        {"path", c.path}};
}

std::string HwmonTemperatureSensor::toJson() {
  value jv = {{SENSOR_TYPE_STRING, {"ChipName", value_from(mChipName)}}};

  return serialize(jv);
}
