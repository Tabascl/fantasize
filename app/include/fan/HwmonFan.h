#ifndef HWMONFAN_H_
#define HWMONFAN_H_

#include <boost/json/object.hpp>
#include <memory>

#include <fan/Fan.h>
#include <fan/PwmControl.h>
#include <sensor/Sensor.h>

class HwmonFan : public Fan {
public:
  HwmonFan(std::shared_ptr<PwmControl> pwmControl,
           std::shared_ptr<Sensor> rpmSensor);

  void pwm(int percent) override;
  int rpm() override;

  json toJson() const override;

private:
  std::shared_ptr<PwmControl> mPwmControl;
  std::shared_ptr<Sensor> mRpmSensor;
};

#endif // HWMONFAN_H_
