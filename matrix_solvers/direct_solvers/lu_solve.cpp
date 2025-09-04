/*
 * Direct Solution to Linear System via Doolittle LU decomposition
 *
 * Author: Alejandro Valencia
 * Update: September 9th, 2025
 */

#include "matrix_solvers/decomposition_methods/doolittle.h"
#include "matrix_solvers/direct_solvers/backwards_substitution.h"
#include "matrix_solvers/direct_solvers/forward_substitution.h"
#include "matrix_solvers/utilities.h"

namespace nm
{

namespace matrix
{

std::vector<double> LUSolve(const Matrix<double>& A, const std::vector<double>& b)
{
    const auto LU_matrices = Doolittle(A);
    const auto y = ForwardSubstitution(LU_matrices.first, b);
    const auto x = BackwardsSubstitution(LU_matrices.second, y);
    return x;
}

}  // namespace matrix

}  // namespace nm
