#ifndef FAN_H_
#define FAN_H_

class Fan {
public:
  virtual void PWM(int percent) = 0;
  virtual int RPM() = 0;
};

#endif // FAN_H_
