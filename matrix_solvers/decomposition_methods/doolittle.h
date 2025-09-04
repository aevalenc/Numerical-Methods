/*
 * Author: Alejandro Valencia
 * Update: August 29, 2025
 *
 * Doolittle decomposition of linear system of equations
 */

#ifndef MATRIX_SOLVERS_DIRECT_SOLVERS_DOOLITTLE_H
#define MATRIX_SOLVERS_DIRECT_SOLVERS_DOOLITTLE_H

#include "matrix_solvers/utilities.h"
#include <utility>

namespace nm
{

namespace matrix
{

std::pair<Matrix<double>, Matrix<double>> Doolittle(const Matrix<double>& A);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_DIRECT_SOLVERS_DOOLITTLE_H
