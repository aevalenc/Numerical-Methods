/*
 * Author: Alejandro Valencia
 * Update: August 26, 2025
 */

#include "matrix_solvers/operations/operations.h"
#include "matrix_solvers/utilities.h"
#include "matrix_solvers/utilities_tests.h"
#include <gtest/gtest.h>
#include <vector>

namespace nm
{

namespace matrix
{

namespace
{

class MatrixOperationsBaseTestFixture : public ::testing::Test
{
  public:
    Matrix<double> A_{};
    Matrix<double> B_{};
    Matrix<double> C_{};
    double tolerance_{0.001};
};

class MatrixOperationKroneckerProductTestFixture : public MatrixOperationsBaseTestFixture
{
  public:
    void SetUp() override
    {
        A_.push_back(std::vector<double>{3.0, 5.0});
        A_.push_back(std::vector<double>{7.0, 9.0});

        B_.push_back(std::vector<double>{1.0, 9.0});
        B_.push_back(std::vector<double>{8.0, 2.0});
    }
};

TEST_F(MatrixOperationKroneckerProductTestFixture, GivenValidMatrices_ExpectExactSolution)
{
    const auto result = KroneckerProduct(A_, B_);

    EXPECT_NEAR(result.at(1).at(1), 6, tolerance_);
    EXPECT_NEAR(result.at(3).at(2), 72, tolerance_);
}

TEST_F(MatrixOperationKroneckerProductTestFixture, GivenLargerValidMatrices_ExpectExactSolution)
{
    A_ = {{1, -4, 7}, {-2, 3, 3}};
    B_ = {{8, -9, -6, 5}, {1, -3, -4, 7}, {2, 8, -8, -3}, {1, 2, -5, -1}};
    const auto result = KroneckerProduct(A_, B_);

    EXPECT_NEAR(result.at(1).at(1), -3, tolerance_);
    EXPECT_NEAR(result.at(3).at(2), -5, tolerance_);
}

TEST_F(MatrixOperationKroneckerProductTestFixture, GivenOneRectangularAndOneSquareMatrix_ExpectExactSolution)
{
    A_ = {{1, 2, 3}, {4, 5, 6}};
    B_ = {{7, 8}, {9, 10}};
    const auto result = KroneckerProduct(A_, B_);

    EXPECT_NEAR(result.at(1).at(1), 10, tolerance_);
    EXPECT_NEAR(result.at(3).at(2), 45, tolerance_);
}

class MatrixUtilitiesDotProductTestFixture : public test::MatrixUtilitiesBaseTestFixture
{

  public:
    std::vector<double> a_{1.0, 2.0, 3.0};
    std::vector<double> b_{4.0, 5.0, 6.0};
    std::vector<double> c_{4.0, 10.0, 18.0};
};

TEST_F(MatrixUtilitiesDotProductTestFixture, Given2ValidVectors_ExpectCorrectDotProductValue)
{
    // Given
    const double expected_value{32.0};

    // Call
    const auto result = Dot(a_, b_);

    // Expect
    EXPECT_NEAR(result, expected_value, tolerance_);
}

TEST_F(MatrixUtilitiesDotProductTestFixture, Given1EmptyVector_ExpectExecption)
{
    // Given
    a_.clear();

    // Call and Expect
    EXPECT_ANY_THROW(Dot(a_, b_));

    // Given
    b_.clear();

    // Call and Expect
    EXPECT_ANY_THROW(Dot(c_, b_));
}

TEST_F(MatrixUtilitiesDotProductTestFixture, Given1VectorShorterThanTheOther_ExpectExecption)
{
    // Given
    a_.resize(1);

    // Call and Expect
    EXPECT_ANY_THROW(Dot(a_, b_));
}

class ResidualTestFixture : public test::MatrixUtilitiesBaseTestFixture
{

