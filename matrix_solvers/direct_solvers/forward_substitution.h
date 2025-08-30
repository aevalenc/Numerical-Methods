/*
 * Author: Alejandro Valencia
 * Update: January 21, 2024
 */

#ifndef MATRIX_SOLVERS_DIRECT_SOLVERS_FORWARD_SUBSTITUTION_H
#define MATRIX_SOLVERS_DIRECT_SOLVERS_FORWARD_SUBSTITUTION_H

#include "matrix_solvers/utilities.h"
#include <vector>

namespace nm
{

namespace matrix
{

/// @brief This function performs a forward substitution algorithm to solve
/// the matrix equation Ax = b, where A is an LOWER triangular matrix.
///
/// NOTE:This function works for a dominant LOWER triangular matrix
///    where elements in diagonal (a_ii) is not 0
///
/// @param A: The lower triangular matrix (square n x n)
/// @param b: The right hand side of the matrix equation (column n x 1)
std::vector<double> ForwardSubstitution(const Matrix<double>& A, const std::vector<double>& b);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_DIRECT_SOLVERS_FORWARD_SUBSTITUTION_H
