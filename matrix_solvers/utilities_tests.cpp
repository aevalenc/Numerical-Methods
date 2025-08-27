/*
 * Matrix utilities tests
 *
 * Author: Alejandro Valencia
 * Update: August 27, 2025
 */

#include "matrix_solvers/utilities_tests.h"
#include "matrix_solvers/utilities.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

namespace nm
{

namespace matrix
{

namespace
{

class MatrixUtilitiesTestFixture : public test::MatrixUtilitiesBaseTestFixture
{
};

TEST_F(MatrixUtilitiesTestFixture, GivenValidSizeForMatrix_ExpectValidIdentityMatrix)
{
    // Given
    const std::int32_t size{3};

    Matrix<double> expected_identity_matrix{};
    expected_identity_matrix.push_back(std::vector<double>{1.0, 0.0, 0.0});
    expected_identity_matrix.push_back(std::vector<double>{0.0, 1.0, 0.0});
    expected_identity_matrix.push_back(std::vector<double>{0.0, 0.0, 1.0});

    // Call
    const auto identity_matrix = CreateIdentityMatrix<double>(size);

    for (std::int32_t i = 0; i < size; ++i)
    {
        for (std::int32_t j = 0; j < size; ++j)
        {
            EXPECT_NEAR(identity_matrix.at(i).at(j), expected_identity_matrix.at(i).at(j), tolerance_);
        }
    }
}

TEST_F(MatrixUtilitiesTestFixture, GivenSizeOneForMatrix_ExpectValidIdentityMatrix)
{
    // Given
    const std::int32_t size{1};

    Matrix<double> expected_identity_matrix{};
    expected_identity_matrix.push_back(std::vector<double>{1.0});

    // Call
    const auto identity_matrix = CreateIdentityMatrix<double>(size);

    for (std::int32_t i = 0; i < size; ++i)
    {
        for (std::int32_t j = 0; j < size; ++j)
        {
            EXPECT_NEAR(identity_matrix.at(i).at(j), expected_identity_matrix.at(i).at(j), tolerance_);
        }
    }
}

TEST_F(MatrixUtilitiesTestFixture, GivenSizeOfZeroForMatrix_ExpectExecption)
{
    // Given
    const std::int32_t size{0};

    const Matrix<double> expected_identity_matrix{};

    // Call and Expect
    EXPECT_ANY_THROW(CreateIdentityMatrix<double>(size););
}

TEST_F(MatrixUtilitiesTestFixture, GivenMatrix_ExpectValidVectorization)
{
    // Call
    const auto result = Vectorize(A_);

    // Expect
    std::vector<double> expected_result{1, 2, 0, 1, 0, 1, 1, 1, 1, 1, 1, 2};

    EXPECT_EQ(result.size(), expected_result.size());
    for (std::int32_t i{0}; i < static_cast<std::int32_t>(expected_result.size()); ++i)
    {
        EXPECT_NEAR(result.at(i), expected_result.at(i), tolerance_);
    }
}

}  // namespace

}  // namespace matrix

}  // namespace nm
