#ifndef HWMONFAN_H_
#define HWMONFAN_H_

#include <boost/json/object.hpp>
#include <memory>

#include <fan/Fan.h>
#include <pwm/PWMControl.h>
#include <sensor/Sensor.h>

class HwmonFan : public Fan {
public:
  HwmonFan(std::shared_ptr<PWMControl> pwmControl,
           std::shared_ptr<Sensor> rpmSensor, std::string label = "",
           int minPWM = 0, int startPWM = 0);

  void PWM(int percent) override;
  int RPM() override;

  void FindMinPWM() override;
  void FindStartPWM() override;

  json toJson() const override;

  const std::string toString() const override;

private:
  std::shared_ptr<PWMControl> mPWMControl;
  std::shared_ptr<Sensor> mRpmSensor;
  std::string mLabel;

  int mMinPWM;
  int mStartPWM;
};

#endif // HWMONFAN_H_
