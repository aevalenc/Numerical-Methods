/*
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 *
 * Doolittle decomposition of linear system of equations
 */

#include <vector>

namespace nm
{
namespace matrix_solvers
{
int Doolittle(std::vector<double>& A, std::vector<double>& L, std::vector<double>& U);
}
}  // namespace nm
