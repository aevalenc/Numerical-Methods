/*
 * Author: Alejandro Valencia
 * Project: Backwards Substitution Matrix Solver
 */

#ifndef MATRIX_SOLVERS_DIRECT_SOLVERS_BACKWARDS_SUBSTITUTION_H
#define MATRIX_SOLVERS_DIRECT_SOLVERS_BACKWARDS_SUBSTITUTION_H

#include "matrix_solvers/utilities.h"
#include <vector>

namespace nm
{

namespace matrix
{

std::vector<double> BackwardsSubstitution(const Matrix<double>& A, const std::vector<double>& b);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_DIRECT_SOLVERS_BACKWARDS_SUBSTITUTION_H
