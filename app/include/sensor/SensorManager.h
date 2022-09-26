#ifndef SENSORMANAGER_H_
#define SENSORMANAGER_H_

#include <memory>
#include <sensor/GPUSensorsFacade.h>
#include <sensor/LMSensorsFacade.h>

class SensorManager {
public:
  SensorManager();

  std::vector<std::shared_ptr<Sensor>> TemperatureSensors();
  std::vector<std::shared_ptr<Sensor>> RPMSensors();

private:
  std::unique_ptr<LMSensorsFacade> mLMSensorsFacade;
  std::unique_ptr<GPUSensorsFacade> mGPUSensorsFacade;
};

#endif // SENSORMANAGER_H_
