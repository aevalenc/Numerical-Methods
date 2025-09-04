/*
 * Author : Alejandro Valencia
 * Project: Backwards Substitution - main unit tests
 */

#include "matrix_solvers/direct_solvers/backwards_substitution.h"
#include "matrix_solvers/direct_solvers/forward_substitution.h"
#include "matrix_solvers/direct_solvers/lu_solve.h"
#include "matrix_solvers/operations/operations.h"
#include "matrix_solvers/utilities.h"
#include <cstdint>
#include <gtest/gtest.h>

namespace nm
{

namespace matrix
{

namespace
{

class DirectSolverBaseTestFixture : public ::testing::Test
{
  public:
    void SetUp() override
    {
        A_.push_back(std::vector<double>{1.0, -2.0, 1.0});
        A_.push_back(std::vector<double>{0.0, 1.0, 6.0});
        A_.push_back(std::vector<double>{0.0, 0.0, 1.0});

        b_.push_back(4);
        b_.push_back(-1);
        b_.push_back(2);
    }

  public:
    std::vector<double> b_{};
    Matrix<double> A_{};
    std::vector<double> x_{0.0, 0.0, 0.0};
    double tolerance_{0.001};
};

class BackwardsSubstitutionTestFixture : public DirectSolverBaseTestFixture
{
};

TEST_F(BackwardsSubstitutionTestFixture, GivenUpperTriangularMatrix_ExpectExactSolution)
{

    const auto x = BackwardsSubstitution(A_, b_);
    // const auto tol = 0.001;

    EXPECT_NEAR(x[0], -24.0, tolerance_);
    EXPECT_NEAR(x[1], -13.0, tolerance_);
    EXPECT_NEAR(x[2], 2.0, tolerance_);
}

class ForwardSubstitutionTestFixture : public DirectSolverBaseTestFixture
{
  public:
    void SetUpForwardSubstitution()
    {
        L_.push_back(std::vector<double>{1, 0, 0});
        L_.push_back(std::vector<double>{-2, 1, 0});
        L_.push_back(std::vector<double>{-2, -1, 1});
        b_.at(0) = 1;
        b_.at(1) = 2;
        b_.at(2) = 3;

        x_expected_.push_back(1);
        x_expected_.push_back(4);
        x_expected_.push_back(9);
    }

  public:
    Matrix<double> L_{};
    std::vector<double> x_expected_{};
};

TEST_F(ForwardSubstitutionTestFixture, GivenLowerTriangularMatrix_ExpectExactSolution)
{
    // Given
    SetUpForwardSubstitution();

    // Call
    const auto x = ForwardSubstitution(L_, b_);

    // Expect
    for (std::size_t i{0}; i < b_.size(); ++i)
    {
        EXPECT_NEAR(x.at(i), x_expected_.at(i), tolerance_);
    }
}

class LUSolverTestFixture : public DirectSolverBaseTestFixture
{
  public:
    void SetUpLUSolve()
    {
        AA_.push_back(std::vector<double>{1, 1, 1});
        AA_.push_back(std::vector<double>{0, 2, 5});
        AA_.push_back(std::vector<double>{2, 5, -1});
        b_.at(0) = 6;
        b_.at(1) = -4;
        b_.at(2) = 27;

        x_expected_.push_back(5);
        x_expected_.push_back(3);
        x_expected_.push_back(-2);
    }

  public:
    Matrix<double> AA_{};
    std::vector<double> x_expected_{};
};

TEST_F(LUSolverTestFixture, GivenStandardMatrixEq_ExpectExactSolution)
{
    // Given
    SetUpLUSolve();

    // Call
    const auto x = LUSolve(AA_, b_);

    // Expect
    for (std::size_t i{0}; i < b_.size(); ++i)
    {
        EXPECT_NEAR(x.at(i), x_expected_.at(i), tolerance_);
    }
}

TEST(MatrixEquationTests, GivenSqaureMatrices_ExpectCorrectResult)
{
    // Given
    Matrix<double> A({{3, 5}, {7, 9}});
    Matrix<double> B({{1, 8}, {9, 2}});
    Matrix<double> C({{3, 4}, {1, 6}});
    const double tolerance{0.001};

    // Construct
    B.TransposeInPlace();
    const auto AA = KroneckerProduct(B, A);
    const auto C_vectorized = Vectorize(C);
    std::vector<double> x(C_vectorized.size(), 1.0);

    // Call
    const auto result = LUSolve(AA, C_vectorized);

    // Expect
    EXPECT_NEAR(result.at(0), -0.0179, tolerance);
    EXPECT_NEAR(result.at(1), 0.0964, tolerance);
    EXPECT_NEAR(result.at(2), -0.3036, tolerance);
    EXPECT_NEAR(result.at(3), 0.2393, tolerance);
}

}  // namespace

}  // namespace matrix

}  // namespace nm
