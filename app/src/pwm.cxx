#include <cstdio>
#include <pwm.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace fs = std::filesystem;
using namespace std;

#define HWMON_BASE_PATH "/sys/class/hwmon"

#define PWM_POSTFIX_ENABLE "_enable"
#define PWM_POSTFIX_MODE "_mode"

#define PWM_MAX_VALUE 255

PWM::PWM() {
  const regex re_ctrl_enable("pwm[0-9]_enable");
  const regex re_ctrl_mode("pwm[0-9]_mode");
  const regex re_ctrl("pwm[0-9]");

  if (!fs::exists(HWMON_BASE_PATH)) {
    cerr << HWMON_BASE_PATH << " doesn't exist" << endl;
  } else {
    for (const fs::directory_entry &hwmon_device :
         fs::directory_iterator{HWMON_BASE_PATH}) {

      for (const fs::directory_entry &control :
           fs::directory_iterator{hwmon_device}) {
        auto filename = control.path().filename().string();

        if (regex_match(filename, re_ctrl)) {
          auto controlPath = control.path().string();

          fs::path path_ctrl_enable(
              string(controlPath + string(PWM_POSTFIX_ENABLE)));
          fs::path path_ctrl_mode(
              string(controlPath + string(PWM_POSTFIX_MODE)));

          if (fs::exists(path_ctrl_enable) && fs::exists(path_ctrl_mode))
            cout << control << endl;

          mPwmControls.insert(
              {controlPath, PWM_CONTROL{controlPath, path_ctrl_enable.string(),
                                        path_ctrl_mode.string()}});
        }
      }
    }
  }
}

void PWM::dumpValues() {
  for (auto control : mPwmControls) {
    cout << control.second.control << ", " << control.second.enable << ", "
         << control.second.mode << endl;
  }
}

std::vector<PWM_CONTROL> PWM::getControls() {
  std::vector<PWM_CONTROL> vec;

  for (auto elem : mPwmControls) {
    vec.push_back(elem.second);
  }

  return vec;
}

void PWM::setEnable(PWM_CONTROL control, PWM_ENABLE value) {
  cout << control.control << endl;
  std::ofstream ostrm(control.enable, std::ios::trunc);
  ostrm << value;
  ostrm.close();
}

void PWM::setValuePwm(PWM_CONTROL control, int pwm) {
  if (pwm < 0 || pwm > 255)
    return;

  std::ofstream ostrm(control.control, std::ios::trunc);
  ostrm << pwm;
  ostrm.close();
}
void PWM::setValuePercent(PWM_CONTROL control, int percentage) {
  setValuePwm(control, PWM_MAX_VALUE * percentage / 100);
}
