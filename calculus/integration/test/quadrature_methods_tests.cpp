/*
 * Tests for Quadrature Based Numerical Integration Methods
 *
 * Author: Alejandro Valencia
 * Update: August 14, 2025
 *
 */

#include "calculus/integration/simpsons_method/simpsons_method.h"
#include "calculus/integration/trapezoidal_method/trapezoidal_method.h"
#include "gtest/gtest.h"
#include <cmath>

namespace nm
{
namespace calculus
{

struct QuadratureTestParameter
{
    double a{};
    double b{};
    double n{};
    double expected_value;
};

namespace
{

class QuadratureTestFixture : public ::testing::Test
{

  public:
    void SetDefaultExponentialFunction()
    {
        default_function_ = [](double x) -> double { return std::exp(x); };
    }

  public:
    std::function<double(double)> default_function_;
    double tolerance_{1e-3};
};

class QuadratureTestFixtureParameterized : public QuadratureTestFixture,
                                           public ::testing::WithParamInterface<QuadratureTestParameter>
{
};

TEST_P(QuadratureTestFixtureParameterized, GivenValidFunction_ExpectCorrectValue)
{
    // Given
    const auto params = GetParam();
    SetDefaultExponentialFunction();

    // Call
    const auto result = TrapezoidalIntegration(default_function_, params.a, params.b, params.n);

    // Expect
    EXPECT_NEAR(result, params.expected_value, tolerance_);
}

INSTANTIATE_TEST_SUITE_P(TrapezoidalMethodTests,
                         QuadratureTestFixtureParameterized,
                         ::testing::Values(QuadratureTestParameter{0, 1, 1, 1.859},
                                           QuadratureTestParameter{0, 1, 10001, 1.718}));

TEST_F(QuadratureTestFixture, GivenGaussianExponential_ExpectCorrectValue)
{
    // Given
    default_function_ = [](const double x) -> double { return std::exp(-x * x); };

    // Call
    const auto result = TrapezoidalIntegration(default_function_, 0, 1, 4);
    const auto simpson = SimpsonsIntegration(default_function_, 0, 1, 4);

    // Expect
    EXPECT_NEAR(result, 0.742984, tolerance_);
    EXPECT_NEAR(simpson, 0.7468, tolerance_);
}

TEST_F(QuadratureTestFixture, GivenRationalFunction_ExpectCorrectValue)
{
    // Given
    default_function_ = [](const double x) -> double { return 6 / (x * x + 1); };

    // Call
    const auto trapezoid = TrapezoidalIntegration(default_function_, -1, 2, 6);
    const auto simpson = SimpsonsIntegration(default_function_, -1, 2, 6);

    // Expect
    EXPECT_NEAR(trapezoid, 11.27307, tolerance_);
    EXPECT_NEAR(simpson, 11.33076, tolerance_);
}

TEST_F(QuadratureTestFixture, GivenOddNumberOfIntervals_ExpectSimpsonThrow)
{
    // Given
    default_function_ = [](const double x) -> double { return 6 / (x * x + 1); };

    // Call
    const auto trapezoid = TrapezoidalIntegration(default_function_, -1, 2, 7);

    // Expect
    EXPECT_NEAR(trapezoid, 11.2947, tolerance_);
    EXPECT_ANY_THROW({ SimpsonsIntegration(default_function_, -1, 2, 7); });
}

}  // namespace
}  // namespace calculus
}  // namespace nm
