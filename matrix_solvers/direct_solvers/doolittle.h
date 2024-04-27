/*
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 *
 * Doolittle decomposition of linear system of equations
 */

#include <utility>
#include <vector>

#ifndef MATRIX_SOLVERS_DIRECT_SOLVERS_DOOLITTLE_H
#define MATRIX_SOLVERS_DIRECT_SOLVERS_DOOLITTLE_H

namespace nm
{

namespace matrix
{

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> Doolittle(
    const std::vector<std::vector<double>>& A);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_DIRECT_SOLVERS_DOOLITTLE_H
