#ifndef AGGREGATORS_H_
#define AGGREGATORS_H_

#include <sensor/Sensor.h>

class Aggregator
{
public:
  virtual int aggregate(std::vector<std::shared_ptr<Sensor>> sensors) const = 0;
  virtual const std::string toString() const = 0;
};

class AverageAggregator : public Aggregator
{
public:
  int aggregate(std::vector<std::shared_ptr<Sensor>> sensors) const override;
  const std::string toString() const override;
};

class MaxAggregator : public Aggregator
{
public:
  int aggregate(std::vector<std::shared_ptr<Sensor>> sensors) const override;
  const std::string toString() const override;
};

#endif // AGGERGATORS_H_
