/*
 * Author: Alejandro Valencia
 * Project: Backwards Substitution Matrix Solver
 */
#include <vector>

#ifndef MATRIX_SOLVERS_DIRECT_SOLVERS_BACKWARDS_SUBSTITUTION_H
#define MATRIX_SOLVERS_DIRECT_SOLVERS_BACKWARDS_SUBSTITUTION_H

namespace nm
{

namespace matrix
{

std::vector<double> BackwardsSubstitution(const std::vector<std::vector<double>>& A, const std::vector<double>& b);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_DIRECT_SOLVERS_BACKWARDS_SUBSTITUTION_H
