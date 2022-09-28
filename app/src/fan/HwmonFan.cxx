#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

#include "pwm/PWMControl.h"
#include <boost/json/object.hpp>
#include <fan/HwmonFan.h>

#define TIMEOUT 5

using namespace std;

HwmonFan::HwmonFan(std::shared_ptr<PWMControl> pwmControl,
                   std::shared_ptr<Sensor> rpmSensor, std::string label,
                   int minPWM, int startPWM)
    : mPWMControl(pwmControl), mRpmSensor(rpmSensor), mLabel(label),
      mMinPWM(minPWM), mStartPWM(startPWM) {
  mPWMControl->EnableManualControl();
}

void HwmonFan::PWM(int percent) { mPWMControl->pwm(percent); }

int HwmonFan::RPM() { return mRpmSensor->value(); }

void HwmonFan::FindMinPWM() {
  int minPWM = 0;

  for (int curPWM = 100; curPWM > 0; curPWM -= 5) {
    PWM(curPWM);
    this_thread::sleep_for(chrono::seconds(TIMEOUT));

    int curRPM = RPM();

    if (curRPM <= 0) {
      minPWM = curPWM + 5;
      break;
    }
  }

  if (minPWM == 0) {
    cout << "Fan never stopped. ";
  }
  cout << "Setting minimal PWM: " << minPWM << endl;

  mMinPWM = minPWM;
}

void HwmonFan::FindStartPWM() {}

json HwmonFan::toJson() const {
  json obj;
  obj = {mPWMControl->toJson(),
         mRpmSensor->toJson(),
         {"label", mLabel},
         {"MinPWM", mMinPWM}};
  return obj;
}

const string HwmonFan::toString() const {
  return "Fan!\nPWMControl: " + mPWMControl->toString() +
         "\nRpmSensor: " + mRpmSensor->toString();
}
