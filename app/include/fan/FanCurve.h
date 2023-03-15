#ifndef FANCURVE_H_
#define FANCURVE_H_

#include <memory>
#include <vector>

#include <fan/Aggregators.h>
#include <fan/HwmonFan.h>
#include <sensor/Sensor.h>

struct FanStep
{
  int Temp;
  int Percent;
};

class FanCurve
{
public:
  FanCurve(std::vector<FanStep> steps,
           std::vector<std::shared_ptr<Sensor>> sensors,
           std::vector<std::shared_ptr<Fan>> fans,
           std::unique_ptr<Aggregator> aggregator);

  void DoFanControl();

private:
  int AggregateTemperature();
  void PrintInfo();

  std::vector<FanStep> mSteps;
  std::vector<std::shared_ptr<Sensor>> mTempSensors;
  std::vector<std::shared_ptr<Fan>> mFans;
  std::unique_ptr<Aggregator> mAggregator;
};

#endif // FANCURVE_H_
