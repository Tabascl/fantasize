#include <filesystem>
#include <iostream>

#include <FanGenerator.h>
#include <Serializer.h>
#include <fan/Fan.h>
#include <pwm/PWMControlFacade.h>
#include <sensor/SensorManager.h>

namespace fs = std::filesystem;

int main() {
  SensorManager sensorManager;
  auto pwmSensors = sensorManager.RPMSensors();

  PWMControlFacade pwmControlFacade;
  auto controls = pwmControlFacade.PWMControls();

  FanGenerator m;
  Serializer s;

  std::vector<std::shared_ptr<Fan>> fans;

  if (fs::exists(fs::path(SERIALIZATION_DIR) / FANS_JSON_FILENAME)) {
    fans = s.DeserializeFans(pwmSensors);
  } else {
    fans = m.FindFans(pwmSensors, controls);
    s.SerializeFans(fans);
  }

  for (auto f : fans) {
    std::cout << f->toString() << std::endl;
  }

  return 0;
}
