#ifndef HWMONFAN_H_
#define HWMONFAN_H_

#include <memory>

#include <fan/Fan.h>
#include <fan/PwmControl.h>
#include <sensor/Sensor.h>

class HwmonFan : public Fan {
public:
  HwmonFan(std::unique_ptr<PwmControl> pwmControl,
           std::unique_ptr<Sensor> rpmSensor);

  void pwm(int percent) override;
  int rpm() override;

private:
  std::unique_ptr<PwmControl> mPwmControl;
  std::unique_ptr<Sensor> mRpmSensor;
};

#endif // HWMONFAN_H_
