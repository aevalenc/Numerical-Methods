/*
 * Author: Alejandro Valencia
 * Update: August 26, 2025
 */

#include "matrix_solvers/operations/operations.h"
#include "matrix_solvers/utilities.h"
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

    EXPECT_NEAR(result[5], 6, tolerance_);
    EXPECT_NEAR(result[14], 72, tolerance_);
}

}  // namespace

}  // namespace matrix

}  // namespace nm
