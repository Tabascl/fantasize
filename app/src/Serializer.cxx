#include <filesystem>
#include <fstream>
#include <iostream>

#include <memory>

#include <Serializer.h>
#include <fan/HwmonFan.h>
#include <fan/PwmControl.h>
#include <sensor/HwmonSensor.h>

using namespace std;
namespace fs = filesystem;

Serializer::Serializer() {
  if (!fs::exists(SERIALIZATION_DIR)) {
    fs::create_directory(SERIALIZATION_DIR);
  }
}

void Serializer::Serialize(vector<shared_ptr<Fan>> fans) {
  json fansArr;

  for (auto f : fans) {
    fansArr.emplace_back(f->toJson());
  }

  json obj;

  obj["fans"] = fansArr;

  cout << "Json obj: " << obj.dump(2) << endl;

  WriteJson(obj);
}

vector<shared_ptr<Fan>>
Serializer::Deserialize(vector<shared_ptr<Sensor>> availableSensors) {
  vector<shared_ptr<Fan>> mapping;

  // Create a for the sensors first, then searching becomes cheaper
  map<string, shared_ptr<Sensor>> sensorMap;
  for (auto s : availableSensors) {
    sensorMap[s->toString()] = s;
  }

  auto data = ReadJson();
  try {
    for (auto &el : data["fans"].items()) {
      auto pwmControl = make_shared<PwmControl>(el.value()["PwmControl"]);
      auto rpmSensor = sensorMap[el.value()["HwmonSensor"]];

      mapping.push_back(make_shared<HwmonFan>(pwmControl, rpmSensor));
    }
  } catch (const std::exception &e) {
    std::cout << "Deserialization error! Message: " << e.what() << std::endl;
  }
  return mapping;
}

void Serializer::WriteJson(json o) {
  ofstream ostrm(fs::path(SERIALIZATION_DIR) / FANS_JSON_FILENAME, ios::trunc);
  ostrm << o.dump(2) << "\n";
}

json Serializer::ReadJson() {
  ifstream istrm(fs::path(SERIALIZATION_DIR) / FANS_JSON_FILENAME);
  return json::parse(istrm);
}
