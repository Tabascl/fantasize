#ifndef PWMCONTROLFACADE_H_
#define PWMCONTROLFACADE_H_

#include <filesystem>
#include <memory>
#include <regex>
#include <vector>

#include <pwm/PWMControl.h>

#define HWMON_BASE_PATH "/sys/class/hwmon"

class PWMControlFacade {
public:
  std::vector<std::shared_ptr<PWMControl>> PWMControls();
};

#endif // PWMCONTROLFACADE_H_
