/*
 * Newton Kleinman Method to solve the LQR problem for control systems
 *
 * Author: Alejandro Valencia
 * Update: September 1st
 */

#include "controls/lqr/newton_kleinman.h"
#include "matrix_solvers/direct_solvers/lu_solve.h"
#include "matrix_solvers/operations/operations.h"
#include "matrix_solvers/utilities.h"
#include <cstdint>

namespace nm
{
namespace controls
{

std::pair<matrix::Matrix<double>, matrix::Matrix<double>> NewtonKleinman(const matrix::Matrix<double>& A,
                                                                         const matrix::Matrix<double>& B,
                                                                         const matrix::Matrix<double>& Q,
                                                                         const matrix::Matrix<double>& R,
                                                                         const matrix::Matrix<double>& K0,
                                                                         const std::int32_t max_iterations,
                                                                         const double tolerance)
{
    // Apply Kronecker product
    // To solve the system S0'P + PS0 = -Q - K'RK
    const auto I = matrix::CreateIdentityMatrix<double>(A.size());
    const auto m = static_cast<std::int32_t>(Q.size());
    matrix::Matrix<double> P{m, m};
    auto K_previous = K0;
    auto K_next = K0;

    // Calculate inverse input cost matrix R
    matrix::Matrix<double> R_inv{R};
    const auto n = static_cast<std::int32_t>(R.size());
    for (std::int32_t i{0}; i < n; ++i)
    {
        R_inv.at(i).at(i) = 1 / R.at(i).at(i);
    }

    for (std::int32_t iter{0}; iter < max_iterations; ++iter)
    {
        auto S = A - matrix::MatMult(B, K_previous);

        const auto KT_RK = matrix::MatMult((MatMult(K_previous.Transpose(), R)), K_previous);
        const auto RHS = Q + KT_RK;
        const auto negative_RHS = matrix::ScalarMultiply(-1.0, RHS);
        const auto RHS_vectorized = matrix::Vectorize(negative_RHS);

        S.TransposeInPlace();
        const auto AA = matrix::KroneckerProduct(I, S) + matrix::KroneckerProduct(S, I);
        const auto P_vectorized = matrix::LUSolve(AA, RHS_vectorized);

        P = matrix::Devectorize(P_vectorized, negative_RHS.size());
        const auto RinvBT = matrix::MatMult(R_inv, B.Transpose());
        K_next = matrix::MatMult(RinvBT, P);

        const auto delta_K = K_next - K_previous;
        const auto residual = matrix::L2Norm(matrix::Vectorize(delta_K));
        if (residual < tolerance)
        {
            break;
        }
        else
        {
            K_previous = K_next;
        }
    }

    return {K_next, P};
}

}  // namespace controls
}  // namespace nm
