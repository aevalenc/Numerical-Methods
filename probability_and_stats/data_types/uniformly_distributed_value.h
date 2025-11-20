/*
 *  Author: Alejandro Valencia
 *  Update: November 17, 2025
 */

#ifndef PROBABILITY_AND_STATS_DATA_TYPES_UNIFORMLY_DISTRIBUTED_VALUE_H
#define PROBABILITY_AND_STATS_DATA_TYPES_UNIFORMLY_DISTRIBUTED_VALUE_H

#include <random>
#include <utility>

namespace nm
{

namespace probs_and_stats
{

template <typename T>
class UniformlyDistributedRealValue
{
  public:
    UniformlyDistributedRealValue() {}
    UniformlyDistributedRealValue(T min_value, T max_value) : min_value_(min_value), max_value_(max_value)
    {
        std::uniform_real_distribution<> value(min_value_, max_value_);
        value_ = value;
    }

    ~UniformlyDistributedRealValue() {}

    UniformlyDistributedRealValue(const UniformlyDistributedRealValue& other)
    {
        if (this != &other)
        {
            value_ = other.value_;
            min_value_ = other.min_value_;
            max_value_ = other.max_value_;
        }
    };
    UniformlyDistributedRealValue(UniformlyDistributedRealValue&& other) noexcept {};

    UniformlyDistributedRealValue& operator=(const UniformlyDistributedRealValue& other)
    {
        if (this != &other)
        {
            value_ = other.value_;
            min_value_ = other.min_value_;
            max_value_ = other.max_value_;
        }
        return *this;
    }
    UniformlyDistributedRealValue& operator=(UniformlyDistributedRealValue&& other) noexcept
    {
        if (this != &other)
        {
            value_ = std::move(other.value_);
            min_value_ = std::move(other.min_value_);
            max_value_ = std::move(other.max_value_);
        }
        return *this;
    }

  public:
    template <typename URNG>
    T GetSample(URNG& seed)
    {
        return value_(seed);
    }
    T GetMinValue() const { return min_value_; }
    T GetMaxValue() const { return max_value_; }

  private:
    T min_value_{};
    T max_value_{};
    std::uniform_real_distribution<> value_{};
};

}  // namespace probs_and_stats
}  // namespace nm

#endif  // PROBABILITY_AND_STATS_DATA_TYPES_UNIFORMLY_DISTRIBUTED_VALUE_H
