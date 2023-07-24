#include <boost/log/attributes/named_scope.hpp>
#include <iostream>

#include <boost/log/trivial.hpp>

#include <fan/FanCurve.h>
#include <memory>

using namespace std;

FanCurve::FanCurve(std::vector<FanStep> steps,
                   std::vector<std::shared_ptr<Sensor>> sensors,
                   std::vector<std::shared_ptr<Fan>> fans,
                   std::unique_ptr<Aggregator> aggregator)
    : mSteps(steps), mTempSensors(sensors), mFans(fans),
      mAggregator(std::move(aggregator)) {
  PrintInfo();
}

void FanCurve::DoFanControl() {
  BOOST_LOG_FUNCTION();

  int temp = AggregateTemperature();

  int t0 = 0, t1 = 0, p0 = 0, p1 = 0;
  int targetFanPower;

  if (temp <= mSteps[0].Temp) {
    targetFanPower = mSteps[0].Percent;
  } else if (temp > mSteps[mSteps.size() - 1].Temp) {
    targetFanPower = mSteps[mSteps.size() - 1].Percent;
  } else {
    for (int i = 0; i < (int)mSteps.size(); i++) {
      if (temp > mSteps[i].Temp) {
        t0 = mSteps[i].Temp;
        p0 = mSteps[i].Percent;

        t1 = mSteps[i + 1].Temp;
        p1 = mSteps[i + 1].Percent;
      }
    }

    targetFanPower = p0 + ((p1 - p0) / (t1 - t0)) * (temp - t0);
  }

  for (auto f : mFans) {
    if (!f->ZeroFanModeSupported() && f->RPM() <= 0) {
      BOOST_LOG_TRIVIAL(warning) << "Fan stopped completely!";
      f->PWM(f->StartPWM());
      f->AdjustPWMLimits();
    } else {
      f->PWM(targetFanPower);
    }
  }
}

int FanCurve::AggregateTemperature() {
  return mAggregator->aggregate(mTempSensors);
}

void FanCurve::PrintInfo() {
  BOOST_LOG_FUNCTION()

  BOOST_LOG_TRIVIAL(info) << "### Fan curve:";

  stringstream sStream;
  sStream << "Steps: ";
  for (auto s : mSteps) {
    sStream << "[ " << s.Temp << "C, " << s.Percent << "% ] ";
  }
  BOOST_LOG_TRIVIAL(info) << sStream.str();

  sStream.str(string());

  sStream << "Sensors: ";
  for (auto s : mTempSensors) {
    sStream << s->toString() << ", ";
  }

  BOOST_LOG_TRIVIAL(info) << sStream.str();

  sStream.str(string());

  sStream << "Fans: ";
  for (auto s : mFans) {
    sStream << s->toString() << ", ";
  }

  BOOST_LOG_TRIVIAL(info) << sStream.str();

  sStream.str(string());

  sStream << "Aggregate function: " << mAggregator->toString();

  BOOST_LOG_TRIVIAL(info) << sStream.str();
}
