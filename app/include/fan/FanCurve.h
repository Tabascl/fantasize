#ifndef FANCURVE_H_
#define FANCURVE_H_

#include <memory>
#include <vector>

#include <fan/Aggregators.h>
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
           std::vector<std::shared_ptr<Fan>> fans,
           std::unique_ptr<Aggregator> aggregator, int hysteresis);

  void DoFanControl();

private:
  void PrintInfo();
  bool ExceedsHysteresis(int temperature);
  void ApplyFanPower(std::shared_ptr<Fan> fan, int targetFanPower);

  std::vector<FanStep> mSteps;
  std::vector<std::shared_ptr<Sensor>> mTempSensors;
  std::vector<std::shared_ptr<Fan>> mFans;
  std::unique_ptr<Aggregator> mAggregator;
  int mHystersis;
  int mLastTemperature;
};

#endif // FANCURVE_H_
