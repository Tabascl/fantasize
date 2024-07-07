#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/trivial.hpp>

#include <Serializer.h>
#include <fan/HwmonFan.h>
#include <pwm/PWMControl.h>
#include <sensor/LMSensor.h>
#include <string>

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
  BOOST_LOG_FUNCTION();

  vector<shared_ptr<Fan>> fans;

  // Create a map for the sensors first, then searching becomes cheaper
  map<string, shared_ptr<Sensor>> sensorMap;
  for (auto s : availableSensors) {
    sensorMap[s->toString()] = s;
  }

  auto data = ReadJson();
  try {
    for (auto &el : data["fans"].items()) {
      auto pwmControl = make_shared<PWMControl>(el.value()["PWMControl"]["Path"], el.value()["PWMControl"]["Index"]);
      auto rpmSensor = sensorMap[el.value()["LMSensor"]];

      int minPWM = el.value()["MinPWM"];
      int startPWM = el.value()["StartPWM"];
      string label = el.value()["Label"];
      bool zeroFan = el.value()["ZeroFan"];

      auto fan = make_shared<HwmonFan>(pwmControl, rpmSensor);
      fan->MinPWM(minPWM);
      fan->StartPWM(startPWM);
      fan->Label(label);
      fan->ZeroFanModeSupported(zeroFan);

      fans.push_back(fan);
    }
  } catch (const std::exception &e) {
    std::cout << "Deserialization error! Message: " << e.what() << std::endl;
  }

  BOOST_LOG_TRIVIAL(trace) << "### Available Fans";
  for (auto f : fans) {
    BOOST_LOG_TRIVIAL(trace) << f->toString();
  }

  return fans;
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
    std::vector<std::shared_ptr<Fan>> availableFans, bool &everythingFound) {
  BOOST_LOG_FUNCTION();

  everythingFound = true;
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
      steps.push_back(FanStep{step.value()[0], step.value()[1]});
    }

    for (auto &sensor : el.value()["Sensors"].items()) {
      if (sensorMap.contains(sensor.value()))
        sensors.push_back(sensorMap[sensor.value()]);
      else {
        BOOST_LOG_TRIVIAL(warning)
            << "Sensor " << sensor.value() << " not found!";
        everythingFound = false;
      }
    }

    for (auto &fan : el.value()["Fans"].items()) {
      if (fanMap.contains(fan.value()))
        fans.push_back(fanMap[fan.value()]);
    }

    std::unique_ptr<Aggregator> aggregator =
        aggregatorFromString(el.value()["AggregateFunction"]);

    int hysteresis = el.value()["Hysteresis"];

    curves.push_back(make_shared<FanCurve>(steps, sensors, fans,
                                           std::move(aggregator), hysteresis));
  }

  return curves;
}

std::unique_ptr<Aggregator>
Serializer::aggregatorFromString(std::string str) const {
  if (str == "max")
    return std::make_unique<MaxAggregator>();
  else
    return std::make_unique<AverageAggregator>();
}

shared_ptr<Settings> Serializer::DeserializeSettings() {
  int frequency = FREQUENCY_DEFAULT;

  auto data = ReadJson();

  if (data.contains("settings")) {
    auto items = data["settings"];

    if (items.contains("frequency"))
      frequency = items["frequency"];
  }

  return make_shared<Settings>(frequency);
}
