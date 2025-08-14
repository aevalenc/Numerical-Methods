/*
 * Tests for Quadrature Based Numerical Integration Methods
 *
 * Author: Alejandro Valencia
 * Update: August 14, 2025
 *
 */

#include "calculus/integration/trapezoidal_method/trapezoidal_method.h"
#include "gtest/gtest.h"

namespace nm
{
namespace calculus
{
struct QuadratureTestParameter
{
    double a{};
    double b{};
    double n{};
    double expected_value{};
};

namespace
{

class QuadratureTestFixture : public ::testing::Test
{

  public:
    void SetDefaultExponentialFunction()
    {
        default_function_ = [](double x) { return std::exp(x); };
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

}  // namespace
}  // namespace calculus
}  // namespace nm
