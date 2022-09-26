#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include <fan/Fan.h>

#define CONFIG_FILE "/etc/fantasize/config.json"

using json = nlohmann::json;

class ConfigManager {
public:
  ConfigManager();
  ~ConfigManager();

  void WriteConfig();

  void SaveFans(std::vector<std::shared_ptr<Fan>> fans);

private:
  json mConfig;
};

#endif // CONFIGMANAGER_H_
