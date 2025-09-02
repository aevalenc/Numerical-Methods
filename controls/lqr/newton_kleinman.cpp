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
                                                                         const matrix::Matrix<double>& K0)
{
    // Apply Kronecker product
    // To solve the system S0'P + PS0 = -Q - K0'RK0
    const std::int32_t max_iterations = 1000;
    const double tolerance = 1e-12;

    const auto I = matrix::CreateIdentityMatrix<double>(A.size());
    matrix::Matrix<double> P(Q.size(), Q.size());
    auto K_previous = K0;
    auto K_next = K0;
    matrix::Matrix<double> R_inv{R};
    R_inv.at(0).at(0) = 1 / R.at(0).at(0);

    for (std::int32_t iter{0}; iter < max_iterations; ++iter)
    {
        const auto BK = matrix::MatMult(B, K_previous);
        auto S = A + BK;

        const auto K_transposed = K_previous.Transpose();
        const auto KTRK = matrix::MatMult((MatMult(K_transposed, R)), K_previous);
        const auto RHS = Q + KTRK;
        const auto negative_RHS = matrix::ScalarMultiply(-1.0, RHS);

        const auto RHS_vectorized = matrix::Vectorize(negative_RHS);
        S.TransposeInPlace();
        const auto IS = matrix::KroneckerProduct(I, S);
        const auto SI = matrix::KroneckerProduct(S, I);

        const auto AA = (IS + SI);
        const auto P_vectorized = matrix::LUSolve(AA, RHS_vectorized);

        P = matrix::Devectorize(P_vectorized, negative_RHS.size());
        const auto RinvBT = matrix::MatMult(R_inv, B.Transpose());
        K_next = matrix::ScalarMultiply(-1.0, matrix::MatMult(RinvBT, P));

        const auto negative_K0 = matrix::ScalarMultiply(-1.0, K_previous);
        const auto delta_K = K_next + negative_K0;
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
