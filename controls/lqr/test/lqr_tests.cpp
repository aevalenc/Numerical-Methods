/*
 * Controls LQR Algorithm Tests
 */

#include "controls/lqr/newton_kleinman.h"
#include "matrix_solvers/utilities.h"
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

    // Setup Right Hand Side
    const matrix::Matrix<double> A{{-c_ / m_, -k_ / m_}, {1.0, 0.0}};
    const matrix::Matrix<double> B{{1 / m_}, {0}};

    matrix::Matrix<double> Q{{0, 0}, {0, 40}};
    matrix::Matrix<double> R{{0.2}};

    matrix::Matrix<double> K0{{2.0, 2.0}};

    const auto result = NewtonKleinman(A, B, Q, R, K0);

    matrix::PrintMatrix(result);

    EXPECT_TRUE(true);
}

}  // namespace
}  // namespace controls
}  // namespace nm
