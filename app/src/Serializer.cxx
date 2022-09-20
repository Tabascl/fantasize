#include <filesystem>
#include <fstream>
#include <iostream>

#include <Serializer.h>

namespace fs = std::filesystem;

#define SERIALIZATION_DIR "/etc/fantasize"
#define FANS_JSON_FILENAME "fans.json"

Serializer::Serializer() {
  if (!fs::exists(SERIALIZATION_DIR)) {
    fs::create_directory(SERIALIZATION_DIR);
  }
}

void Serializer::Serialize(std::vector<std::shared_ptr<Fan>> fans) {
  json fansArr;

  for (auto f : fans) {
    fansArr.push_back(f->toJson());
  }

  json obj;

  obj["fans"] = fansArr;

  std::cout << "Json obj: " << obj.dump(2) << std::endl;

  WriteJson(obj);
}

void Serializer::WriteJson(json o) {
  std::ofstream ostrm(fs::path(SERIALIZATION_DIR) / FANS_JSON_FILENAME,
                      std::ios::trunc);
  ostrm << o.dump(2) << "\n";
}
