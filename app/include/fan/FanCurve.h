#ifndef FANCURVE_H_
#define FANCURVE_H_

#include <memory>
#include <vector>

#include <fan/HwmonFan.h>
#include <sensor/Sensor.h>

struct FanStep {
  int Temp;
  int Percent;
};

class FanCurve {
public:
  FanCurve(std::vector<FanStep> steps,
           std::vector<std::shared_ptr<Sensor>> sensors,
           std::vector<std::shared_ptr<Fan>> fans);

  void DoFanControl();

private:
  int AggregateTemperature();
  void PrintInfo();

  std::vector<FanStep> mSteps;
  std::vector<std::shared_ptr<Sensor>> mTempSensors;
  std::vector<std::shared_ptr<Fan>> mFans;
};

#endif // FANCURVE_H_
