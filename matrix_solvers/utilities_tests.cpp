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

struct MatrixTransposeTestParameter
{
    Matrix<double> matrix{};
    Matrix<double> expected_transpose{};
    std::string test_name{};
};

class MatrixTransposeTestFixture : public ::testing::TestWithParam<MatrixTransposeTestParameter>
{
  public:
    double tolerance_{0.001};
};

TEST_P(MatrixTransposeTestFixture, GivenSqaureMatrices_ExpectValidTransposes)
{
    // Given
    auto param = GetParam();

    // Call
    param.matrix.TransposeInPlace();

    // Expect
    for (std::int32_t i{0}; i < static_cast<std::int32_t>(param.matrix.size()); ++i)
    {
        for (std::int32_t j{0}; j < static_cast<std::int32_t>(param.matrix.at(0).size()); ++j)
        {
            EXPECT_NEAR(param.matrix.at(i).at(j), param.expected_transpose.at(i).at(j), tolerance_);
        }
    }
}

INSTANTIATE_TEST_SUITE_P(MatrixTransposeTests,
                         MatrixTransposeTestFixture,
                         ::testing::Values(
                             // clang-format off
                         MatrixTransposeTestParameter{
                             .matrix = Matrix<double>({{3, 5}, {7, 9}}),
                             .expected_transpose = Matrix<double>({{3, 7}, {5, 9}}),
                             .test_name = "TwoByTwo",
                         },
                         MatrixTransposeTestParameter{
                             .matrix = Matrix<double>({{3, 5, 9}, {7, 9, 1}, {2, 8, 0}}),
                             .expected_transpose = Matrix<double>({{3, 7, 2}, {5, 9, 8}, {9, 1, 0}}),
                             .test_name = "ThreeByThree",
                         },
                         MatrixTransposeTestParameter{
                             .matrix = Matrix<double>({{2, 4, 9, 5}, {7, 9, 1, 0}, {2, 8, 0, 2}, {6, 6, 2, 5}}),
                             .expected_transpose = Matrix<double>({{2, 7, 2, 6}, {4, 9, 8, 6}, {9, 1, 0, 2}, {5, 0, 2, 5}}),
                             .test_name = "FourByFour",
                         }  // clang-format on
                             ),
                         [](const ::testing::TestParamInfo<MatrixTransposeTestParameter>& info) -> std::string {
                             return info.param.test_name;
                         });

TEST(AdditionOperatorTests, GivenTwoMatrices_ExpectCorrectSum)
{
    // Given
    const Matrix<double> A{{1, 1}, {1, 1}};
    const Matrix<double> B{{2, 3}, {4, 5}};
    const double tolerance = 1e-3;

    // Call
    const auto result = A + B;

    // Expect
    EXPECT_NEAR(result.at(0).at(0), 3, tolerance);
    EXPECT_NEAR(result.at(0).at(1), 4, tolerance);
    EXPECT_NEAR(result.at(1).at(0), 5, tolerance);
    EXPECT_NEAR(result.at(1).at(1), 6, tolerance);
}

TEST(AdditionOperatorTests, GivenTwoOneDimensionalMatrices_ExpectCorrectSum)
{
    // Given
    const Matrix<double> A{{1, 1, 1, 1}};
    const Matrix<double> B{{2, 3, 4, 5}};
    const double tolerance = 1e-3;

    // Call
    const auto result = A + B;

    // Expect
    EXPECT_NEAR(result.at(0).at(0), 3, tolerance);
    EXPECT_NEAR(result.at(0).at(1), 4, tolerance);
    EXPECT_NEAR(result.at(0).at(2), 5, tolerance);
    EXPECT_NEAR(result.at(0).at(3), 6, tolerance);
}

TEST(DevectorizeTests, GivenVectorAndColumnHeight_ExpectCorrectMatrix)
{
    // Given
    const std::vector<double> B{{2, 3, 4, 5}};
    const double tolerance = 1e-3;

    // Call
    const auto result = Devectorize(B, 2);
    PrintMatrix(result);

    // Expect
    EXPECT_NEAR(result.at(0).at(0), 2, tolerance);
    EXPECT_NEAR(result.at(0).at(1), 4, tolerance);
    EXPECT_NEAR(result.at(1).at(0), 3, tolerance);
    EXPECT_NEAR(result.at(1).at(1), 5, tolerance);
}

}  // namespace

}  // namespace matrix

}  // namespace nm
