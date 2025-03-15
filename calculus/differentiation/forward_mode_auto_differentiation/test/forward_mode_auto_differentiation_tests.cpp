/*
 * Author: Alejandro Valencia
 * Update: March, 9 2025
 */

#include "calculus/data_types/data_types.h"
#include "calculus/differentiation/forward_mode_auto_differentiation/forward_mode_auto_differentiation.h"
#include <functional>
#include <gtest/gtest.h>
#include <string>

namespace nm
{
namespace calculus
{

namespace
{

struct ForwardModeAutoDifferentiationParam
{
    std::function<DualNumber(const DualNumber&)> func{};
    double x{};
    double expected_value{};
    std::string test_name{};
};

class DualNumberTestFixture : public ::testing::TestWithParam<ForwardModeAutoDifferentiationParam>
{
  protected:
    const double tolerance_{1e-3};
};

TEST_P(DualNumberTestFixture, DualNumberTest)
{
    const auto& param = GetParam();
    const auto result = ForwardModeAutoDifferentiation(param.func, param.x);

    EXPECT_NEAR(result, param.expected_value, tolerance_);
    EXPECT_NEAR(result, param.expected_value, tolerance_);
}

INSTANTIATE_TEST_SUITE_P(
    DualNumberTest,
    DualNumberTestFixture,
    ::testing::Values(
        ForwardModeAutoDifferentiationParam{[](const DualNumber& x) { return x; },
                                            1.0,
                                            1.0,
                                            "GivenLinearFunctionReturnsOne"},
        ForwardModeAutoDifferentiationParam{[](const DualNumber& x) { return x; },
                                            4.0,
                                            1.0,
                                            "GivenLinearFunctionAndOtherValueReturnsOne"},
        ForwardModeAutoDifferentiationParam{[](const DualNumber& x) { return x * x; }, 2.0, 4.0, "Square"},
        ForwardModeAutoDifferentiationParam{[](const DualNumber& x) { return x * x * x; }, 2.0, 12.0, "Cube"}),
    [](const testing::TestParamInfo<ForwardModeAutoDifferentiationParam>& info) { return info.param.test_name; });

}  // namespace

}  // namespace calculus
}  // namespace nm
