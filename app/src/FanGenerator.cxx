#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <thread>

#include <FanGenerator.h>
#include <fan/HwmonFan.h>
#include <pwm/PWMControl.h>

#define SETTLE_TIMEOUT 10

using namespace std;

vector<shared_ptr<Fan>>
FanGenerator::FindFans(vector<shared_ptr<Sensor>> rpmSensors,
                       vector<shared_ptr<PWMControl>> pwmControls) {
  print("RPM Sensors", rpmSensors);
  print("PWM controllers", pwmControls);
  vector<shared_ptr<Fan>> mapping;

  cout << "Setting all fans to maximum speed" << endl;
  for (auto c : pwmControls) {
    c->EnableManualControl();
    c->SetPower(100);
  }

  // Wait for fans to settle
  cout << "Waiting for fans to settle" << endl;
  this_thread::sleep_for(chrono::seconds(SETTLE_TIMEOUT));

  // Record values of all RPM sensors
  for (auto s : rpmSensors) {
    int value = s->value();
    s->max(value);

    cout << s->toString() << " max value: " << s->max() << endl;
  }

  // Set each fan to 50% and check if a sensor matches
  for (auto c : pwmControls) {
    cout << "Setting " << c->toString()
         << " to 50% and wait for it to settle..." << endl;
    c->SetPower(50);

    this_thread::sleep_for(chrono::seconds(SETTLE_TIMEOUT));

    for (auto s : rpmSensors) {
      if (s->value() < s->max() * 0.7) {
        cout << "Found matching sensor " << s->toString() << endl;
        mapping.push_back(make_shared<HwmonFan>(c, s));
      }
    }

    cout << "Setting fan back to 100%" << endl;
    c->SetPower(100);
  }

  return mapping;
}

template <class Printable>
void FanGenerator::print(string listLabel, vector<shared_ptr<Printable>> list) {
  cout << listLabel << ": " << endl;

  for (auto i : list) {
    cout << i->toString() << endl;
  }
  cout << "\n";
}
