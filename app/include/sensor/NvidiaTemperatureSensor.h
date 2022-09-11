#ifndef NVIDIA_H_
#define NVIDIA_H_

#include <sensor/TemperatureSensor.h>

class NvidiaTemperatureSensor : public TemperatureSensor {
public:
  NvidiaTemperatureSensor();
  ~NvidiaTemperatureSensor();

  int temperature() override;
  std::string name() override;
};

#endif // NVIDIA_H_
