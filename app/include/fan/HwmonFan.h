#ifndef HWMONFAN_H_
#define HWMONFAN_H_

#include <chrono>
#include <memory>

#include <fan/Fan.h>
#include <pwm/PWMControl.h>
#include <sensor/Sensor.h>

class HwmonFan : public Fan {
public:
  HwmonFan(std::shared_ptr<PWMControl> pwmControl,
           std::shared_ptr<Sensor> rpmSensor);

  void PWM(int percent) override;
  int RPM() override;

  void Label(std::string label) override;

  void MinPWM(int value) override;
  int MinPWM() override;

  void StartPWM(int value) override;
  int StartPWM() override;

  void FindPWMLimits() override;
  void AdjustPWMLimits() override;

  json toJson() const override;

  const std::string toString() const override;

private:
  std::shared_ptr<PWMControl> mPWMControl;
  std::shared_ptr<Sensor> mRpmSensor;
  std::string mLabel;

  int mMinPWM;
  int mStartPWM;
  std::chrono::time_point<std::chrono::steady_clock> mLastAdjustmentTime;
};

#endif // HWMONFAN_H_
