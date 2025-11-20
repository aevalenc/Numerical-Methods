/*
 *  Author: Alejandro Valencia
 *  Update: November 17, 2025
 */

#ifndef PROBABILITY_AND_STATS_DATA_TYPES_NORMALLY_DISTRIBUTED_VALUE_H
#define PROBABILITY_AND_STATS_DATA_TYPES_NORMALLY_DISTRIBUTED_VALUE_H

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <utility>

#define PI 4 * atan(1)

namespace nm
{

namespace probs_and_stats
{

template <typename T>
class NormallyDistributedRealValue
{
  public:
    NormallyDistributedRealValue() {}
    NormallyDistributedRealValue(T mean, T std_dev) : mean_(mean), std_dev_(std_dev)
    {
        std::normal_distribution<> value(mean_, std_dev_);
        value_ = value;
        max_value_ = value_.max();
        min_value_ = value_.min();
    }

    NormallyDistributedRealValue(T mean, T std_dev, T min_value, T max_value)
        : mean_(mean), std_dev_(std_dev), min_value_(min_value), max_value_(max_value)
    {
        std::normal_distribution<> value(mean_, std_dev_);
        value_ = value;
    }

    ~NormallyDistributedRealValue() {}

    NormallyDistributedRealValue(const NormallyDistributedRealValue& other)
    {
        if (this != &other)
        {
            value_ = other.value_;
            mean_ = other.mean_;
            std_dev_ = other.std_dev_;
            min_value_ = other.min_value_;
            max_value_ = other.max_value_;
        }
    };
    NormallyDistributedRealValue(NormallyDistributedRealValue&& other) noexcept {};

    NormallyDistributedRealValue& operator=(const NormallyDistributedRealValue& other)
    {
        if (this != &other)
        {
            value_ = other.value_;
            mean_ = other.mean_;
            std_dev_ = other.std_dev_;
            min_value_ = other.min_value_;
            max_value_ = other.max_value_;
        }
        return *this;
    }
    NormallyDistributedRealValue& operator=(NormallyDistributedRealValue&& other) noexcept
    {
        if (this != &other)
        {
            value_ = std::move(other.value_);
            mean_ = std::move(other.mean_);
            std_dev_ = std::move(other.std_dev_);
            min_value_ = std::move(other.min_value_);
            max_value_ = std::move(other.max_value_);
        }
        return *this;
    }

  public:
    bool IsMeanValid() const
    {
        return ((mean_ != std::numeric_limits<T>::infinity()) || (mean_ != std::numeric_limits<T>::max()) ||
                (mean_ != std::numeric_limits<T>::min()));
    }
    bool IsStdDevValid() const
    {
        return ((std_dev_ != std::numeric_limits<T>::infinity()) || (std_dev_ != std::numeric_limits<T>::max()) ||
                (std_dev_ != std::numeric_limits<T>::min()));
    }
    bool IsMinValueValid() const
    {
        return ((min_value_ != -std::numeric_limits<T>::infinity()) || (min_value_ != std::numeric_limits<T>::min()));
    }
    bool IsMaxValueValid() const
    {
        return ((max_value_ != std::numeric_limits<T>::infinity()) || (max_value_ != std::numeric_limits<T>::max()));
    }
    T GetMinValue() const
    {
        if (IsMinValueValid())
        {
            return min_value_;
        }
        return std::numeric_limits<T>::infinity();
    }
    T GetMaxValue() const
    {
        if (IsMaxValueValid())
        {
            return max_value_;
        }
        return std::numeric_limits<T>::infinity();
    }

    template <typename URNG>
    T GetSample(URNG& seed)
    {
        const auto sample = value_(seed);
        if (IsMinValueValid() && IsMaxValueValid())
        {
            return std::clamp(sample, min_value_, max_value_);
        }

        return sample;
    }

  private:
    T mean_{std::numeric_limits<T>::infinity()};
    T std_dev_{std::numeric_limits<T>::infinity()};
    T min_value_{-std::numeric_limits<T>::infinity()};
    T max_value_{std::numeric_limits<T>::infinity()};
    std::normal_distribution<> value_{};
};

}  // namespace probs_and_stats
}  // namespace nm

#endif  // PROBABILITY_AND_STATS_DATA_TYPES_NORMALLY_DISTRIBUTED_VALUE_H
