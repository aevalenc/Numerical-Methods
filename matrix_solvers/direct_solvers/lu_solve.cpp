/*
 * Author: Alejandro Valencia
 * Update: January 21, 2024
 */

#include "matrix_solvers/direct_solvers/backwards_substitution.h"
#include "matrix_solvers/direct_solvers/doolittle.h"
#include "matrix_solvers/direct_solvers/forward_substitution.h"
#include <cstdint>

namespace nm
{

namespace matrix
{

std::vector<double> LUSolve(const std::vector<std::vector<double>>& A, const std::vector<double>& b)
{
    const auto LU_matrices = Doolittle(A);
    const auto y = ForwardSubstitution(LU_matrices.first, b);
    const auto x = BackwardsSubstitution(LU_matrices.second, y);
    return x;
}

}  // namespace matrix

}  // namespace nm
