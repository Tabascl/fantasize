#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include <Settings.h>
#include <fan/Aggregators.h>
#include <fan/Fan.h>
#include <fan/FanCurve.h>
#include <sensor/Sensor.h>

#define SERIALIZATION_DIR "/etc/fantasize"
#define FANS_JSON_FILENAME "fans.json"

using json = nlohmann::json;

class Serializer
{
public:
  Serializer();
  void SerializeFans(std::vector<std::shared_ptr<Fan>> fans);
  std::vector<std::shared_ptr<Fan>> DeserializeFans(
    std::vector<std::shared_ptr<Sensor>> availableSensors);
  std::vector<std::shared_ptr<FanCurve>> DeserializeFanCurves(
    std::vector<std::shared_ptr<Sensor>> availableSensors,
    std::vector<std::shared_ptr<Fan>> availableFans);
  std::shared_ptr<Settings> DeserializeSettings();

private:
  void WriteJson(json o);
  json ReadJson();
  std::unique_ptr<Aggregator> aggregatorFromString(std::string str) const;
};

#endif // SERIALIZER_H_
