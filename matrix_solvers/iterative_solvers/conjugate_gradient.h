/*
 * Author: Alejandro Valencia
 * Update: October 8, 2023
 */

#include "matrix_solvers/utilities.h"
#include <cstdint>
#include <vector>

#ifndef MATRIX_SOLVERS_ITERATIVE_SOLVERS_CONJUGATE_GRADIENT_H
#define MATRIX_SOLVERS_ITERATIVE_SOLVERS_CONJUGATE_GRADIENT_H

namespace nm
{

namespace matrix
{

/// @brief Perform a Single Iteration of the Conjugate Gradient Method
///
/// @param A: nxn Matrix
/// @param b: Right hand side of matrix equation
/// @param x: Initial guess to solution
/// @param residual: residual vector
/// @param p: direction vector
///
/// @return std::pair<residual, p>: where residual is the updated negative gradient and p is the direction vector
std::pair<std::vector<double>, std::vector<double>> ConjugateGradient(const Matrix<double>& A,
                                                                      const std::vector<double>& b,
                                                                      std::vector<double>& x,
                                                                      std::vector<double>& residual,
                                                                      std::vector<double>& p);

/// @brief Conjugate Gradient iterative linear solver
///
/// Solves the linear system Ax = b for symmetric positive-definite matrices using the Conjugate Gradient method.
///
/// @param A nxn symmetric positive-definite matrix
/// @param b Right-hand side vector
/// @param x On input: initial guess; on output: approximate solution
/// @param tolerance Stopping criterion for the residual norm
/// @param max_iterations Maximum number of iterations
///
void ConjugateGradient(const Matrix<double>& A,
                       const std::vector<double>& b,
                       std::vector<double>& x,
                       const double tolerance = 1e-3,
                       const std::int32_t max_iterations = 1000);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_ITERATIVE_SOLVERS_CONJUGATE_GRADIENT_H