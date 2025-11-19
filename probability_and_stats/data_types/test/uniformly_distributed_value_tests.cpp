/*
 * Author: Alejandro Valencia
 * Update: November 17, 2025
 *
 * Unit tests for the uniformly distributed value data type
 *
 */

#include "probability_and_stats/data_types/uniformly_distributed_value.h"
#include <cstdint>
#include <gtest/gtest.h>
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
    nm::probs_and_stats::UniformlyDistributedRealValue<double> u_{};
    double tolerance_{0.001};
};

TEST_F(BaseClassFixture, GivenDefaultInstantiation_ExpectDefaultUniformlyDistributedValue)
{
    const auto result = u_;
    EXPECT_NEAR(result.GetMinValue(), 0.0, tolerance_);
    EXPECT_NEAR(result.GetMaxValue(), 0.0, tolerance_);
}

TEST(BaseClassTests, GivenValidBounds_ExpectValidUniformlyDistributedValue)
{
    // Given
    double a = 0.0;
    double b = 1.0;

    // Call
    const UniformlyDistributedRealValue<double> result(a, b);

    // Expect
    double tolerance = 1e-3;
    EXPECT_NEAR(result.GetMinValue(), 0.0, tolerance);
    EXPECT_NEAR(result.GetMaxValue(), 1.0, tolerance);
}

TEST(BaseClassTests, GivenValidUniformlyDistributedValue_ExpectValidConstructedCopy)
{
    // Given
    double a = 0.0;
    double b = 1.0;

    // Call
    const UniformlyDistributedRealValue<double> result(a, b);
    const auto copy = result;

    // Expect
    double tolerance = 1e-3;
    EXPECT_NEAR(copy.GetMinValue(), 0.0, tolerance);
    EXPECT_NEAR(copy.GetMaxValue(), 1.0, tolerance);
}

TEST(BaseClassTests, GivenValidUniformlyDistributedValue_ExpectValidSample)
{
    // Given
    double a = 0.0;
    double b = 1.0;

    std::random_device random_device;         // Will be used to obtain a seed for the random number engine
    std::mt19937 generator(random_device());  // Standard mersenne_twister_engine seeded with rd()

    // Call
    UniformlyDistributedRealValue<double> result(a, b);

    // Expect
    std::int32_t max_iterations{1000};
    double sample{};
    for (std::int32_t i{0}; i < max_iterations; ++i)
    {
        sample = result.GetSample<std::mt19937>(generator);
        EXPECT_GE(sample, a);
        EXPECT_LE(sample, b);
    }
}

}  // namespace
}  // namespace probs_and_stats
}  // namespace nm
