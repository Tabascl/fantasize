#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include "fan/HwmonFan.h"
#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include <fan/Fan.h>
#include <fan/FanCurve.h>
#include <sensor/Sensor.h>

#define SERIALIZATION_DIR "/etc/fantasize"
#define FANS_JSON_FILENAME "fans.json"

using json = nlohmann::json;

class Serializer {
public:
  Serializer();
  void SerializeFans(std::vector<std::shared_ptr<Fan>> fans);
  std::vector<std::shared_ptr<Fan>>
  DeserializeFans(std::vector<std::shared_ptr<Sensor>> availableSensors);
  std::vector<std::shared_ptr<FanCurve>>
  DeserializeFanCurves(std::vector<std::shared_ptr<Sensor>> availableSensors,
                       std::vector<std::shared_ptr<Fan>> availableFans);

private:
  void WriteJson(json o);
  json ReadJson();
};

#endif // SERIALIZER_H_
