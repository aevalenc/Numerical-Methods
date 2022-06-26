/*
 * Author: Alejandro Valencia
 * Project: Backwards Substitution Matrix Solver
 */
#include <vector>

namespace nm {
namespace matrix {
void BackwardsSubstitution(const std::vector<std::vector<double>> &A,
                           std::vector<double> &x,
                           const std::vector<double> &b);
}
} // namespace nm