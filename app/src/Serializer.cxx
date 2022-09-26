#include <filesystem>
#include <fstream>
#include <iostream>

#include <memory>

#include <Serializer.h>
#include <fan/HwmonFan.h>
#include <pwm/PWMControl.h>
#include <sensor/LMSensor.h>

using namespace std;
namespace fs = filesystem;

Serializer::Serializer() {
  if (!fs::exists(SERIALIZATION_DIR)) {
    fs::create_directory(SERIALIZATION_DIR);
  }
}

void Serializer::SerializeFans(vector<shared_ptr<Fan>> fans) {
  json obj;

  for (auto f : fans) {
    obj["fans"].push_back(f->toJson());
  }

  WriteJson(obj);
}

vector<shared_ptr<Fan>>
Serializer::DeserializeFans(vector<shared_ptr<Sensor>> availableSensors) {
  vector<shared_ptr<Fan>> mapping;

  // Create a for the sensors first, then searching becomes cheaper
  map<string, shared_ptr<Sensor>> sensorMap;
  for (auto s : availableSensors) {
    sensorMap[s->toString()] = s;
  }

  auto data = ReadJson();
  try {
    for (auto &el : data["fans"].items()) {
      auto pwmControl = make_shared<PWMControl>(el.value()["PWMControl"]);
      auto rpmSensor = sensorMap[el.value()["LMSensor"]];

      mapping.push_back(make_shared<HwmonFan>(pwmControl, rpmSensor));
    }
  } catch (const std::exception &e) {
    std::cout << "Deserialization error! Message: " << e.what() << std::endl;
  }
  return mapping;
}

void Serializer::WriteJson(json o) {
  json obj;

  if (fs::exists(fs::path(SERIALIZATION_DIR) / FANS_JSON_FILENAME)) {
    auto obj = ReadJson();
  }

  for (auto &[key, value] : o.items()) {
    obj[key] = value;
  }

  ofstream ostrm(fs::path(SERIALIZATION_DIR) / FANS_JSON_FILENAME, ios::trunc);
  ostrm << obj.dump(2) << "\n";
}

json Serializer::ReadJson() {
  ifstream istrm(fs::path(SERIALIZATION_DIR) / FANS_JSON_FILENAME);
  return json::parse(istrm);
}

void Serializer::SerializeTempSensors(vector<shared_ptr<Sensor>> sensors) {
  json obj;

  for (auto s : sensors) {
    obj["tempSensors"].push_back(s->toJson());
  }

  WriteJson(obj);
}
vector<shared_ptr<Sensor>>
DeserializeTempSensors(vector<shared_ptr<Sensor>> availableSensors) {
  return vector<shared_ptr<Sensor>>();
}
