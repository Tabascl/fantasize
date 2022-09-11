#ifndef HWMONFAN_H_
#define HWMONFAN_H_

#include <fan/Fan.h>
#include <fan/PwmControl.h>

class HwmonFan : public Fan {
public:
  void PWM(int percent) override;
  int RPM() override;

private:
  PwmControl mPwmControl;
  // PwmSensor mPwmSensor;
};

#endif // HWMONFAN_H_
