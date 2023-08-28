#include "fan/Fan.h"
#include "fan/FanCurve.h"
#include <chrono>
#include <execution>

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/trivial.hpp>

#include <App.h>
#include <memory>
#include <thread>

using namespace std;

void App::Init() {
  BOOST_LOG_FUNCTION();

  bool everythingFound = false;

  mFans = mSerializer.DeserializeFans(mSensorManager.RPMSensors());
  auto fanCurves = mSerializer.DeserializeFanCurves(
      mSensorManager.TemperatureSensors(), mFans, everythingFound);

  while (!everythingFound) {
    BOOST_LOG_TRIVIAL(info) << "Couldn't find every sensor. Retrying in 5s...";
    this_thread::sleep_for(chrono::seconds(5));

    mSensorManager.ReloadSensors();
    mFans = mSerializer.DeserializeFans(mSensorManager.RPMSensors());
    fanCurves = mSerializer.DeserializeFanCurves(
        mSensorManager.TemperatureSensors(), mFans, everythingFound);
  }

  mSettings = mSerializer.DeserializeSettings();

  mController = make_unique<Controller>(mSettings, fanCurves);
}

void App::InitialSetup() {
  auto fans = mFanGenerator.FindFans(mSensorManager.RPMSensors(),
                                     mPWMControlFacade.PWMControls());

  std::for_each(std::execution::par, std::begin(fans), std::end(fans),
                [](auto &&fan) { fan->FindPWMLimits(); });

  mFanLabeler.RunFanLabelInteraction(fans);

  mSerializer.SerializeFans(fans);

  mFans = fans;
}

void App::NormalOperation() {
  if (mController)
    mController->StartFanControlLoop();
}

void App::Shutdown() {
  mSerializer.SerializeFans(mFans);
  mFans.clear();
  mController.reset();
}
