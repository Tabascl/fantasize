#include <boost/log/attributes/named_scope.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <boost/log/trivial.hpp>

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
  BOOST_LOG_FUNCTION();

  BOOST_LOG_TRIVIAL(trace) << "Cleanup";
  Reset();
}

void PWMControl::SetPower(int percent) {
  BOOST_LOG_FUNCTION();

  int pwmValue = (PWM_MAX_VALUE * percent) / 100;

  if (pwmValue != CurrentPWM()) {
    BOOST_LOG_TRIVIAL(trace) << "Updating control value of " << toString()
                             << " to " << percent << "% (" << pwmValue << ")";
    ofstream ostrm(mControlPath, ios::trunc);
    ostrm << pwmValue;
    ostrm.close();
  }
}

int PWMControl::CurrentPWM() {
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

const string PWMControl::toString() const { return fs::path(mControlPath); }

json PWMControl::toJson() const {
  json obj = {"PWMControl", mControlPath};
  return obj;
}
