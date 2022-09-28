#include <execution>
#include <iostream>

#include <FanGenerator.h>
#include <Serializer.h>
#include <fan/Fan.h>
#include <memory>
#include <pstl/glue_execution_defs.h>
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

  // fans = m.FindFans(pwmSensors, controls);
  // s.SerializeFans(fans);
  fans = s.DeserializeFans(pwmSensors);

  std::for_each(std::execution::par, std::begin(fans), std::end(fans),
                [](auto &&f) { f->FindMinPWM(); });

  s.SerializeFans(fans);

  return 0;
}
