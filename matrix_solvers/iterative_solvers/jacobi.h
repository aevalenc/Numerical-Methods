/*
 * Author: ALejandro Valencia
 * Update: 16 April, 2023
 */

#ifndef MATRIX_SOLVERS_ITERATIVE_SOLVERS_JACOBI_H
#define MATRIX_SOLVERS_ITERATIVE_SOLVERS_JACOBI_H

#include "matrix_solvers/utilities.h"
#include <vector>

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
double Jacobi(const Matrix<double>& A, const std::vector<double>& b, std::vector<double>& x);

/// @brief This function implements a full iterative jacobi method solver
///
/// @param A: nxn Matrix
/// @param b:	Right hand side of matrix equation
/// @param x: Initialized solution
///
/// @return residual: L2 norm defined as sqrt(sum((x-x0)^2))
void Jacobi(const Matrix<double>& A,
            const std::vector<double>& b,
            std::vector<double>& x,
            const int max_iterations,
            const double tolerance);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_ITERATIVE_SOLVERS_JACOBI_H
