#include <filesystem>
#include <iostream>

#include <Mapping.h>
#include <Serializer.h>
#include <fan/Fan.h>
#include <sensor/NvidiaSensor.h>
#include <sensor/SensorsWrapper.h>

namespace fs = std::filesystem;

int main() {

  SensorsWrapper sensorsWrapper;

  auto tempSensors = sensorsWrapper.Sensors(SENSORS_SUBFEATURE_TEMP_INPUT);
  tempSensors.push_back(std::make_shared<NvidiaSensor>());

  auto pwmSensors = sensorsWrapper.Sensors(SENSORS_SUBFEATURE_FAN_INPUT);

  auto controls = sensorsWrapper.PwmControls();

  Mapping m;
  Serializer s;

  std::vector<std::shared_ptr<Fan>> fans;

  if (fs::exists(fs::path(SERIALIZATION_DIR) / FANS_JSON_FILENAME)) {
    fans = s.Deserialize(pwmSensors);
  } else {
    fans = m.createMapping(pwmSensors, controls);
    s.Serialize(fans);
  }

  for (auto f : fans) {
    std::cout << f->toString() << std::endl;
  }

  return 0;
}
