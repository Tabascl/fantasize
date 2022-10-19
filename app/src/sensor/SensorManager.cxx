#include <sensor/SensorManager.h>

using namespace std;

SensorManager::SensorManager()
    : mLMSensorsFacade(make_unique<LMSensorsFacade>())
    , mGPUSensorsFacade(make_unique<GPUSensorsFacade>())
{
}

vector<shared_ptr<Sensor>> SensorManager::TemperatureSensors()
{
    vector<shared_ptr<Sensor>> tempSensors;

    tempSensors = mLMSensorsFacade->TemperatureSensors();

#ifdef HAVE_NVML
    auto gpuSensors = mGPUSensorsFacade->TemperatureSensors();
    tempSensors.insert(tempSensors.end(), gpuSensors.begin(), gpuSensors.end());
#endif

    return tempSensors;
}

vector<shared_ptr<Sensor>> SensorManager::RPMSensors()
{
    return mLMSensorsFacade->RPMSensors();
}
