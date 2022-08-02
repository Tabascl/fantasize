#ifndef PWM_H_
#define PWM_H_

#include <string>
#include <unordered_map>
#include <vector>

enum class PWM_CONTROL_PROPERTY { CONTROL, ENABLE, MODE };

struct PWM_CONTROL {
  std::string control;
  std::string enable;
  std::string mode;

  std::string initialEnable;
  std::string initialMode;
};

enum class PWM_ENABLE { FULL_SPEED = 0, MANUAL_CONTROL };
enum class PWM_MODE { DC = 0, PWM };

class PWM {
public:
  PWM();
  void dumpValues();

  std::vector<PWM_CONTROL> getControls();
  int readValue(PWM_CONTROL control, PWM_CONTROL_PROPERTY property);

  void setEnable(PWM_CONTROL control, PWM_ENABLE value);
  void setMode(PWM_CONTROL control, PWM_MODE mode);
  void setValuePwm(PWM_CONTROL control, int pwm);
  void setValuePercent(PWM_CONTROL control, int percentage);

private:
  std::unordered_map<std::string, PWM_CONTROL> mPwmControls;
};

#endif // PWM_H_
