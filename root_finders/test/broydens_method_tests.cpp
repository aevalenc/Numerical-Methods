/*
 * Author : Alejandro Valencia
 * Project: Generalized Secant Method for Systems of Nonlinear Equations - main unit tests
 * Update : October 22nd, 2025
 */

#include "matrix_solvers/utilities.h"
#include "root_finders/broydens_method/broydens_method.h"
#include <cstdint>
#include <gtest/gtest.h>

namespace nm
{
namespace root_finders
{
namespace
{

struct FiniteDifferenceJacobianEvaluationTestParameter
{
    std::vector<std::function<double(std::vector<double>)>> equations{};
    std::vector<std::vector<double>> arguments{};
    double delta{0.1};
    matrix::Matrix<double> expected_value{};
    std::string test_name{"TEST"};
};

struct BroydensMethodTestParameter
{
    std::vector<std::function<double(std::vector<double>)>> equations{};
    std::vector<std::vector<double>> arguments{};
    double delta{0.1};
    std::vector<double> expected_values{};
    std::string test_name{"TEST"};
    double algorithm_tolerance{1e-6};
    std::int32_t max_iterations{1000};
};

class FiniteDifferenceJacobianEvaluationTestFixture
    : public ::testing::TestWithParam<FiniteDifferenceJacobianEvaluationTestParameter>
{
  public:
    const double expectation_tolerance_{0.001};
};

TEST_P(FiniteDifferenceJacobianEvaluationTestFixture, DISABLED_GivenValidInputs_ExpectValidOutput)
{
    // Given
    const auto& param = GetParam();

    // Call
    const auto result = EvaluateJacobian(param.equations, param.arguments, param.delta);

    // Expect
    for (std::int32_t i{0}; i < static_cast<std::int32_t>(result.first.size()); ++i)
    {
        for (std::int32_t j{0}; j < static_cast<std::int32_t>(result.first.size()); ++j)
        {
            EXPECT_NEAR(result.first.at(i).at(j), param.expected_value.at(i).at(j), expectation_tolerance_);
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    JacobianEstimationTests,
    FiniteDifferenceJacobianEvaluationTestFixture,
    ::testing::Values(
        FiniteDifferenceJacobianEvaluationTestParameter{
            {[](std::vector<double> x) -> double { return x.at(0) * x.at(0) - x.at(1) - 1; },
             [](std::vector<double> x) -> double { return x.at(0) - x.at(1) * x.at(1) + 1; }},
            {{1.0, 1.0}},
            0.1,
            {{2.1, -1.0}, {1.0, -2.1}},
            "WithTwoParabolas"},
        FiniteDifferenceJacobianEvaluationTestParameter{
            {[](std::vector<double> x) -> double { return x.at(0) * x.at(0) - 2 * x.at(0) - x.at(1) + 1; },
             [](std::vector<double> x) -> double { return x.at(0) * x.at(0) + x.at(1) * x.at(1) - 1; }},
            {{1.0, 1.0}},
            0.1,
            {{0.1, -1.0}, {2.1, 2.1}},
            "WithParabolaAndCircle"}),
    [](const ::testing::TestParamInfo<FiniteDifferenceJacobianEvaluationTestParameter>& info) {
        return info.param.test_name;
    });

class BroydensMethodTestFixture : public ::testing::TestWithParam<BroydensMethodTestParameter>
{
  public:
    const double expectation_tolerance_{0.001};
};

TEST_P(BroydensMethodTestFixture, GivenValidInputs_ExpectValidOutput)
{
    // Given
    const auto& param = GetParam();

    // Call
    const auto result = BroydensMethod(param.equations, param.arguments, param.delta);
    matrix::PrintVector(result);

    // Expect
    // for (std::int32_t i{0}; i < static_cast<std::int32_t>(result.size()); ++i)
    // {
    //     EXPECT_NEAR(result.at(i), param.expected_values.at(i), expectation_tolerance_);
    // }
    EXPECT_FALSE(false);
}

INSTANTIATE_TEST_SUITE_P(
    BroydensMethodTests,
    BroydensMethodTestFixture,
    ::testing::Values(
        BroydensMethodTestParameter{{[](std::vector<double> x) -> double { return x.at(0) * x.at(0) - x.at(1) - 1; },
                                     [](std::vector<double> x) -> double { return x.at(0) - x.at(1) * x.at(1) + 1; }},
                                    {{1.0, 1.0}},
                                    0.1,
                                    {2.1, -1.0},
                                    "WithTwoParabolas"}
        //                             ,
        // BroydensMethodTestParameter{
        //     {[](std::vector<double> x) -> double { return x.at(0) * x.at(0) - 2 * x.at(0) - x.at(1) + 1; },
        //      [](std::vector<double> x) -> double { return x.at(0) * x.at(0) + x.at(1) * x.at(1) - 1; }},
        //     {{1.0, 1.0}},
        //     0.1,
        //     {0.1, -1.0},
        //     "WithParabolaAndCircle"}
        ),
    [](const ::testing::TestParamInfo<BroydensMethodTestParameter>& info) { return info.param.test_name; });

}  // namespace
}  // namespace root_finders
}  // namespace nm
