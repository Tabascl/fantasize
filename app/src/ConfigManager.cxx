#include <filesystem>
#include <fstream>

#include <ConfigManager.h>
#include <memory>

using namespace std;
namespace fs = std::filesystem;

ConfigManager::ConfigManager() {
  if (fs::exists(CONFIG_FILE)) {
    ifstream f(CONFIG_FILE);
    mConfig = json::parse(f);
  }
}

void ConfigManager::SaveFans(vector<shared_ptr<Fan>> fans) {
  json obj;

  for (auto fan : fans) {
  }
}

ConfigManager::~ConfigManager() { WriteConfig(); }

void ConfigManager::WriteConfig() {
  ofstream f(CONFIG_FILE, ios::trunc);
  f << mConfig.dump(2) << endl;
}
