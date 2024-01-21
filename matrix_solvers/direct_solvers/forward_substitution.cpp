/*
 * Author: Alejandro Valencia
 * Update: January 21, 2024
 */

#include "matrix_solvers/direct_solvers/forward_substitution.h"
#include <cstdint>

namespace nm
{

namespace matrix
{

std::vector<double> ForwardSubstitution(const std::vector<std::vector<double>>& A, const std::vector<double>& b)
{
    /* Declarations */
    double sum;
    std::vector<double> x{b};

    /* Main Algorithm */
    x.at(0) = b.at(0) / A.at(0).at(0);
    const auto n = static_cast<std::int32_t>(b.size());
    for (std::int32_t i = 1; i < n; ++i)
    {
        sum = 0.0;
        for (std::int32_t j = 0; j < i; ++j)
        {
            sum += A.at(i).at(j) * x.at(j);
        }

        x.at(i) = (b[i] - sum) / A.at(i).at(i);
    }

    return x;
}

}  // namespace matrix

}  // namespace nm
