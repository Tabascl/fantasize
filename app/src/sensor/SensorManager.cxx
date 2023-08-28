#include <sensor/SensorManager.h>

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/trivial.hpp>

using namespace std;

SensorManager::SensorManager()
    : mLMSensorsFacade(make_unique<LMSensorsFacade>()),
      mGPUSensorsFacade(make_unique<GPUSensorsFacade>()) {}

vector<shared_ptr<Sensor>> SensorManager::TemperatureSensors() {
  BOOST_LOG_FUNCTION();

  vector<shared_ptr<Sensor>> tempSensors;

  tempSensors = mLMSensorsFacade->TemperatureSensors();

  BOOST_LOG_TRIVIAL(trace) << "### Temperature sensors:";
  for (auto s : tempSensors) {
    BOOST_LOG_TRIVIAL(trace) << s->toString();
  }

  //   auto gpuSensors = mGPUSensorsFacade->TemperatureSensors();
  //  tempSensors.insert(tempSensors.end(), gpuSensors.begin(),
  //  gpuSensors.end());

  return tempSensors;
}

vector<shared_ptr<Sensor>> SensorManager::RPMSensors() {
  return mLMSensorsFacade->RPMSensors();
}

void SensorManager::ReloadSensors() { mLMSensorsFacade->ReloadSensors(); }
