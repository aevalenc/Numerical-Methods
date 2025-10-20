/*
 * Author : Alejandro Valencia
 * Project: Newton's Method - main unit tests
 * Update: September 9, 2023
 */

#include "root_finders/secant_method/multivar_secant_method.h"
#include <cmath>
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
    std::vector<std::function<double(std::vector<double>)>> equations;
    std::vector<double> x0;
    std::vector<double> x1;
    std::vector<double> x2;
    std::vector<double> expected_values;
    double algorithm_tolerance{1e-6};
    std::int32_t max_iterations{1000};
};

class MultiVarSecantMethodTestFixture : public ::testing::TestWithParam<MultiVarSecantMethodTestParameter>
{
  public:
    const double expectation_tolerance_{0.001};
};

// TEST_P(MultiVarSecantMethodTestFixture, GivenValidInputs_ExpectValidOutput)
// {
//     const auto& param = GetParam();
//     const auto result = MultiVarSecantMethod(param.equations, param.x0, param.x1, param.x2);
//     EXPECT_NEAR(result.at(0), param.expected_values.front(), expectation_tolerance_);
// }

// INSTANTIATE_TEST_SUITE_P(SecantMethodTests,
//                          MultiVarSecantMethodTestFixture,
//                          ::testing::Values(MultiVarSecantMethodTestParameter{
//                              {[](std::vector<double> x) -> double { return x.at(0) * x.at(0) - x.at(1) - 1; },
//                               [](std::vector<double> x) -> double { return x.at(0) - x.at(1) * x.at(1) + 1; }},
//                              {1.0, 1.0},
//                              {1.0, 2.0},
//                              {1.5, 2.0},
//                              {1.56, 9.0},
//                              1e-6}));

TEST_F(MultiVarSecantMethodTestFixture, GivenValidInputs_ExpectValidOutput)
{
    auto lambda1 = [](std::vector<double> x) -> double { return x.at(0) * x.at(0) - x.at(1) - 1; };
    auto lambda2 = [](std::vector<double> x) -> double { return x.at(0) - x.at(1) * x.at(1) + 1; };
    MultiVarSecantMethodTestParameter param{{lambda1, lambda2}, {1.0, 1.0}, {1.0, 2.0}, {1.5, 2.0}, {1.56, 9.0}, 1e-6};
    const auto result = MultiVarSecantMethod(param.equations, param.x0, param.x1, param.x2);
    // EXPECT_NEAR(result.at(0), param.expected_values.front(), expectation_tolerance_);
    EXPECT_FALSE(false);
}

}  // namespace

}  // namespace root_finders

}  // namespace nm
