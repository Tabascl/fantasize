#include <filesystem>
#include <iostream>
#include <regex>

#include <pwm/PWMControlFacade.h>

using namespace std;
namespace fs = std::filesystem;

vector<shared_ptr<PWMControl>> PWMControlFacade::PWMControls() {
  vector<shared_ptr<PWMControl>> controls;

  const regex re_ctrl_enable("pwm[0-9]_enable");
  const regex re_ctrl_mode("pwm[0-9]_mode");
  const regex re_ctrl("pwm[0-9]");

  if (!fs::exists(HWMON_BASE_PATH)) {
    cout << HWMON_BASE_PATH << " doesn't exist" << endl;
  } else {
    for (const fs::directory_entry &hwmon_device :
         fs::directory_iterator{HWMON_BASE_PATH}) {

      for (const fs::directory_entry &control :
           fs::directory_iterator{hwmon_device}) {
        auto filename = control.path().filename().string();

        if (regex_match(filename, re_ctrl)) {
          auto controlPath = control.path().string();

          controls.push_back(make_shared<PWMControl>(controlPath));
        }
      }
    }
  }

  return controls;
}
