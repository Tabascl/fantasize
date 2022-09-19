#ifndef PRINTABLE_H_
#define PRINTABLE_H_

#include <string>

class Printable {
public:
  virtual const std::string toString() const = 0;
};

#endif // PRINTABLE_H_
