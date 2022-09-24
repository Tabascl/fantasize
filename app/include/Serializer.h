#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include <fan/Fan.h>
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

  void SerializeTempSensors(std::vector<std::shared_ptr<Sensor>> senors);
  std::vector<std::shared_ptr<Sensor>>
  DeserializeTempSensors(std::vector<std::shared_ptr<Sensor>> availableSensors);

private:
  void WriteJson(json o);
  json ReadJson();
};

#endif // SERIALIZER_H_
