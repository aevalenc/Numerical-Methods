/*
 * Newton Kleinman Method to solve the LQR problem for control systems
 *
 * Author: Alejandro Valencia
 * Update: September 1st
 */

#ifndef CONTROLS_LQR_NEWTON_KLEINMAN_H
#define CONTROLS_LQR_NEWTON_KLEINMAN_H

#include "matrix_solvers/utilities.h"

namespace nm
{
namespace controls

{

///
/// @brief Solves for full state feedback control gains using the Newton-Kleinman method and the Kronecker product.
///
/// This function computes the optimal state feedback gain matrix for a continuous-time linear quadratic regulator (LQR)
/// problem. It uses the Newton-Kleinman iterative method, leveraging the Kronecker product to solve the associated
/// Lyapunov or Riccati equations.
///
/// @param A System dynamics matrix (n x n)
/// @param B Input matrix (n x m)
/// @param Q State weighting matrix (n x n, symmetric positive semi-definite)
/// @param R Input weighting matrix (m x m, symmetric positive definite)
/// @param K0 Initial guess for the feedback gain matrix (m x n)
/// @param max_iterations Maximum number of iterations for the Newton-Kleinman algorithm (default: 1000)
/// @param tolerance Convergence tolerance for the iterative solution (default: 1e-6)
/// @return std::pair<matrix::Matrix<double>, matrix::Matrix<double>>
///         First: Optimal state feedback gain matrix (K)
///         Second: Solution to the Riccati equation (P matrix)
///
std::pair<matrix::Matrix<double>, matrix::Matrix<double>> NewtonKleinman(const matrix::Matrix<double>& A,
                                                                         const matrix::Matrix<double>& B,
                                                                         const matrix::Matrix<double>& Q,
                                                                         const matrix::Matrix<double>& R,
                                                                         const matrix::Matrix<double>& K0,
                                                                         const std::int32_t max_iterations = 1000,
                                                                         const double tolerance = 1e-6);

}  // namespace controls
}  // namespace nm

#endif  // CONTROLS_LQR_NEWTON_KLEINMAN_H
