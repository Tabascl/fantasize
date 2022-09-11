#ifndef HWMONFAN_H_
#define HWMONFAN_H_

#include <Fan.h>

class HwmonFan : public Fan {
public:
  void PWM(int value) override;
  int RPM() override;
};

#endif // HWMONFAN_H_
