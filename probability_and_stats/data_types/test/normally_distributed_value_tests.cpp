/*
 * Author: Alejandro Valencia
 * Update: November 19, 2025
 *
 * Unit tests for the normally distributed value data type
 *
 */

#include "probability_and_stats/data_types/normally_distributed_value.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <limits>
#include <random>

namespace nm
{
namespace probs_and_stats
{

namespace
{

class BaseClassFixture : public testing::Test
{
  protected:
};

TEST(BaseClassTests, GivenDefaultInstantiation_ExpectDefaultNormallyDistributedValue)
{
    // Given
    nm::probs_and_stats::NormallyDistributedRealValue<double> result{};

    // Expect
    EXPECT_TRUE((result.GetMinValue() == -std::numeric_limits<double>::infinity()) ||
                (result.GetMinValue() == std::numeric_limits<double>::min()));
    EXPECT_TRUE((result.GetMaxValue() == std::numeric_limits<double>::infinity()) ||
                (result.GetMaxValue() == std::numeric_limits<double>::max()));
}

TEST(BaseClassTests, GivenValidMeanAndStdDev_ExpectValidNormallyDistributedValue)
{
    // Given
    double mean = 0.0;
    double std_dev = 1.0;

    // Call
    const NormallyDistributedRealValue<double> result(mean, std_dev);
    std::cout << "Min Value: " << result.GetMinValue() << std::endl;

    // Expect
    EXPECT_TRUE(result.IsMeanValid());
    EXPECT_TRUE(result.IsStdDevValid());
}

TEST(BaseClassTests, GivenValidMeanAndStdDevWithMinAndMax_ExpectValidNormallyDistributedValue)
{
    // Given
    double mean = 0.0;
    double std_dev = 1.0;
    double min = 0;
    double max = 100;

    // Call
    const NormallyDistributedRealValue<double> result(mean, std_dev, min, max);

    // Expect
    double tolerance_{0.001};
    EXPECT_NEAR(result.GetMinValue(), 0.0, tolerance_);
    EXPECT_NEAR(result.GetMaxValue(), 100.0, tolerance_);
}

TEST(BaseClassTests, GivenValidNormamllyDistributedValueWithMinAndMax_ExpectValidConstructedCopy)
{
    // Given
    double mean = 0.0;
    double std_dev = 1.0;
    double min = 0;
    double max = 100;

    // Call
    const NormallyDistributedRealValue<double> result(mean, std_dev, min, max);
    const auto copy = result;

    // Expect
    double tolerance = 1e-3;
    EXPECT_NEAR(copy.GetMinValue(), 0.0, tolerance);
    EXPECT_NEAR(copy.GetMaxValue(), 100.0, tolerance);
}

TEST(BaseClassTests, GivenValidNormallyDistributedValue_ExpectValidSample)
{
    // Given
    double mean = 0;
    double std_dev = 1.0;

    std::random_device random_device;         // Will be used to obtain a seed for the random number engine
    std::mt19937 generator(random_device());  // Standard mersenne_twister_engine seeded with rd()

    // Call
    NormallyDistributedRealValue<double> result(mean, std_dev);

    // Expect
    std::int32_t max_iterations{10};
    for (std::int32_t i{0}; i < max_iterations; ++i)
    {
        EXPECT_NO_THROW(result.GetSample<std::mt19937>(generator));
    }
}

TEST(BaseClassTests, GivenValidNormallyDistributedValueWithMinAndMax_ExpectValidSample)
{
    // Given
    double mean = 0;
    double std_dev = 10.0;
    double min = 0;
    double max = 3;

    std::random_device random_device;         // Will be used to obtain a seed for the random number engine
    std::mt19937 generator(random_device());  // Standard mersenne_twister_engine seeded with rd()

    // Call
    NormallyDistributedRealValue<double> result(mean, std_dev, min, max);

    // Expect
    std::int32_t max_iterations{3};
    for (std::int32_t i{0}; i < max_iterations; ++i)
    {
        EXPECT_GE(result.GetSample<std::mt19937>(generator), min);
        EXPECT_LE(result.GetSample<std::mt19937>(generator), max);
    }
}

}  // namespace
}  // namespace probs_and_stats
}  // namespace nm
