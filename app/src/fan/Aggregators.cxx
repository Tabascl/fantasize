#include <climits>
#include <fan/Aggregators.h>

int
AverageAggregator::aggregate(std::vector<std::shared_ptr<Sensor>> sensors) const
{
  int sum = 0;

  for (auto sensor : sensors) {
    sum += sensor->value();
  }

  return sum / sensors.size();
}

const std::string
AverageAggregator::toString() const
{
  return "Average";
}

int
MaxAggregator::aggregate(std::vector<std::shared_ptr<Sensor>> sensors) const
{
  int max = INT_MIN;

  for (auto sensor : sensors) {
    if (sensor->value() > max)
      max = sensor->value();
  }

  return max;
}

const std::string
MaxAggregator::toString() const
{
  return "Max";
}
