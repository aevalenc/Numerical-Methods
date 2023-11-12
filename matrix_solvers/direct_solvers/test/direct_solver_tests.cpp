/*
 * Author : Alejandro Valencia
 * Project: Backwards Substitution - main unit tests
 */

#include "matrix_solvers/direct_solvers/backwards_substitution.h"
#include "matrix_solvers/direct_solvers/doolittle.h"
#include "matrix_solvers/utilities.h"
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
    double max_iterations_{1000};
};

class BackwardsSubstitutionTestFixture : public DirectSolverBaseTestFixture
{
};

TEST_F(BackwardsSubstitutionTestFixture, GivenUpperTriangularMatrix_ExpectExactSolution)
{

    std::vector<double> b{};
    b_.push_back(4);
    b_.push_back(-1);
    b_.push_back(2);

    std::vector<double> x{0.0, 0.0, 0.0};
    BackwardsSubstitution(A_, x, b_);

    const auto tol = 0.001;
    EXPECT_NEAR(x[0], -24.0, tol);
    EXPECT_NEAR(x[1], -13.0, tol);
    EXPECT_NEAR(x[2], 2.0, tol);
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
    }

  public:
    std::vector<std::vector<double>> L_expected_{};
    std::vector<std::vector<double>> U_expected_{};
};

TEST_F(DooLittleTestFixture, GivenUpperTriangularMatrix_ExpectExactSolution)
{
    // Given
    SetUpDoolittle();

    L_expected_.push_back(std::vector<double>{1, 0, 0});
    L_expected_.push_back(std::vector<double>{-2, 1, 0});
    L_expected_.push_back(std::vector<double>{-2, -1, 1});

    U_expected_.push_back(std::vector<double>{2, -1, -2});
    U_expected_.push_back(std::vector<double>{0, 4, -1});
    U_expected_.push_back(std::vector<double>{0, 0, 3});

    // Call
    const auto LU_matrices = Doolittle(A_);

    // // Expect
    const auto L = LU_matrices.first;
    const auto U = LU_matrices.second;
    PrintMatrix(L);
    PrintMatrix(U);
    // PrintVector(L.at(0));
    // EXPECT_EQ(L.at(0), L_expected_.at(0));
}

}  // namespace

}  // namespace matrix

}  // namespace nm
