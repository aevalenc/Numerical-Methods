/*
 * Author : Alejandro Valencia
 * Project: Newton's Method - main unit tests
 * Update: September 9, 2023
 */

#include "root_finders/secant_method/secant_method.h"
#include <cmath>
#include <cstdint>
#include <gtest/gtest.h>

namespace nm
{

namespace root_finders
{

namespace
{

struct SecantMethodTestParameter
{
    std::function<double(const double)> function;
    double x0;
    double x1;
    double expected_value;
    double algorithm_tolerance{1e-6};
    std::int32_t max_iterations{1000};
};

class SecantMethodTestFixture : public ::testing::TestWithParam<SecantMethodTestParameter>
{
  public:
    const double expectation_tolerance_{0.001};
};

TEST_P(SecantMethodTestFixture, GivenValidInputs_ExpectValidOutput)
{
    const auto& param = GetParam();
    const auto result = SecantMethod(param.function, param.x0, param.x1, param.algorithm_tolerance);
    EXPECT_NEAR(result, param.expected_value, expectation_tolerance_);
}

INSTANTIATE_TEST_SUITE_P(
    SecantMethodTests,
    SecantMethodTestFixture,
    ::testing::Values(
        SecantMethodTestParameter{[](const double x) -> double { return (x * (1.0 - x)); }, -2.0, 0.5, 0.0},
        SecantMethodTestParameter{[](const double x) -> double { return (x * (1.0 - x)); }, 0.5, 1.5, 1.0},
        SecantMethodTestParameter{[](const double x) -> double { return ((x * x * x) - 30 * (x * x) + 2552); },
                                  0.0,
                                  20.0,
                                  11.861501,
                                  1e-8},
        SecantMethodTestParameter{[](const double x) -> double { return 2.5 * sinh(x / 4) - 1; },
                                  -10.0,
                                  10.0,
                                  1.5601412,
                                  1e-6}));

}  // namespace

}  // namespace root_finders

}  // namespace nm
