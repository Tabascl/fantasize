#ifndef SENSOR_H_
#define SENSOR_H_

#include <Printable.h>
#include <Serializable.h>

class Sensor : public Printable, public Serializable {
public:
  // Read the current value
  virtual int value() = 0;

  virtual int max() const;
  virtual void max(int value);

protected:
  int mMax = 0;
};

#endif // SENSOR_H_
