#include <fan/FanCurve.h>

#include <array>

using namespace std;

void FanCurve::DoFanControl() {
  int temp = AggregateTemperature();

  int t0, t1, p0, p1;

  if (temp <= mSteps[0].Temp) {
    t0 = t1 = mSteps[0].Temp;
    p0 = p1 = mSteps[0].Percent;
  } else if (temp > mSteps[mSteps.size() - 1].Temp) {
    t0 = t1 = mSteps[mSteps.size() - 1].Temp;
    p0 = p1 = mSteps[mSteps.size() - 1].Percent;
  } else {
    for (int i = 0; i < mSteps.size(); i++) {
      if (temp > mSteps[i].Temp) {
        t0 = mSteps[i].Temp;
        p0 = mSteps[i].Percent;

        t1 = mSteps[i + 1].Temp;
        p1 = mSteps[i + 1].Percent;
      }
    }
  }

  int targetFanSpeed = p0 + ((p1 - p0) / (t1 - t0)) * (temp - t0);

  for (auto f : mFans) {
    f->pwm(targetFanSpeed);
  }
}

// Dummy Implementation using AVG
int FanCurve::AggregateTemperature() {
  int sum;
  for (auto s : mTempSensors) {
    sum += s->value();
  }

  return sum / mTempSensors.size();
}
