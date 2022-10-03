#include <boost/log/attributes/named_scope.hpp>
#include <iostream>

#include <boost/log/trivial.hpp>

#include <fan/FanCurve.h>

using namespace std;

FanCurve::FanCurve(std::vector<FanStep> steps,
                   std::vector<std::shared_ptr<Sensor>> sensors,
                   std::vector<std::shared_ptr<Fan>> fans)
    : mSteps(steps), mTempSensors(sensors), mFans(fans) {
  PrintInfo();
}

void FanCurve::DoFanControl() {
  int temp = AggregateTemperature();

  int t0, t1, p0, p1;
  int targetFanSpeed;

  if (temp <= mSteps[0].Temp) {
    targetFanSpeed = mSteps[0].Percent;
  } else if (temp > mSteps[mSteps.size() - 1].Temp) {
    targetFanSpeed = mSteps[mSteps.size() - 1].Percent;
  } else {
    for (int i = 0; i < mSteps.size(); i++) {
      if (temp > mSteps[i].Temp) {
        t0 = mSteps[i].Temp;
        p0 = mSteps[i].Percent;

        t1 = mSteps[i + 1].Temp;
        p1 = mSteps[i + 1].Percent;
      }
    }

    targetFanSpeed = p0 + ((p1 - p0) / (t1 - t0)) * (temp - t0);
  }

  for (auto f : mFans) {
    f->PWM(targetFanSpeed);
  }
}

// Dummy Implementation using AVG
int FanCurve::AggregateTemperature() {
  int sum = 0;
  for (auto s : mTempSensors) {
    sum += s->value();
  }

  return sum / mTempSensors.size();
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
}
