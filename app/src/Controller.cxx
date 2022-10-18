#include <chrono>
#include <memory>

#include <Controller.h>
#include <fan/FanCurve.h>

using namespace std;

Controller::Controller(shared_ptr<Settings> settings,
                       vector<shared_ptr<FanCurve>> curves)
    : mTimeout((1 / settings->Frequency()) * 1000), mFanCurves(curves),
      mRun(false) {}

Controller::~Controller() { StopFanControlLoop(); }

void Controller::StartFanControlLoop() {
  mRun = true;
  Loop();
  // mWorker = make_unique<thread>(&Controller::Loop, this);
}

void Controller::StopFanControlLoop() {
  mRun = false;
  // if (mWorker->joinable())
  //   mWorker->join();
  // mWorker.reset();
}

void Controller::Loop() {
  while (mRun) {
    for (auto c : mFanCurves) {
      c->DoFanControl();
    }

    this_thread::sleep_for(chrono::milliseconds(mTimeout));
  }
}
