#ifndef APP_H_
#define APP_H_

#include <memory>

#include <Controller.h>
#include <FanGenerator.h>
#include <Serializer.h>
#include <fan/FanLabeler.h>
#include <pwm/PWMControlFacade.h>
#include <sensor/SensorManager.h>

class App {
public:
  void Init();

  void InitialSetup();
  void NormalOperation();

  void Shutdown();

private:
  SensorManager mSensorManager;
  Serializer mSerializer;
  PWMControlFacade mPWMControlFacade;
  FanLabeler mFanLabeler;
  FanGenerator mFanGenerator;

  std::unique_ptr<Controller> mController;
};

#endif // APP_H_
