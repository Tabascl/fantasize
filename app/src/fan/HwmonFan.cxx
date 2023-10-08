#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/trivial.hpp>

#include <fan/HwmonFan.h>
#include <pwm/PWMControl.h>

#define TIMEOUT 10
#define INHIBIT_STOP_PERIOD 120
#define STEP 2

using namespace std;

HwmonFan::HwmonFan(std::shared_ptr<PWMControl> pwmControl,
                   std::shared_ptr<Sensor> rpmSensor)
    : mPWMControl(pwmControl), mRpmSensor(rpmSensor) {
  mPWMControl->EnableManualControl();
}

void HwmonFan::PWM(int percent) {
  if (percent < mMinPWM) {
    if (mZeroFanModeSupported && InhibitStopPeriodExpired()) {
      SetPower(percent);
      mWasStopped = true;
    } else {
      SetPower(mMinPWM);
    }
  } else {
    if (mWasStopped) {
      mWasStopped = false;
      mLastStartTime = chrono::steady_clock::now();
      SetPower(mStartPWM);
    } else {
      SetPower(percent);
    }
  }
}

bool HwmonFan::InhibitStopPeriodExpired() {
  BOOST_LOG_FUNCTION();

  auto result = chrono::steady_clock::now() - mLastStartTime >
                chrono::duration(chrono::seconds(INHIBIT_STOP_PERIOD));

  BOOST_LOG_TRIVIAL(trace) << "Inhibit-Stop period expired:"
                           << (result ? "true" : "false");

  return result;
}

void HwmonFan::SetPower(int percent) {
  mPWMControl->SetPower(percent);
  mSetValue = percent;
}

int HwmonFan::RPM() { return mRpmSensor->value(); }

void HwmonFan::Label(std::string label) { mLabel = label; }

void HwmonFan::MinPWM(int value) { mMinPWM = value; }

int HwmonFan::MinPWM() { return mMinPWM; }

void HwmonFan::StartPWM(int value) { mStartPWM = value; }

int HwmonFan::StartPWM() { return mStartPWM; }

void HwmonFan::ZeroFanModeSupported(bool value) {
  mZeroFanModeSupported = value;
}

bool HwmonFan::ZeroFanModeSupported() { return mZeroFanModeSupported; }

void HwmonFan::FindPWMLimits() {
  cout << "Looking for minimal PWM" << endl;
  int minPWM = 0;
  mMinPWM = 0;
  mStartPWM = 0;

  for (int curPWM = 100; curPWM > 0; curPWM -= STEP) {
    PWM(curPWM);
    this_thread::sleep_for(chrono::seconds(TIMEOUT));

    if (RPM() <= 0) {
      minPWM = curPWM + STEP;
      break;
    }
  }

  cout << "Setting minimal PWM: " << minPWM << endl;
  mMinPWM = minPWM;

  if (minPWM == 0) {
    cout << "Fan never stopped. ";
  } else {
    int startPWM = 0;

    cout << "Looking for start PWM!" << endl;
    for (int curPWM = minPWM - STEP; curPWM < 100; curPWM += STEP) {
      PWM(curPWM);
      this_thread::sleep_for(chrono::seconds(TIMEOUT));

      if (RPM() > 0) {
        cout << "Setting start PWM: " << startPWM << endl;
        startPWM = curPWM;
        break;
      }
    }

    mStartPWM = startPWM;
  }
}

void HwmonFan::AdjustPWMLimits() {
  BOOST_LOG_FUNCTION()

  chrono::time_point now = chrono::steady_clock::now();

  if ((now - mLastAdjustmentTime) >
      chrono::duration(chrono::seconds(TIMEOUT))) {
    BOOST_LOG_TRIVIAL(info) << "Increasing minimal fan speed";

    mLastAdjustmentTime = now;
    mMinPWM += 2;
  }
}

void HwmonFan::EnforceSetValue() { mPWMControl->SetPower(mSetValue); }

json HwmonFan::toJson() const {
  json obj;
  obj = {mPWMControl->toJson(),   mRpmSensor->toJson(),
         {"Label", mLabel},       {"MinPWM", mMinPWM},
         {"StartPWM", mStartPWM}, {"ZeroFan", mZeroFanModeSupported}};
  return obj;
}

const string HwmonFan::toString() const {
  if (!mLabel.empty()) {
    return mLabel;
  } else {
    return mPWMControl->toString();
  }
}
