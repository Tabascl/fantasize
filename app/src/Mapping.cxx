#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <thread>

#include <Mapping.h>
#include <fan/HwmonFan.h>
#include <fan/PwmControl.h>

#define SETTLE_TIMEOUT 5

using namespace std;

vector<shared_ptr<Fan>>
Mapping::createMapping(vector<shared_ptr<Sensor>> rpmSensors,
                       vector<shared_ptr<PwmControl>> pwmControls) {
  print("RPM Sensors", rpmSensors);
  print("PWM controllers", pwmControls);
  vector<shared_ptr<Fan>> mapping;

  cout << "Settings all fans to maximum speed" << endl;
  for (auto c : pwmControls) {
    c->enableManualControl();
    c->pwm(100);
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
    c->pwm(50);

    this_thread::sleep_for(chrono::seconds(SETTLE_TIMEOUT));

    for (auto s : rpmSensors) {
      if (s->value() < s->max() * 0.7) {
        cout << "Found matching sensor " << s->toString() << endl;
        mapping.push_back(make_shared<HwmonFan>(c, s));
      }
    }

    cout << "Setting fan back to 100% and wait for settling" << endl;
    c->pwm(100);
    this_thread::sleep_for(chrono::seconds(SETTLE_TIMEOUT));
  }

  cout << "Resetting all fans" << endl;
  for (auto c : pwmControls) {
    c->reset();
  }

  return mapping;
}

template <class Printable>
void Mapping::print(string listLabel, vector<shared_ptr<Printable>> list) {
  cout << listLabel << ": " << endl;

  for (auto i : list) {
    cout << i->toString() << endl;
  }
  cout << "\n";
}
