#include <fan/HwmonFan.h>

using namespace std;

HwmonFan::HwmonFan(shared_ptr<PwmControl> pwmControl,
                   shared_ptr<Sensor> rpmSensor)
    : mPwmControl(pwmControl), mRpmSensor(rpmSensor) {}

void HwmonFan::pwm(int percent) { mPwmControl->pwm(percent); }

int HwmonFan::rpm() { return mRpmSensor->value(); }
