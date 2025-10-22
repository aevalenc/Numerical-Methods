/*
 * Author : Alejandro Valencia
 * Project: Generalized Secant Method for Systems of Nonlinear Equations - main unit tests
 * Update : October 22nd, 2025
 */

#include "root_finders/secant_method/multivar_secant_method.h"
#include <cstdint>
#include <gtest/gtest.h>

namespace nm
{
namespace root_finders
{
namespace
{

struct MultiVarSecantMethodTestParameter
{
    std::vector<std::function<double(std::vector<double>)>> equations{};
    std::vector<std::vector<double>> arguments{};
    std::vector<double> expected_values;
    double algorithm_tolerance{1e-6};
    std::int32_t max_iterations{1000};
    std::string test_name{"TEST"};
};

class MultiVarSecantMethodTestFixture : public ::testing::TestWithParam<MultiVarSecantMethodTestParameter>
{
  public:
    const double expectation_tolerance_{0.001};
};

TEST_P(MultiVarSecantMethodTestFixture, GivenValidInputs_ExpectValidOutput)
{
    // Given
    const auto& param = GetParam();

    // Call
    const auto result =
        MultiVarSecantMethod(param.equations, param.arguments, param.algorithm_tolerance, param.max_iterations);

    // Expect
    for (std::int32_t i{0}; i < static_cast<std::int32_t>(result.size()); ++i)
    {
        EXPECT_NEAR(result.at(i), param.expected_values.at(i), expectation_tolerance_);
    }
}

INSTANTIATE_TEST_SUITE_P(SecantMethodTests,
                         MultiVarSecantMethodTestFixture,
                         ::testing::Values(
                             MultiVarSecantMethodTestParameter{
                                 {[](std::vector<double> x) -> double { return x.at(0) * x.at(0) - x.at(1) - 1; },
                                  [](std::vector<double> x) -> double { return x.at(0) - x.at(1) * x.at(1) + 1; }},
                                 {{1.0, 1.0}, {1.0, 2.0}, {1.5, 2.0}},
                                 {1.618, 1.618},
                                 1e-6,
                                 100,
                                 "WithStartingValuesInFirstQuadrant"},
                             MultiVarSecantMethodTestParameter{
                                 {[](std::vector<double> x) -> double { return x.at(0) * x.at(0) - x.at(1) - 1; },
                                  [](std::vector<double> x) -> double { return x.at(0) - x.at(1) * x.at(1) + 1; }},
                                 {{-1.0, -1.0}, {-1.0, -2.0}, {-1.5, -2.0}},
                                 {-0.618, -0.618},
                                 1e-6,
                                 100,
                                 "WithStartingValuesInSecondQuadrant"},
                             MultiVarSecantMethodTestParameter{
                                 {[](std::vector<double> x) -> double { return x.at(0) * x.at(0) - x.at(1) - 1; },
                                  [](std::vector<double> x) -> double { return x.at(0) - x.at(1) * x.at(1) + 1; }},
                                 {{-1.0, 1.0}, {-1.0, 2.0}, {-1.5, 2.0}},
                                 {-1.0, 0.0},
                                 1e-6,
                                 100,
                                 "WithStartingValuesInThirdQuadrant"},
                             MultiVarSecantMethodTestParameter{
                                 {[](std::vector<double> x) -> double { return x.at(0) * x.at(0) - x.at(1) - 1; },
                                  [](std::vector<double> x) -> double { return x.at(0) - x.at(1) * x.at(1) + 1; }},
                                 {{1.0, -1.0}, {1.0, -2.0}, {1.5, -2.0}},
                                 {0.0, -1.0},
                                 1e-6,
                                 100,
                                 "WithStartingValuesInFourthQuadrant"}),
                         [](const ::testing::TestParamInfo<MultiVarSecantMethodTestParameter>& info) {
                             return info.param.test_name;
                         });

}  // namespace
}  // namespace root_finders
}  // namespace nm
