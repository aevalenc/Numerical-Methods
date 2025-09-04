/*
 * Doolittle decomposition of linear system of equations
 *
 * Author: Alejandro Valencia
 * Update: August 29, 2025
 */

#ifndef MATRIX_SOLVERS_DECOMPOSITION_METHODS_QR_DECOMPOSTION_H
#define MATRIX_SOLVERS_DECOMPOSITION_METHODS_QR_DECOMPOSTION_H

#include "matrix_solvers/utilities.h"
#include <utility>

namespace nm
{

namespace matrix
{

/// @brief Computes the QR decomposition of a matrix using the classical Gram-Schmidt process.
///
/// Decomposes matrix A into an orthogonal matrix Q and an upper triangular matrix R such that A = QR.
///
/// @param A The input matrix to decompose (m x n)
/// @return std::pair<Matrix<double>, Matrix<double>> A pair (Q, R) where Q is m x n and R is n x n
std::pair<Matrix<double>, Matrix<double>> QRDecompositionGramSchmidt(const Matrix<double>& A);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_DECOMPOSITION_METHODS_QR_DECOMPOSTION_H
