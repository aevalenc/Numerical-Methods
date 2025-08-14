/*
 * Author : Alejandro Valencia
 * Project: Newton's Method - main unit tests
 * Update: September 9, 2023
 */

#include "gtest/gtest.h"
#include "root_finders/bisection_method/bisection_method.h"
#include <gtest/gtest.h>

namespace nm
{

namespace root_finders
{

namespace
{

struct BisectionMethodTestParameter
{
    std::function<double(const double)> function;
    double a;
    double b;
    double expected_value;
};

class BisectionMethodTestFixture : public ::testing::TestWithParam<BisectionMethodTestParameter>
{
  public:
    const double expectation_tolerance_{0.001};
};

TEST_P(BisectionMethodTestFixture, GivenValidInputs_ExpectValidOutput)
{
    const auto& param = GetParam();
    const auto result = BisectionMethod(param.function, param.a, param.b, expectation_tolerance_);
    EXPECT_NEAR(result, param.expected_value, expectation_tolerance_);
}

INSTANTIATE_TEST_CASE_P(
    BisectionMethodTests,
    BisectionMethodTestFixture,
    ::testing::Values(
        BisectionMethodTestParameter{[](const double x) -> double { return (x * (1.0 - x)); }, -2.0, 0.5, 0.0},
        BisectionMethodTestParameter{[](const double x) -> double { return (x * (1.0 - x)); }, 0.5, 1.5, 1.0}));

}  // namespace

}  // namespace root_finders

}  // namespace nm
