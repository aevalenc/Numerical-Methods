/*
 * Author : Alejandro Valencia
 * Project: Newton's Method - main unit tests
 * Update: September 9, 2023
 */

// #include "root_finders/newtons_method.h"
#include "newtons_method.h"
#include <cmath>
#include <gtest/gtest.h>

namespace nm
{

namespace root_finders
{

namespace
{

class NewtonsMethodTestParameter
{
  public:
};

class NewtonsMethodTestFixture : public ::testing::Test
{
  public:
    void RunTest(double x_0, const double expected_value)
    {
        auto function = [](const double x) -> double { return (x * (1.0 - x)); };
        auto derivative = [](const double x) -> double { return (1 + (-2.0 * x)); };
        const auto result = NewtonsMethod(x_0, function, derivative);
        EXPECT_NEAR(result, expected_value, expectation_tolerance_);
    }

  public:
    const double expectation_tolerance_{0.001};
};

TEST_F(NewtonsMethodTestFixture, GivenInitialGuessCloserToFirstRoot_ExpectFirstRootFound)
{
    double x_0 = 0.25;
    RunTest(x_0, 0.0);
}

TEST_F(NewtonsMethodTestFixture, GivenInitialGuessCloserToSecondRoot_ExpectSecondRootFound)
{
    double x_0 = 0.75;
    RunTest(x_0, 1.0);
}

TEST_F(NewtonsMethodTestFixture, GivenInitialGuessAtLocalMaxima_ExpectNaN)
{
    double x_0 = 0.5;
    auto function = [](const double x) -> double { return (x * (1.0 - x)); };
    auto derivative = [](const double x) -> double { return (1 + (-2.0 * x)); };
    const auto result = NewtonsMethod(x_0, function, derivative);
    std::cout << "results: " << result << "\n";
    EXPECT_TRUE(std::isnan(result));
}

}  // namespace

}  // namespace root_finders

}  // namespace nm
