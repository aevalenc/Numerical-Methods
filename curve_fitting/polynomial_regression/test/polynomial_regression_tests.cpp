/*
 * Polynomial Regression Tests
 *
 * Author: Alejandro Valencia
 * Update: September 5th, 2025
 *
 */

#include "curve_fitting/polynomial_regression/cholesky_regression.h"
#include "matrix_solvers/utilities.h"
#include <algorithm>
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace nm
{

namespace curve_fitting
{

namespace
{

class PolynomialCurveFittingTestFixture : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        // Initialize test data
        // clang-format off
        A_ = matrix::Matrix<double>({
            {1, 0.846},
            {1, 0.654},
            {1, 0.339},
            {1, 0.315},
            {1, 0.778},
            {1, 0.838},
            {1, 0.568},
        });

        b_ = matrix::Matrix<double>({
            {0.435},
            {0.526},
            {0.980},
            {0.690},
            {0.748},
            {0.100},
            {0.449}
        });
    }
    // clang-format on

    matrix::Matrix<double> A_;
    matrix::Matrix<double> b_;
};

TEST_F(PolynomialCurveFittingTestFixture, GivenBaseCase_WithCholeskyRegression_ExpectCorrectResults)
{
    // Given expected coefficients
    const std::vector<double> expected_coefficients = {1.0825, -0.8412};

    // Call
    const auto coefficients = CholeskyRegression(A_, b_);

    // Expect
    ASSERT_EQ(coefficients.size(), expected_coefficients.size());
    for (size_t i = 0; i < coefficients.size(); ++i)
    {
        EXPECT_NEAR(coefficients.at(i), expected_coefficients.at(i), 1e-3);
    }
}

TEST_F(PolynomialCurveFittingTestFixture, GivenData_WhenDegreeIsOne_ExpectCorrectMatrix)
{
    // Given
    const auto A_transposed = A_.Transpose();

    // Call
    const auto A = ConstructVandermondeMatrix(A_transposed.at(1), 1);

    // Expect
    const auto m = static_cast<std::int32_t>(A.size());
    const auto n = static_cast<std::int32_t>(A.at(0).size());
    for (std::int32_t i{0}; i < m; ++i)
    {
        for (std::int32_t j{0}; j < n; ++j)
        {
            EXPECT_NEAR(A_.at(i).at(j), A.at(i).at(j), 1e-3);
        }
    }
}

TEST_F(PolynomialCurveFittingTestFixture, GivenData_WhenDegreeTwo_ExpectCorrectMatrix)
{
    // Given
    const auto A_transposed = A_.Transpose();
    matrix::Matrix<double> A_degree_2 = {
        A_transposed.at(0), A_transposed.at(1), {0.716, 0.428, 0.115, 0.099, 0.605, 0.702, 0.323}};

    // Call
    const auto A = ConstructVandermondeMatrix(A_transposed.at(1), 2);

    // Expect
    const auto m = static_cast<std::int32_t>(A.size());
    const auto n = static_cast<std::int32_t>(A.at(0).size());
    for (std::int32_t i{0}; i < m; ++i)
    {
        for (std::int32_t j{0}; j < n; ++j)
        {
            EXPECT_NEAR(A.at(i).at(j), A_degree_2.Transpose().at(i).at(j), 1e-3);
        }
    }
}

}  // namespace
}  // namespace curve_fitting
}  // namespace nm
