#include "pwm/PWMControl.h"
#include <boost/json/object.hpp>
#include <fan/HwmonFan.h>

using namespace std;

HwmonFan::HwmonFan(shared_ptr<PWMControl> pwmControl,
                   shared_ptr<Sensor> rpmSensor)
    : mPWMControl(pwmControl), mRpmSensor(rpmSensor) {}

void HwmonFan::pwm(int percent) { mPWMControl->pwm(percent); }

int HwmonFan::rpm() { return mRpmSensor->value(); }

json HwmonFan::toJson() const {
  json obj;
  obj = {mPWMControl->toJson(), mRpmSensor->toJson(), mLabel};
  return obj;
}

const string HwmonFan::toString() const {
  return "Fan!\nPWMControl: " + mPWMControl->toString() +
         "\nRpmSensor: " + mRpmSensor->toString();
}
