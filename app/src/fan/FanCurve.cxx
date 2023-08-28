#include <iostream>

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/trivial.hpp>

#include <fan/FanCurve.h>
#include <memory>

using namespace std;

FanCurve::FanCurve(std::vector<FanStep> steps,
                   std::vector<std::shared_ptr<Sensor>> sensors,
                   std::vector<std::shared_ptr<Fan>> fans,
                   std::unique_ptr<Aggregator> aggregator, int hysteresis)
    : mSteps(steps), mTempSensors(sensors), mFans(fans),
      mAggregator(std::move(aggregator)), mHystersis(hysteresis),
      mLastTemperature(INT_MIN) {
  PrintInfo();
}

void FanCurve::DoFanControl() {
  BOOST_LOG_FUNCTION()

  BOOST_LOG_TRIVIAL(trace) << "## Fans in curve";
  for (auto f : mFans)
    BOOST_LOG_TRIVIAL(trace) << f->toString();

  BOOST_LOG_TRIVIAL(trace) << "## Sensors in curve";
  for (auto s : mTempSensors)
    BOOST_LOG_TRIVIAL(trace) << s->toString();

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

  BOOST_LOG_TRIVIAL(trace) << "Current temp: " << temp;
  BOOST_LOG_TRIVIAL(trace) << "Last temp: " << mLastTemperature;

  BOOST_LOG_TRIVIAL(trace) << "# Hysteresis check";
  if (ExceedsHysteresis(temp)) {
    BOOST_LOG_TRIVIAL(trace) << "passed";
    for (auto f : mFans) {
      ApplyFanPower(f, targetFanPower);

      mLastTemperature = temp;
    }
  } else {
    for (auto f : mFans)
      f->EnforceSetValue();

    BOOST_LOG_TRIVIAL(trace) << "not passed";
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

bool FanCurve::ExceedsHysteresis(int temperature) {
  int lowThreshold = mLastTemperature - mHystersis;
  int highThreshold = mLastTemperature + mHystersis;

  return temperature <= lowThreshold || temperature >= highThreshold;
}

void FanCurve::ApplyFanPower(std::shared_ptr<Fan> fan, int targetFanPower) {
  BOOST_LOG_FUNCTION();

  if (!fan->ZeroFanModeSupported() && fan->RPM() <= 0) {
    BOOST_LOG_TRIVIAL(warning) << "Fan stopped completely!";
    fan->PWM(fan->StartPWM());
    fan->AdjustPWMLimits();
  } else {
    fan->PWM(targetFanPower);
  }
}
