#include <iostream>
#include <string>

#include <fan/FanLabeler.h>

using namespace std;

void FanLabeler::RunFanLabelInteraction(
    std::vector<std::shared_ptr<Fan>> fans) {
  cout << "Setting all fans to their minimum value" << endl;

  for (auto f : fans) {
    f->PWM(0);
  }

  cout << endl;

  for (auto f : fans) {
    cout << "Setting fan " << f->toString() << " to max power" << endl;

    f->PWM(100);

    cout << "Look inside your PC and check which fan is\n"
            "spinning fastest and enter a name for it.\n"
            "Just press enter to skip."
         << endl;

    std::string name;
    getline(cin, name);

    if (!name.empty()) {
      cout << "Setting " << name << " as label for this fan." << endl;
      f->Label(name);
    }

    cout << "Resetting fan to lowest value\n\n" << endl;
    f->PWM(0);
  }

  cout << "Done!\n" << endl;
}
