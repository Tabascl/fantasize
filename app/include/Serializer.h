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
  void Serialize(std::vector<std::shared_ptr<Fan>> fans);
  std::vector<std::shared_ptr<Fan>>
  Deserialize(std::vector<std::shared_ptr<Sensor>> availableSensors);

private:
  void WriteJson(json o);
  json ReadJson();
};

#endif // SERIALIZER_H_
