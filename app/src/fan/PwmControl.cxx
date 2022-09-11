#include <filesystem>
#include <fstream>

#include <fan/PwmControl.h>

#define PWM_POSTFIX_ENABLE "_enable"
#define PWM_POSTFIX_MODE "_mode"

#define PWM_MAX_VALUE 255

using namespace std;
namespace fs = filesystem;

PwmControl::PwmControl(string controlPath) : mControlPath(controlPath) {
  fs::path pathEnable(mControlPath + PWM_POSTFIX_ENABLE);
  fs::path pathMode(mControlPath + PWM_POSTFIX_MODE);

  mEnablePath = pathEnable;
  mModePath = pathMode;

  ifstream istrm;

  istrm.open(mEnablePath);
  istrm >> mInitialEnable;
  istrm.close();

  istrm.open(mInitialMode);
  istrm >> mInitialMode;
  istrm.close();
}

void PwmControl::pwm(int percent) {
  int pwmValue = PWM_MAX_VALUE * percent / 100;

  ofstream ostrm(mControlPath, ios::trunc);
  ostrm << pwmValue;
  ostrm.close();
}

int PwmControl::pwm() {
  int value;
  ifstream istrm;

  istrm.open(mControlPath);
  istrm >> value;

  return value;
}

void PwmControl::enableManualControl() {
  ofstream ostrm(mEnablePath, ios::trunc);
  ostrm << static_cast<int>(PWM_ENABLE::MANUAL_CONTROL);
  ostrm.close();
}

void PwmControl::reset() {
  ofstream ostrm(mEnablePath, ios::trunc);
  ostrm << mInitialEnable;
  ostrm.close();
}
