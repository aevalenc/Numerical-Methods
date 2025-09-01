/*
 * Newton Kleinman Method to solve the LQR problem for control systems
 *
 * Author: Alejandro Valencia
 * Update: September 1st
 */

#include "controls/lqr/newton_kleinman.h"
#include "matrix_solvers/iterative_solvers/jacobi.h"
#include "matrix_solvers/operations/operations.h"
#include "matrix_solvers/utilities.h"
#include <vector>

namespace nm
{
namespace controls
{

nm::matrix::Matrix<double> NewtonKleinman(const nm::matrix::Matrix<double>& A,
                                          const nm::matrix::Matrix<double>& B,
                                          const nm::matrix::Matrix<double>& Q,
                                          const nm::matrix::Matrix<double>& R,
                                          const nm::matrix::Matrix<double> K0)
{
    const auto I = nm::matrix::CreateIdentityMatrix<double>(A.size());
    const auto BK0 = nm::matrix::MatMult(B, K0);
    auto S0 = A + BK0;

    // Apply Kronecker product
    // To solve the system S0'P + PS0 = -Q - K0'RK0
    const auto K0_transposed = K0.Transpose();
    const auto K0TRK0 = nm::matrix::MatMult((MatMult(K0_transposed, R)), K0);
    const auto RHS = Q + K0TRK0;
    const auto negative_RHS = matrix::ScalarMultiply(-1.0, RHS);

    const auto RHS_vectorized = matrix::Vectorize(negative_RHS);
    const auto IA = matrix::KroneckerProduct(I, A);
    const auto AI = matrix::KroneckerProduct(A, I);

    const auto AA = (IA + AI);

    std::vector<double> P_vectorized{0, 0, 0, 0};
    matrix::Jacobi(AA, RHS_vectorized, P_vectorized, 100, 1e-3);

    return nm::matrix::Matrix<double>{};
}

}  // namespace controls
}  // namespace nm
