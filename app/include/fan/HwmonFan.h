#ifndef HWMONFAN_H_
#define HWMONFAN_H_

#include <fan/Fan.h>

class HwmonFan : public Fan {
public:
  void PWM(int percent) override;
  int RPM() override;
};

#endif // HWMONFAN_H_
