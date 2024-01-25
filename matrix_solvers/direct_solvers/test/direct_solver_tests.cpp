/*
 * Author : Alejandro Valencia
 * Project: Backwards Substitution - main unit tests
 */

#include "matrix_solvers/direct_solvers/backwards_substitution.h"
#include "matrix_solvers/direct_solvers/doolittle.h"
#include "matrix_solvers/direct_solvers/forward_substitution.h"
#include "matrix_solvers/direct_solvers/lu_solve.h"
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
    std::vector<std::vector<double>> A_{};
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

class DooLittleTestFixture : public DirectSolverBaseTestFixture
{
  public:
    void SetUpDoolittle()
    {
        std::vector<double> a1{2, -1, -2};
        std::vector<double> a2{-4, 6, 3};
        std::vector<double> a3{-4, -2, 8};
        A_.at(0).assign(a1.begin(), a1.end());
        A_.at(1).assign(a2.begin(), a2.end());
        A_.at(2).assign(a3.begin(), a3.end());

        L_expected_.push_back(std::vector<double>{1, 0, 0});
        L_expected_.push_back(std::vector<double>{-2, 1, 0});
        L_expected_.push_back(std::vector<double>{-2, -1, 1});

        U_expected_.push_back(std::vector<double>{2, -1, -2});
        U_expected_.push_back(std::vector<double>{0, 4, -1});
        U_expected_.push_back(std::vector<double>{0, 0, 3});
    }

  public:
    std::vector<std::vector<double>> L_expected_{};
    std::vector<std::vector<double>> U_expected_{};
};

TEST_F(DooLittleTestFixture, GivenUpperTriangularMatrix_ExpectExactSolution)
{
    // Given
    SetUpDoolittle();

    // Call
    const auto LU_matrices = Doolittle(A_);

    // // Expect
    const auto L = LU_matrices.first;
    const auto U = LU_matrices.second;

    for (std::ptrdiff_t i{0}; i < L.size(); ++i)
    {
        for (std::ptrdiff_t j{0}; j < L.size(); ++j)
        {
            EXPECT_NEAR(L.at(i).at(j), L_expected_.at(i).at(j), tolerance_);
            EXPECT_NEAR(U.at(i).at(j), U_expected_.at(i).at(j), tolerance_);
        }
    }
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
    std::vector<std::vector<double>> L_{};
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
    std::vector<std::vector<double>> AA_{};
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

}  // namespace

}  // namespace matrix

}  // namespace nm
