/*
 * Author : Alejandro Valencia
 * Project: Jacobi - main unit tests
 */

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
    double tolerance_{0.001};
    double residual{0.0};
    double max_iterations{10};
};

TEST_F(JacobiMethodTestFixture, GivenValidMatrix_ExpectConvergedSolution)
{
    std::vector<double> x{0.0, 0.0, 0.0};
    for (std::size_t iteration = 0; iteration < max_iterations; ++iteration)
    {
        residual = jacobi(A, b, x);
    }
    EXPECT_NEAR(residual, 0.0, tolerance_);
}

}  // namespace

}  // namespace matrix

}  // namespace nm
