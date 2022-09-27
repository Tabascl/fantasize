#include <iostream>

#include <FanGenerator.h>
#include <Serializer.h>
#include <fan/Fan.h>
#include <pwm/PWMControlFacade.h>
#include <sensor/SensorManager.h>

int main() {
  SensorManager sensorManager;
  auto pwmSensors = sensorManager.RPMSensors();

  PWMControlFacade pwmControlFacade;
  auto controls = pwmControlFacade.PWMControls();

  FanGenerator m;
  Serializer s;

  std::vector<std::shared_ptr<Fan>> fans;

  fans = m.FindFans(pwmSensors, controls);

  for (auto f : fans) {
    std::cout << f->toString() << std::endl;
  }

  return 0;
}
