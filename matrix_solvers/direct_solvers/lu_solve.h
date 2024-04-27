/*
 * Author: Alejandro Valencia
 * Update: January 21, 2024
 */

#include <vector>

#ifndef MATRIX_SOLVERS_DIRECT_SOLVERS_LU_SOLVE_H
#define MATRIX_SOLVERS_DIRECT_SOLVERS_LU_SOLVE_H

namespace nm
{

namespace matrix
{

/// @brief This function performs an LU decomposition to solve
/// the matrix equation Ax = b
///
/// @param A: The lower triangular matrix (square n x n)
/// @param b: The right hand side of the matrix equation (column n x 1)
std::vector<double> LUSolve(const std::vector<std::vector<double>>& A, const std::vector<double>& b);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_DIRECT_SOLVERS_LU_SOLVE_H
