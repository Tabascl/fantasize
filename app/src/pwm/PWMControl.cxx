#include <boost/json/object.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <pwm/PWMControl.h>

#define PWM_POSTFIX_ENABLE "_enable"
#define PWM_POSTFIX_MODE "_mode"

#define PWM_MAX_VALUE 255

using namespace std;
namespace fs = filesystem;

PWMControl::PWMControl(string controlPath) : mControlPath(controlPath) {
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

PWMControl::~PWMControl() {
  cout << "Cleanup" << endl;
  Reset();
}

void PWMControl::pwm(int percent) {
  int pwmValue = PWM_MAX_VALUE * percent / 100;

  ofstream ostrm(mControlPath, ios::trunc);
  ostrm << pwmValue;
  ostrm.close();
}

int PWMControl::pwm() {
  int value;
  ifstream istrm;

  istrm.open(mControlPath);
  istrm >> value;

  return value;
}

void PWMControl::EnableManualControl() {
  ofstream ostrm(mEnablePath, ios::trunc);
  ostrm << static_cast<int>(PWM_ENABLE::MANUAL_CONTROL);
  ostrm.close();
}

void PWMControl::Reset() {
  ofstream ostrm(mEnablePath, ios::trunc);

  ostrm << mInitialEnable;
  ostrm.close();

  ostrm.open(mModePath, ios::trunc);
  ostrm << mInitialMode;

  ostrm.close();
}

const string PWMControl::toString() const {
  return fs::path(mControlPath).filename();
}

json PWMControl::toJson() const {
  json obj = {"PWMControl", mControlPath};
  return obj;
}
