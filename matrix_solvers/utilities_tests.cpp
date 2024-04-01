/*
 * Author: Alejandro Valencia
 * Update: April 1st, 2024
 */

#include "matrix_solvers/utilities.h"
#include <gtest/gtest.h>
#include <vector>

namespace nm
{

namespace matrix
{

namespace
{

class MatrixUtilitiesBaseTestFixture : public ::testing::Test
{
    void SetUp() override
    {
        A_.push_back(std::vector<double>{1.0, 0.0, 1.0});
        A_.push_back(std::vector<double>{2.0, 1.0, 1.0});
        A_.push_back(std::vector<double>{0.0, 1.0, 1.0});
        A_.push_back(std::vector<double>{1.0, 1.0, 2.0});

        B_.push_back(std::vector<double>{1.0, 2.0, 1.0});
        B_.push_back(std::vector<double>{2.0, 3.0, 1.0});
        B_.push_back(std::vector<double>{4.0, 2.0, 2.0});

        C_.push_back(std::vector<double>{5.0, 4.0, 3.0});
        C_.push_back(std::vector<double>{8.0, 9.0, 5.0});
        C_.push_back(std::vector<double>{6.0, 5.0, 3.0});
        C_.push_back(std::vector<double>{11.0, 9.0, 6.0});
    }

  public:
    std::vector<std::vector<double>> A_{};
    std::vector<std::vector<double>> B_{};
    std::vector<std::vector<double>> C_{};
    double tolerance_{0.001};
};

class MatrixUtilitiesTestFixture : public MatrixUtilitiesBaseTestFixture
{
};

TEST_F(MatrixUtilitiesTestFixture, GivenInvalidMatrix_ExpectException)
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

TEST_F(MatrixUtilitiesTestFixture, GivenValidMatrices_ExpectExactSolution)
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

}  // namespace

}  // namespace matrix

}  // namespace nm
