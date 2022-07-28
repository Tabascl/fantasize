#ifndef PWM_H_
#define PWM_H_

#include <string>
#include <unordered_map>
#include <vector>

typedef struct {
  std::string control;
  std::string enable;
  std::string mode;
} PWM_CONTROL;

typedef enum { FULL_SPEED = 0, MANUAL_CONTROL, AUTOMATIC } PWM_ENABLE;
typedef enum { DC = 0, PWM } PWM_MODE;

class PWM {
public:
  PWM();
  void dumpValues();

  std::vector<PWM_CONTROL> getControls();

  void setEnable(PWM_CONTROL control, PWM_ENABLE value);
  void setMode(PWM_CONTROL control, PWM_MODE mode);
  void setValuePwm(PWM_CONTROL control, int pwm);
  void setValuePercent(PWM_CONTROL control, int percentage);

private:
  std::unordered_map<std::string, PWM_CONTROL> mPwmControls;
};

#endif // PWM_H_
