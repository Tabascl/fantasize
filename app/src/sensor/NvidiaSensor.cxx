#include <boost/json/object.hpp>
#include <include/nvml.h>

#include <sensor/NvidiaSensor.h>

using namespace std;

NvidiaSensor::NvidiaSensor() { nvmlInit_v2(); }
NvidiaSensor::~NvidiaSensor() { nvmlShutdown(); }

int NvidiaSensor::value() {
  nvmlDevice_t device;

  nvmlDeviceGetHandleByIndex_v2(0, &device);

  unsigned int temp;
  nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);

  return static_cast<int>(temp);
}

const std::string NvidiaSensor::toString() const { return "NvidiaGPU"; }

json NvidiaSensor::toJson() const {
  json obj = {"NvidiaSensor", toString()};
  return obj;
}
