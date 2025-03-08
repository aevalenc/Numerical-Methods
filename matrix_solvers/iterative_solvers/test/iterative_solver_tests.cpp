/*
 * Author : Alejandro Valencia
 * Project: Jacobi - main unit tests
 */

#include "matrix_solvers/iterative_solvers/conjugate_gradient.h"
#include "matrix_solvers/iterative_solvers/gauss_seidel.h"
#include "matrix_solvers/iterative_solvers/jacobi.h"
#include "matrix_solvers/utilities.h"
#include <gtest/gtest.h>

namespace nm
{

namespace matrix
{

namespace
{

class IterativeSolversBaseTestFixture : public ::testing::Test
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
    Matrix<double> A{};
    std::vector<double> b{};
    std::vector<double> x{0.0, 0.0, 0.0};
    double tolerance_{0.001};
    double max_iterations_{1000};
};

class JacobiMethodTestFixture : public IterativeSolversBaseTestFixture
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

class GaussSeidelTestFixture : public IterativeSolversBaseTestFixture
{
};

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

class ConjugateGradientTestFixture : public IterativeSolversBaseTestFixture
{
  public:
    void SetUp() override
    {
        A_.push_back(std::vector<double>{4.0, 1.0});
        A_.push_back(std::vector<double>{1.0, 3.0});

        b_.push_back(1);
        b_.push_back(2);

        x.resize(2);

        max_iterations_ = 10;
    }

  public:
    Matrix<double> A_{};
    std::vector<double> b_{};
    std::vector<double> x_expected_{0.0909, 0.6364};
};

TEST_F(ConjugateGradientTestFixture, GivenValidMatrix_ExpectConvergedSolutionWithinDefaultValues)
{
    // Given
    const auto n = static_cast<std::int32_t>(b_.size());
    std::vector<double> x{0.0, 0.0};

    // Call
    ConjugateGradient(A_, b_, x);

    // Expect
    for (std::int32_t i{0}; i < n; ++i)
    {
        EXPECT_NEAR(x.at(i), x_expected_.at(i), tolerance_);
    }
}

TEST_F(ConjugateGradientTestFixture, GivenValidMatrix_ExpectConvergedSolutionWithinSetValues)
{
    // Given
    const auto n = static_cast<std::int32_t>(b_.size());
    std::vector<double> x{0.0, 0.0};

    // When
    const double tolerance{0.0001};
    const std::int32_t max_iterations{100};

    // Call
    ConjugateGradient(A_, b_, x, tolerance, max_iterations);

    // Expect
    for (std::int32_t i{0}; i < n; ++i)
    {
        EXPECT_NEAR(x.at(i), x_expected_.at(i), tolerance_);
    }
}

TEST_F(ConjugateGradientTestFixture, GivenValidMatrix_ExpectUnConvergedSolutionWithLowMaxIterations)
{
    // Given
    const auto n = static_cast<std::int32_t>(b_.size());
    std::vector<double> x{0.0, 0.0};

    // When
    const std::int32_t max_iterations{5};

    // Call
    ConjugateGradient(A_, b_, x, tolerance_, max_iterations);

    // Expect
    x_expected_ = {0.104, 0.625};
    for (std::int32_t i{0}; i < n; ++i)
    {
        EXPECT_NEAR(x.at(i), x_expected_.at(i), tolerance_);
    }
}

}  // namespace

}  // namespace matrix

}  // namespace nm
