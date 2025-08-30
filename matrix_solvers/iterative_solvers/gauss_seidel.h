/*
 * Author: Alejandro Valencia
 * Update: October 8, 2023
 */

#ifndef MATRIX_SOLVERS_ITERATIVE_SOLVERS_GAUSS_SEIDEL_H
#define MATRIX_SOLVERS_ITERATIVE_SOLVERS_GAUSS_SEIDEL_H

#include "matrix_solvers/utilities.h"
#include <vector>

namespace nm
{

namespace matrix
{

/// @brief Gauss Seidel foward sweep iterative linear solver
///
/// @param A: nxn Matrix
/// @param b: Right hand side of matrix equation
/// @param x: Initial guess to solution
///
/// @return residual: Max absolute error defined max(|x-x0|)
double GaussSeidel(const Matrix<double>& A, const std::vector<double>& b, std::vector<double>& x);

/// @brief Gauss Seidel foward sweep iterative linear solver
///
/// @param A: nxn Matrix
/// @param b: Right hand side of matrix equation
/// @param x: Initial guess to solution
/// @param max_iterations: maximum iterations limit for algorithm
/// @param tolerance: tolerance limit for algorithm break
///
void GaussSeidel(const Matrix<double>& A,
                 const std::vector<double>& b,
                 std::vector<double>& x,
                 const int max_iterations,
                 const double tolerance);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_ITERATIVE_SOLVERS_GAUSS_SEIDEL_H
