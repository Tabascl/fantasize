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

  void ZeroFanModeSupported(bool value) override;
  bool ZeroFanModeSupported() override;

  void FindPWMLimits() override;
  void AdjustPWMLimits() override;

  void EnforceSetValue() override;

  json toJson() const override;

  const std::string toString() const override;

private:
  bool InhibitStopPeriodExpired();
  void SetPower(int percent);

  std::shared_ptr<PWMControl> mPWMControl;
  std::shared_ptr<Sensor> mRpmSensor;
  std::string mLabel;

  int mMinPWM = 0;
  int mStartPWM = 0;
  bool mZeroFanModeSupported = false;
  std::chrono::time_point<std::chrono::steady_clock> mLastAdjustmentTime;
  std::chrono::time_point<std::chrono::steady_clock> mLastStartTime;
  int mSetValue = 0;
  bool mWasStopped = false;
};

#endif // HWMONFAN_H_
