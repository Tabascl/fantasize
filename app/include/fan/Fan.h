#ifndef FAN_H_
#define FAN_H_

#include <Printable.h>
#include <Serializable.h>

class Fan : public Serializable, public Printable {
public:
  virtual void PWM(int percent) = 0;
  virtual int RPM() = 0;

  virtual void FindMinPWM() = 0;
  virtual void FindStartPWM() = 0;
};

#endif // FAN_H_
