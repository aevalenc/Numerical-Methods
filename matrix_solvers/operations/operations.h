/*
 * Author: Alejandro Valencia
 * Update: April 1, 2024
 *
 * Matrix operation functions
 */

#ifndef MATRIX_SOLVERS_OPERATIONS_OPERATIONS_H
#define MATRIX_SOLVERS_OPERATIONS_OPERATIONS_H

#include "matrix_solvers/utilities.h"
#include <cstdint>
#include <vector>

namespace nm
{

namespace matrix
{

/// @brief Matrix Multiplication Function for 2 Matrices of type Matrix<double>
///
/// @param A: mxn Matrix of doubles
/// @param B: nxp Matrix of doubles
///
/// @return C: a mxp Matrix of doubles
Matrix<double> MatMult(const Matrix<double>& A, const Matrix<double>& B);

/// @brief Matrix Multiplication between a Matrix and a vector
///
/// @param A: mxn Matrix of doubles
/// @param b: nx1 std::vector of doubles
///
/// @return
std::vector<double> MatMult(const Matrix<double>& A, const std::vector<double>& b);

/// @brief Calculate the L2 norm of a vector
///
/// @param vector: std::vector of doubles
///
/// @return L2 norm computed value
double L2Norm(const std::vector<double>& vector);

/// @brief Performs the dot (scalar) product
///
/// @param vector_1: std::vector of doubles
/// @param vector_2: std::vector of doubles
///
/// @return dot product result
double Dot(const std::vector<double>& vector_1, const std::vector<double>& vector_2);

/// @brief Helper function to calculate the residual of the matrix equation Ax = b
///
/// @param A: Matrix of doubles
/// @param b: std::vector of doubles
/// @param x: Guess value for solution
/// @param n: size of x
///
/// @return residual as std::vector of doubles
std::vector<double> CalculateResidual(const Matrix<double>& A,
                                      const std::vector<double>& b,
                                      const std::vector<double>& x,
                                      const std::int32_t n);

Matrix<double> KroneckerProduct(const Matrix<double>& A, const Matrix<double>& B);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_OPERATIONS_OPERATIONS_H
