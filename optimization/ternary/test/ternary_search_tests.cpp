/*
 * Author : Alejandro Valencia
 * Project: Single Variable optimization - main unit tests
 */

#include "optimization/ternary/ternary.h"
#include <gtest/gtest.h>

namespace nm
{

namespace optimize
{

namespace
{

class SingleVariableOptimizationBaseTestFixture : public ::testing::Test
{
  public:
    std::function<double(double)> function_;
    int max_iterations_{1000};
    double tolerance_{0.001};
};

class TernarySearchTestFixture : public SingleVariableOptimizationBaseTestFixture
{
  public:
    double lower_bound_{-10.0};
    double upper_bound_{10.0};
};

TEST_F(TernarySearchTestFixture, GivenParabolicFunction_ExpectExactSolution)
{
    // Setup
    function_ = [](const double x) -> double { return 6 + 0.5 * x * x; };

    // Call
    const auto x = ternary_min_search(function_, tolerance_, max_iterations_, lower_bound_, upper_bound_);
    const auto f_of_x = function_(x);

    // Expect
    EXPECT_NEAR(x, 0.0, tolerance_);
    EXPECT_NEAR(f_of_x, 6, tolerance_);
}

TEST_F(TernarySearchTestFixture, GivenCubicFunction_ExpectExactSolution)
{
    // Setup
    function_ = [](const double x) -> double { return (x * x * x) / 3.0 - (x * x) / 2.0 - x - 1; };

    // Call
    const auto x = ternary_min_search(function_, tolerance_, max_iterations_, 1, 2);
    const auto f_of_x = function_(x);

    // Expect
    EXPECT_NEAR(x, 1.618, tolerance_);
    EXPECT_NEAR(f_of_x, -2.515, tolerance_);
}

}  // namespace

}  // namespace optimize

}  // namespace nm
