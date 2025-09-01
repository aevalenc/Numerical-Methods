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

nm::matrix::Matrix<double> NewtonKleinman(const nm::matrix::Matrix<double>& A,
                                          const nm::matrix::Matrix<double>& B,
                                          const nm::matrix::Matrix<double>& Q,
                                          const nm::matrix::Matrix<double>& R,
                                          const nm::matrix::Matrix<double>& K0)
{
    // Apply Kronecker product
    // To solve the system S0'P + PS0 = -Q - K0'RK0
    const std::int32_t max_iterations = 1000;
    const double tolerance = 1e-3;
    const auto I = nm::matrix::CreateIdentityMatrix<double>(A.size());
    auto K_previous = K0;
    auto K_next = K0;
    matrix::Matrix<double> P_previous{{0, 0}, {0, 0}};

    for (std::int32_t iter{0}; iter < max_iterations; ++iter)
    {
        const auto BK = nm::matrix::MatMult(B, K_previous);
        auto S = A + BK;

        const auto K_transposed = K_previous.Transpose();
        const auto KTRK = nm::matrix::MatMult((MatMult(K_transposed, R)), K_previous);
        const auto RHS = Q + KTRK;
        const auto negative_RHS = matrix::ScalarMultiply(-1.0, RHS);

        const auto RHS_vectorized = matrix::Vectorize(negative_RHS);
        const auto IS = matrix::KroneckerProduct(I, S);
        const auto SI = matrix::KroneckerProduct(S, I);

        const auto AA = (IS + SI);
        const auto P_vectorized = matrix::LUSolve(AA, RHS_vectorized);

        const auto P = matrix::Devectorize(P_vectorized, negative_RHS.size());
        const auto RBT = matrix::MatMult(R, B.Transpose());
        K_next = matrix::ScalarMultiply(-1.0, matrix::MatMult(RBT, P));

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

    return K_next;
}

}  // namespace controls
}  // namespace nm
