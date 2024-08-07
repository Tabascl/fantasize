#ifndef PWMCONTROL_H_
#define PWMCONTROL_H_

#include <string>

#include <Printable.h>
#include <Serializable.h>

enum class PWM_CONTROL_PROPERTY { CONTROL, ENABLE, MODE };
enum class PWM_ENABLE { FULL_SPEED = 0, MANUAL_CONTROL };
enum class PWM_MODE { DC = 0, PWM };

class PWMControl : public Printable, public Serializable {
public:
  PWMControl(std::string controlPath, int deviceIndex);
  ~PWMControl();

  void SetPower(int percent);
  int CurrentPWM();

  void EnableManualControl();
  void Reset();

  const std::string toString() const override;

  json toJson() const override;

private:
  std::string mConfigPath;
  std::string mControlPath;
  std::string mEnablePath;
  std::string mModePath;
  int mDeviceIndex;

  std::string mInitialEnable;
  std::string mInitialMode;
};

#endif // PWMCONTROL_H_
