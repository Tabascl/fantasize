#ifndef FANLABELER_H_
#define FANLABELER_H_

#include <memory>
#include <vector>

#include <fan/Fan.h>

class FanLabeler {
public:
  void RunFanLabelInteraction(std::vector<std::shared_ptr<Fan>> fans);
};

#endif // FANLABELER_H_
