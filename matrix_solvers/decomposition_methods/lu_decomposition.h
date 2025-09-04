/*
 * LU decomposition methods
 *
 * Author: Alejandro Valencia
 * Update: September 4, 2025
 */

#ifndef MATRIX_SOLVERS_DECOMPOSITION_METHODS_LU_DECOMPOSITION_H
#define MATRIX_SOLVERS_DECOMPOSITION_METHODS_LU_DECOMPOSITION_H

#include "matrix_solvers/utilities.h"
#include <utility>

namespace nm
{

namespace matrix
{

std::pair<Matrix<double>, Matrix<double>> Doolittle(const Matrix<double>& A);
Matrix<double> CholeskyDecomposition(const Matrix<double>& A);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_DECOMPOSITION_METHODS_LU_DECOMPOSITION_H
