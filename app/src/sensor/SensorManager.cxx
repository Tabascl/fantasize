#include <sensor/SensorManager.h>

using namespace std;

SensorManager::SensorManager()
    : mLMSensorsFacade(make_unique<LMSensorsFacade>()),
      mGPUSensorsFacade(make_unique<GPUSensorsFacade>()) {}

vector<shared_ptr<Sensor>> SensorManager::TemperatureSensors() {
  vector<shared_ptr<Sensor>> tempSensors;

  tempSensors = mLMSensorsFacade->TemperatureSensors();

  auto gpuSensors = mGPUSensorsFacade->TemperatureSensors();
  tempSensors.insert(tempSensors.end(), gpuSensors.begin(), gpuSensors.end());

  return tempSensors;
}

vector<shared_ptr<Sensor>> SensorManager::RPMSensors() {
  return mLMSensorsFacade->RPMSensors();
}
