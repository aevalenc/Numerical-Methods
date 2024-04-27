/*
 * Author: ALejandro Valencia
 * Update: 16 April, 2023
 */

#include <vector>

#ifndef MATRIX_SOLVERS_ITERATIVE_SOLVERS_JACOBI_H
#define MATRIX_SOLVERS_ITERATIVE_SOLVERS_JACOBI_H

namespace nm
{

namespace matrix
{

/// @brief This function implements a single iteration of the jacobi method
///
/// @param A: nxn Matrix
/// @param b:	Right hand side of matrix equation
/// @param x: Initialized solution
///
/// @return residual: L2 norm defined as sqrt(sum((x-x0)^2))
double jacobi(const std::vector<std::vector<double>>& A, const std::vector<double>& b, std::vector<double>& x);

/// @brief This function implements a full iterative jacobi method solver
///
/// @param A: nxn Matrix
/// @param b:	Right hand side of matrix equation
/// @param x: Initialized solution
///
/// @return residual: L2 norm defined as sqrt(sum((x-x0)^2))
void jacobi(const std::vector<std::vector<double>>& A,
            const std::vector<double>& b,
            std::vector<double>& x,
            const int max_iterations,
            const double tolerance);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_ITERATIVE_SOLVERS_JACOBI_H
