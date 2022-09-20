#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include <fan/Fan.h>

using json = nlohmann::json;

class Serializer {
public:
  Serializer();
  void Serialize(std::vector<std::shared_ptr<Fan>> fans);

private:
  void WriteJson(json o);
};

#endif // SERIALIZER_H_
