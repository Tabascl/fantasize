#include <Mapping.h>
#include <Serializer.h>
#include <sensor/NvidiaSensor.h>
#include <sensor/SensorsWrapper.h>

int main() {

  SensorsWrapper sensorsWrapper;

  auto tempSensors = sensorsWrapper.Sensors(SENSORS_SUBFEATURE_TEMP_INPUT);
  tempSensors.push_back(std::make_shared<NvidiaSensor>());

  auto pwmSensors = sensorsWrapper.Sensors(SENSORS_SUBFEATURE_FAN_INPUT);

  auto controls = sensorsWrapper.PwmControls();

  Mapping m;
  auto mapping = m.createMapping(pwmSensors, controls);

  Serializer s;
  s.Serialize(mapping);

  return 0;
}
