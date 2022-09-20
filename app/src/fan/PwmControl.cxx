#include <boost/json/object.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

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

PwmControl::~PwmControl() {
  cout << "Cleanup" << endl;
  Reset();
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

void PwmControl::EnableManualControl() {
  ofstream ostrm(mEnablePath, ios::trunc);
  ostrm << static_cast<int>(PWM_ENABLE::MANUAL_CONTROL);
  ostrm.close();
}

void PwmControl::Reset() {
  ofstream ostrm(mEnablePath, ios::trunc);

  ostrm << mInitialEnable;
  ostrm.close();

  ostrm.open(mModePath, ios::trunc);
  ostrm << mInitialMode;

  ostrm.close();
}

const string PwmControl::toString() const {
  return fs::path(mControlPath).filename();
}

json PwmControl::toJson() const {
  json obj = {"PwmControl", toString()};
  return obj;
}
