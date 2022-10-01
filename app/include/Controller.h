#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <memory>
#include <thread>
#include <vector>

#include <fan/FanCurve.h>

class Controller {
public:
  Controller(std::vector<std::shared_ptr<FanCurve>> curves);
  ~Controller();

  void StartFanControlLoop();
  void StopFanControlLoop();

private:
  void Loop();

  std::vector<std::shared_ptr<FanCurve>> mFanCurves;
  std::atomic<bool> mRun;

  std::unique_ptr<std::thread> mWorker;
};

#endif // CONTROLLER_H_
