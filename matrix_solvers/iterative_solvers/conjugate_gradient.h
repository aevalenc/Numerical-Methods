/*
 * Author: Alejandro Valencia
 * Update: October 8, 2023
 */

#include "matrix_solvers/utilities.h"
#include <cstdint>
#include <vector>

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

/// @brief Gauss Seidel foward sweep iterative linear solver
///
/// @param A: nxn Matrix
/// @param b: Right hand side of matrix equation
/// @param x: Initial guess to solution
/// @param max_iterations: maximum iterations limit for algorithm
/// @param tolerance: tolerance limit for algorithm break
///
void ConjugateGradient(const Matrix<double>& A,
                       const std::vector<double>& b,
                       std::vector<double>& x,
                       const std::int32_t max_iterations,
                       const double tolerance);

}  // namespace matrix

}  // namespace nm
