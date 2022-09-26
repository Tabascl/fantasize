#include <sensor/GPUSensorsFacade.h>

#include <sensor/NvidiaSensor.h>

using namespace std;

vector<shared_ptr<Sensor>> GPUSensorsFacade::TemperatureSensors() {
  return vector<shared_ptr<Sensor>>{make_shared<NvidiaSensor>()};
}
