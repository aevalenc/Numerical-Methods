/*
 * Matrix Decomposition Methods Tests
 *
 * Author: Alejandro Valencia
 * Update: September 9th, 2025
 */

#include "matrix_solvers/decomposition_methods/doolittle.h"
#include "matrix_solvers/decomposition_methods/qr_decomposition.h"
#include <cmath>
#include <gtest/gtest.h>

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

}  // namespace
}  // namespace matrix
}  // namespace nm
