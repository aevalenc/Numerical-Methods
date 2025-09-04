/*
 * Controls LQR Algorithm Tests
 */

#include "controls/lqr/newton_kleinman.h"
#include "matrix_solvers/utilities.h"
#include <cmath>
#include <gtest/gtest.h>

namespace nm
{
namespace controls
{
namespace
{

TEST(LQRTests, GivenLyaponovEquation_ExpectValidSolution)
{
    // Given
    const double m_ = 10.0;
    const double k_ = 50.0;
    const double c_ = 0.3 * (2 * std::sqrt(k_ * m_));
    const double tolerance = 1e-3;

    // Setup Right Hand Side
    const matrix::Matrix<double> A{{-c_ / m_, -k_ / m_}, {1.0, 0.0}};
    const matrix::Matrix<double> B{{1 / m_}, {0}};

    // Cost Matrices
    matrix::Matrix<double> Q{{0, 0}, {0, 40}};
    matrix::Matrix<double> R{{0.2}};

    // Initial Guess
    matrix::Matrix<double> K0{{2.0, 2.0}};

    // Call
    const auto result = NewtonKleinman(A, B, Q, R, K0);

    // Expect
    ASSERT_EQ(result.first.size(), 1);
    ASSERT_EQ(result.first.at(0).size(), 2);
    EXPECT_NEAR(result.first.at(0).at(0), 1.39003, tolerance);
    EXPECT_NEAR(result.first.at(0).at(1), 1.96152, tolerance);

    ASSERT_EQ(result.second.size(), 2);
    ASSERT_EQ(result.second.at(0).size(), 2);
    EXPECT_NEAR(result.second.at(0).at(0), 2.78005, tolerance);
    EXPECT_NEAR(result.second.at(0).at(1), 3.92305, tolerance);
    EXPECT_NEAR(result.second.at(1).at(0), result.second.at(0).at(1), tolerance);
    EXPECT_NEAR(result.second.at(1).at(1), 19.7089, tolerance);
}

}  // namespace
}  // namespace controls
}  // namespace nm
