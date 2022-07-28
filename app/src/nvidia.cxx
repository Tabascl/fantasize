#include <include/nvml.h>
#include <nvidia.h>

Nvidia::Nvidia() { nvmlInit_v2(); }
Nvidia::~Nvidia() { nvmlShutdown(); }

double Nvidia::get_gpu_temperature() {
  nvmlDevice_t device;

  nvmlDeviceGetHandleByIndex_v2(0, &device);

  unsigned int temp;
  nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);

  return static_cast<double>(temp);
}
