#ifndef FAN_H_
#define FAN_H_

class Fan {
public:
  virtual void pwm(int percent) = 0;
  virtual int rpm() = 0;
};

#endif // FAN_H_
