#ifndef FAN_H_
#define FAN_H_

#include <Printable.h>
#include <Serializable.h>

class Fan : public Serializable, public Printable {
public:
  virtual void PWM(int percent) = 0;
  virtual int RPM() = 0;

  virtual void Label(std::string label) = 0;

  virtual void MinPWM(int value) = 0;
  virtual int MinPWM() = 0;

  virtual void StartPWM(int value) = 0;
  virtual int StartPWM() = 0;

  virtual void FindPWMLimits() = 0;
  virtual void AdjustPWMLimits() = 0;
};

#endif // FAN_H_
