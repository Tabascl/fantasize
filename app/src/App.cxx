#include <execution>

#include <App.h>

using namespace std;

void App::Init() {
  mFans = mSerializer.DeserializeFans(mSensorManager.RPMSensors());

  auto fanCurves = mSerializer.DeserializeFanCurves(
      mSensorManager.TemperatureSensors(), mFans);

  mController = make_unique<Controller>(fanCurves);
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
  mController.reset();
  mSerializer.SerializeFans(mFans);
}
