#ifndef FAN_H_
#define FAN_H_

#include <Printable.h>
#include <Serializable.h>

class Fan : public Serializable, public Printable {
public:
  virtual void pwm(int percent) = 0;
  virtual int rpm() = 0;
};

#endif // FAN_H_
