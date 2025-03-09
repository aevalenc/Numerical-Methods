/*
 * Author: Alejandro Valencia
 * Update: March, 9 2025
 */

#include "calculus/data_types/data_types.h"
#include <gtest/gtest.h>
#include <string>

namespace nm
{
namespace calculus
{

namespace
{

struct DualNumberTestParameter
{
    DualNumber first{1.0, 1.0};
    DualNumber second{2.0, 2.0};
    DualNumber expected_value{3.0, 3.0};
    std::string operation{"+"};
};

class DualNumberTestFixture : public ::testing::TestWithParam<DualNumberTestParameter>
{
  protected:
    const double tolerance_{1e-3};
};

TEST_P(DualNumberTestFixture, DualNumberTest)
{
    const auto& param = GetParam();
    DualNumber result{};

    if (param.operation == "+")
    {
        result = param.first + param.second;
    }
    else if (param.operation == "-")
    {
        result = param.first - param.second;
    }
    else if (param.operation == "*")
    {
        result = param.first * param.second;
    }
    else if (param.operation == "/")
    {
        result = param.first / param.second;
    }

    EXPECT_NEAR(result.real, param.expected_value.real, tolerance_);
    EXPECT_NEAR(result.dual, param.expected_value.dual, tolerance_);
}

INSTANTIATE_TEST_SUITE_P(
    DualNumberTest,
    DualNumberTestFixture,
    ::testing::Values(
        DualNumberTestParameter{DualNumber{1.0, 1.0}, DualNumber{2.0, 2.0}, DualNumber{3.0, 3.0}, "+"},
        DualNumberTestParameter{DualNumber{1.0, 1.0}, DualNumber{2.0, 2.0}, DualNumber{-1.0, -1.0}, "-"},
        DualNumberTestParameter{DualNumber{1.0, 1.0}, DualNumber{2.0, 2.0}, DualNumber{2.0, 4.0}, "*"},
        DualNumberTestParameter{DualNumber{1.0, 1.0}, DualNumber{2.0, 2.0}, DualNumber{0.5, 0.0}, "/"},
        DualNumberTestParameter{DualNumber{2.0, 4.0}, DualNumber{7.0, -3.0}, DualNumber{2.0 / 7.0, 34.0 / 49.0}, "/"}));

}  // namespace

}  // namespace calculus
}  // namespace nm
