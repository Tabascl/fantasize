#ifndef PWMCONTROL_H_
#define PWMCONTROL_H_

#include <string>

#include <Printable.h>

enum class PWM_CONTROL_PROPERTY { CONTROL, ENABLE, MODE };
enum class PWM_ENABLE { FULL_SPEED = 0, MANUAL_CONTROL };
enum class PWM_MODE { DC = 0, PWM };

class PwmControl : public Printable {
public:
  PwmControl(std::string controlPath);

  void pwm(int percent);
  int pwm();

  void enableManualControl();
  void reset();

  const std::string toString() const override;

private:
  int readValue(std::string path);

  std::string mControlPath;
  std::string mEnablePath;
  std::string mModePath;

  std::string mInitialEnable;
  std::string mInitialMode;
};

#endif // PWMCONTROL_H_
