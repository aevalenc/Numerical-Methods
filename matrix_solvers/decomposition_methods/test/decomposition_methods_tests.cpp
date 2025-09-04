/*
 * Matrix Decomposition Methods Tests
 *
 * Author: Alejandro Valencia
 * Update: September 9th, 2025
 */

#include "matrix_solvers/decomposition_methods/lu_decomposition.h"
#include "matrix_solvers/decomposition_methods/qr_decomposition.h"
#include "matrix_solvers/utilities.h"
#include <cmath>
#include <gtest/gtest.h>
#include <stdexcept>

namespace nm
{
namespace matrix
{
namespace
{
class DooLittleTestFixture : public ::testing::Test
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
    Matrix<double> A_{3, 3};
    Matrix<double> L_expected_{};
    Matrix<double> U_expected_{};
    double tolerance_{1e-3};
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

    for (std::int32_t i{0}; i < static_cast<std::int32_t>(L.size()); ++i)
    {
        for (std::int32_t j{0}; j < static_cast<std::int32_t>(L.size()); ++j)
        {
            EXPECT_NEAR(L.at(i).at(j), L_expected_.at(i).at(j), tolerance_);
            EXPECT_NEAR(U.at(i).at(j), U_expected_.at(i).at(j), tolerance_);
        }
    }
}

struct QRDecompositionTestParameter
{
    Matrix<double> input_matrix{};
    Matrix<double> expected_Q{};
    Matrix<double> expected_R{};
    std::string test_name{};
};

class QRDecompositionTestFixture : public ::testing::TestWithParam<QRDecompositionTestParameter>
{
  public:
    double tolerance_{0.001};
};

TEST_P(QRDecompositionTestFixture, GivenValidMatrix_ExpectCorrectDecomposition)
{
    // Given
    const auto& param = GetParam();
    const Matrix<double> A = param.input_matrix;
    const Matrix<double> expected_Q = param.expected_Q;
    const Matrix<double> expected_R = param.expected_R;

    // Call
    const auto qr_pair = QRDecompositionGramSchmidt(A);

    // Expect
    for (std::int32_t i{0}; i < static_cast<std::int32_t>(expected_Q.size()); ++i)
    {
        for (std::int32_t j{0}; j < static_cast<std::int32_t>(expected_Q.at(0).size()); ++j)
        {
            EXPECT_NEAR(qr_pair.first.at(i).at(j), expected_Q.at(i).at(j), tolerance_);
        }
    }
    for (std::int32_t i{0}; i < static_cast<std::int32_t>(expected_R.size()); ++i)
    {
        for (std::int32_t j{0}; j < static_cast<std::int32_t>(expected_R.at(0).size()); ++j)
        {
            EXPECT_NEAR(qr_pair.second.at(i).at(j), expected_R.at(i).at(j), tolerance_);
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    QRDecompositionTests,
    QRDecompositionTestFixture,
    ::testing::Values(
        QRDecompositionTestParameter{.input_matrix = Matrix<double>({{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}}),
                                     .expected_Q = Matrix<double>({{0.857, -0.3943, -0.3314},
                                                                   {0.4286, 0.9028, 0.0342},
                                                                   {-0.2857, 0.1714, -0.9429}}),
                                     .expected_R = Matrix<double>({{14, 21, -14}, {0, 175, -70}, {0, 0, 35}}),
                                     .test_name = "SquareMatrix"},
        QRDecompositionTestParameter{.input_matrix = {{1.0, std::sqrt(5.0)}, {2, 0}, {0, -std::sqrt(5.0)}},
                                     .expected_Q = {{1.0 / std::sqrt(5.0), 4.0 / (3.0 * std::sqrt(5.0))},
                                                    {2.0 / std::sqrt(5.0), -2.0 / (3 * std::sqrt(5.0))},
                                                    {0, -5.0 / (3 * std::sqrt(5.0))}},
                                     .expected_R = {{std::sqrt(5.0), 1.0}, {0, 3.0}},
                                     .test_name = "ThreeByTwo"}),
    [](const ::testing::TestParamInfo<QRDecompositionTestParameter>& info) { return info.param.test_name; });

struct CholeskyDecompositionTestParameter
{
    Matrix<double> input_matrix{};
    Matrix<double> expected_G{};
    std::string test_name{};
};

class CholeskyDecompositionTestFixture : public ::testing::TestWithParam<CholeskyDecompositionTestParameter>
{
  public:
    double tolerance_{0.001};
};

TEST_P(CholeskyDecompositionTestFixture, GivenValidMatrix_ExpectCorrectDecomposition)
{
    // Given
    const auto& param = GetParam();
    const Matrix<double> A = param.input_matrix;
    const Matrix<double> expected_G = param.expected_G;

    // Call
    const auto G = CholeskyDecomposition(A);

    // Expect
    for (std::int32_t i{0}; i < static_cast<std::int32_t>(expected_G.size()); ++i)
    {
        for (std::int32_t j{0}; j < static_cast<std::int32_t>(expected_G.at(0).size()); ++j)
        {
            EXPECT_NEAR(G.at(i).at(j), expected_G.at(i).at(j), tolerance_);
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    CholeskyDecompositionTests,
    CholeskyDecompositionTestFixture,
    ::testing::Values(
        // clang-format off
        CholeskyDecompositionTestParameter{
            .input_matrix = Matrix<double>({{1, 0, 1},
                                            {0, 2, 0},
                                            {1, 0, 3}}),
            .expected_G = Matrix<double>({{1.0,     0.0,    0.0},
                                          {0.0,  1.4142,    0.0},
                                          {1.0,     0.0, 1.4142}}),
            .test_name = "ThreeByThree"},
        CholeskyDecompositionTestParameter{
            .input_matrix = Matrix<double>({{ 4,   12, -16},
                                            { 12,  37, -43},
                                            {-16, -43,  98}}),
            .expected_G = Matrix<double>({{ 2,  0, 0},
                                          { 6,  1, 0},
                                          {-8,  5, 3}}),
            .test_name = "NonZeroThreeByThree"},
        CholeskyDecompositionTestParameter{
            .input_matrix = {{2,  -1,  0, 0},
                            {-1,   2, -1, 0},
                            { 0,  -1,  2, -1},
                            { 0,   0, -1, 2}},
            .expected_G = {{ 1.4142,       0,       0,      0},
                           {-0.7071,  1.2247,       0,      0},
                           {      0, -0.8165,  1.1547,      0},
                           {      0,       0, -0.8660, 1.1180}},
            .test_name = "FourByFour"}),
    // clang-format on
    [](const ::testing::TestParamInfo<CholeskyDecompositionTestParameter>& info) { return info.param.test_name; });

TEST(CholeskyDecompositionTests, GivenNonPositiveDefiniteMatrix_ExpectThrow)
{
    // Given
    const Matrix<double> A{{2, 3}, {4, -9}};

    // Call and Expect
    EXPECT_THROW(CholeskyDecomposition(A), std::invalid_argument);
}

}  // namespace
}  // namespace matrix
}  // namespace nm