  public:
    std::vector<double> b_{4.0, 5.0, 6.0};
    std::vector<double> expected_result_{4.0, 5.0, 6.0};
};

TEST_F(ResidualTestFixture, GivenValidMatrixEquation_ExpectValidResidual)
{
    // Given
    const std::int32_t n{3};
    std::vector<double> x{0.0, 0.0, 0.0};
    A_.resize(n);

    // Call and Expect
    const auto result = CalculateResidual(A_, b_, x, n);

    // Expect
    for (std::int32_t i{0}; i < n; ++i)
    {
        EXPECT_NEAR(result.at(i), expected_result_.at(i), tolerance_);
    }
}

class MatrixMultiplicationTestFixture : public test::MatrixUtilitiesBaseTestFixture
{
};

TEST_F(MatrixMultiplicationTestFixture, GivenInvalidMatrix_ExpectException)
{
    A_.clear();

    // Call & Expect
    EXPECT_ANY_THROW({
        try
        {
            const auto result = MatMult(A_, B_);
        }
        catch (const std::exception& exception)
        {
            throw;
        }
    });
}

TEST_F(MatrixMultiplicationTestFixture, GivenInvalidMatricesForMultiplication_ExpectException)
{
    // Given
    std::vector<double> b = {1, 2, 3};

    // Call & Expect
    EXPECT_ANY_THROW({
        try
        {
            const auto result = MatMult(A_, b);
        }
        catch (const std::exception& exception)
        {
            throw;
        }
    });
}

TEST_F(MatrixMultiplicationTestFixture, GivenValidMatrices_ExpectExactSolution)
{
    const auto m = static_cast<std::int32_t>(A_.size());
    const auto p = static_cast<std::int32_t>(B_.at(0).size());
    const auto C = MatMult(A_, B_);

    for (std::int32_t i = 0; i < m; ++i)
    {
        for (std::int32_t j = 0; j < p; ++j)
        {
            EXPECT_NEAR(C.at(i).at(j), C_.at(i).at(j), tolerance_);
        }
    }
}

TEST_F(MatrixMultiplicationTestFixture, GivenOneMatrixAndOneVector_ExpectExactSolution)
{
    const std::vector<double> b = {1, 2, 3};
    const std::vector<double> C_expected = {8, 11, 14};

    const auto n = static_cast<std::int32_t>(b.size());
    const auto C = MatMult(B_, b);

    for (std::int32_t i = 0; i < n; ++i)
    {

        EXPECT_NEAR(C.at(i), C_expected.at(i), tolerance_);
    }
}

TEST(QRDecompositionTests, GivenValidSquareMatrix_ExpectCorrectDecomposition)
{
    // Given
    const Matrix<double> A = {{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}};

    // Call
    const auto qr_pair = QRDecompositionGramSchmidt(A);

    // Expect
    EXPECT_NEAR(qr_pair.first.at(0).at(0), 6.0 / 7.0, 0.001);
    EXPECT_NEAR(qr_pair.first.at(1).at(0), 3.0 / 7.0, 0.001);
    EXPECT_NEAR(qr_pair.first.at(2).at(0), -2.0 / 7.0, 0.001);
    EXPECT_NEAR(qr_pair.second.at(0).at(0), 14.0, 0.001);
    EXPECT_NEAR(qr_pair.second.at(0).at(1), 21.0, 0.001);
    EXPECT_NEAR(qr_pair.second.at(0).at(2), -14.0, 0.001);
    EXPECT_NEAR(qr_pair.second.at(1).at(0), 0.0, 0.001);
    EXPECT_NEAR(qr_pair.second.at(1).at(1), 175.0, 0.001);
    EXPECT_NEAR(qr_pair.second.at(1).at(2), -70.0, 0.001);
    EXPECT_NEAR(qr_pair.second.at(2).at(0), 0.0, 0.001);
    EXPECT_NEAR(qr_pair.second.at(2).at(1), 0.0, 0.001);
    EXPECT_NEAR(qr_pair.second.at(2).at(2), 35.0, 0.001);
}

}  // namespace

}  // namespace matrix

}  // namespace nm
