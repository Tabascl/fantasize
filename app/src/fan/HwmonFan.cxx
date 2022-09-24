#include "fan/PwmControl.h"
#include <boost/json/object.hpp>
#include <fan/HwmonFan.h>

using namespace std;

HwmonFan::HwmonFan(shared_ptr<PwmControl> pwmControl,
                   shared_ptr<Sensor> rpmSensor)
    : mPwmControl(pwmControl), mRpmSensor(rpmSensor) {}

void HwmonFan::pwm(int percent) { mPwmControl->pwm(percent); }

int HwmonFan::rpm() { return mRpmSensor->value(); }

json HwmonFan::toJson() const {
  json obj;
  obj = {mPwmControl->toJson(), mRpmSensor->toJson()};
  return obj;
}

const string HwmonFan::toString() const {
  return "Fan!\nPwmControl: " + mPwmControl->toString() +
         "\nRpmSensor: " + mRpmSensor->toString();
}
