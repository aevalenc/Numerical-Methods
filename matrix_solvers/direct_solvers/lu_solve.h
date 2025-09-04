/*
 * Direct Solution to Linear System via Doolittle LU decomposition
 *
 * Author: Alejandro Valencia
 * Update: September 9th, 2025
 */

#ifndef MATRIX_SOLVERS_DIRECT_SOLVERS_LU_SOLVE_H
#define MATRIX_SOLVERS_DIRECT_SOLVERS_LU_SOLVE_H

#include "matrix_solvers/utilities.h"
#include <vector>

namespace nm
{

namespace matrix
{

/// @brief This function performs a Doolittle LU decomposition to solve
/// the matrix equation Ax = b
///
/// @param A: The lower triangular matrix (square n x n)
/// @param b: The right hand side of the matrix equation (column n x 1)
std::vector<double> LUSolve(const Matrix<double>& A, const std::vector<double>& b);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_DIRECT_SOLVERS_LU_SOLVE_H
