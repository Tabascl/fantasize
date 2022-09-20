#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Serializable {
public:
  virtual json toJson() const = 0;
};

#endif // SERIALIZABLE_H_
