#include "fan/FanCurve.h"
#include "sensor/Sensor.h"
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

      int minPWM = el.value()["MinPWM"];
      string label = el.value()["Label"];

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
    obj = ReadJson();
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

vector<shared_ptr<FanCurve>> Serializer::DeserializeFanCurves(
    std::vector<std::shared_ptr<Sensor>> availableSensors,
    std::vector<std::shared_ptr<Fan>> availableFans) {
  auto data = ReadJson();

  map<string, shared_ptr<Sensor>> sensorMap;
  for (auto s : availableSensors) {
    sensorMap[s->toString()] = s;
  }

  map<string, shared_ptr<Fan>> fanMap;
  for (auto f : availableFans) {
    fanMap[f->toString()] = f;
  }

  vector<shared_ptr<FanCurve>> curves;

  for (auto &el : data["fancurves"].items()) {
    vector<FanStep> steps;
    vector<shared_ptr<Sensor>> sensors;
    vector<shared_ptr<Fan>> fans;

    for (auto &step : el.value()["FanSteps"].items()) {
      FanStep fanStep{step.value()[0], step.value()[1]};
    }

    for (auto &sensor : el.value()["Sensors"].items()) {
      sensors.push_back(sensorMap[sensor.value()]);
    }

    for (auto &fan : el.value()["Fans"].items()) {
      fans.push_back(fanMap[fan.value()]);
    }

    curves.push_back(make_shared<FanCurve>(steps, sensors, fans));
  }

  return curves;
}
