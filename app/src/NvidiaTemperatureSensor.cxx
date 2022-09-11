#include <include/nvml.h>

#include <NvidiaTemperatureSensor.h>

using namespace std;

NvidiaTemperatureSensor::NvidiaTemperatureSensor() { nvmlInit_v2(); }
NvidiaTemperatureSensor::~NvidiaTemperatureSensor() { nvmlShutdown(); }

int NvidiaTemperatureSensor::temperature() {
  nvmlDevice_t device;

  nvmlDeviceGetHandleByIndex_v2(0, &device);

  unsigned int temp;
  nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);

  return static_cast<int>(temp);
}

string NvidiaTemperatureSensor::name() { return "GPU"; }
