/*
 * Author : Alejandro Valencia
 * Project: Jacobi - main unit tests
 */

#include "matrix_solvers/iterative_solvers/gauss_seidel.h"
#include "matrix_solvers/iterative_solvers/jacobi.h"
#include <gtest/gtest.h>

namespace nm
{

namespace matrix
{

namespace
{

class JacobiMethodTestFixture : public ::testing::Test
{
    void SetUp() override
    {
        A.push_back(std::vector<double>{1.0, -2.0, 1.0});
        A.push_back(std::vector<double>{0.0, 1.0, 6.0});
        A.push_back(std::vector<double>{0.0, 0.0, 1.0});

        b.push_back(4);
        b.push_back(-1);
        b.push_back(2);
    }

  public:
    std::vector<double> b{};
    std::vector<std::vector<double>> A{};
    std::vector<double> x{0.0, 0.0, 0.0};
    double tolerance_{0.001};
    double max_iterations_{1000};
};

class GaussSeidelTestFixture : public JacobiMethodTestFixture
{
};

TEST_F(JacobiMethodTestFixture, GivenValidMatrix_ExpectConvergedSolution)
{
    double residual{0.0};
    for (std::size_t iteration = 0; iteration < max_iterations_; ++iteration)
    {
        residual = jacobi(A, b, x);
    }
    EXPECT_NEAR(residual, 0.0, tolerance_);
}

TEST_F(JacobiMethodTestFixture, GivenValidMatrix_ExpectConvergedSolutionWithVoidFunction)
{
    jacobi(A, b, x, max_iterations_, tolerance_);
    EXPECT_NEAR(x.at(0), -24.0, tolerance_);
}

TEST_F(JacobiMethodTestFixture, GivenValidMatrix_ExpectSingleIterationToMatchWithVoidImplementation)
{
    auto x_void = x;

    for (std::size_t iteration = 0; iteration < max_iterations_; ++iteration)
    {
        std::ignore = jacobi(A, b, x);
    }

    jacobi(A, b, x_void, max_iterations_, tolerance_);
    EXPECT_NEAR(x.at(0), x_void.at(0), tolerance_);
}

TEST_F(GaussSeidelTestFixture, GivenValidMatrix_ExpectConvergedSolution)
{
    double residual{0.0};
    for (std::size_t iteration = 0; iteration < max_iterations_; ++iteration)
    {
        residual = GaussSeidel(A, b, x);
    }
    EXPECT_NEAR(residual, 0.0, tolerance_);
}

TEST_F(GaussSeidelTestFixture, GivenValidMatrix_ExpectConvergedSolutionWithVoidFunction)
{
    GaussSeidel(A, b, x, max_iterations_, tolerance_);
    EXPECT_NEAR(x.at(0), -24.0, tolerance_);
}

TEST_F(GaussSeidelTestFixture, GivenValidMatrix_ExpectSingleIterationToMatchWithVoidImplementation)
{
    auto x_void = x;

    for (std::size_t iteration = 0; iteration < max_iterations_; ++iteration)
    {
        std::ignore = GaussSeidel(A, b, x);
    }

    GaussSeidel(A, b, x_void, max_iterations_, tolerance_);
    EXPECT_NEAR(x.at(0), x_void.at(0), tolerance_);
}

}  // namespace

}  // namespace matrix

}  // namespace nm
