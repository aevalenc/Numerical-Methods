/*
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 *
 * Utility functions for matrix solvers
 */

#include "matrix_solvers/utilities.h"

namespace nm
{
namespace matrix_solvers
{
std::vector<std::vector<double>> CreateIdentityMatrix(std::int32_t size)
{

    std::vector<std::vector<double>> I{};
    I.reserve(size);
    for (std::int32_t i{0}; i < size; ++i)
    {
        I.at(i).reserve(size);
        I.at(i).at(i) = 1.0;
    }

    return I;
}
}  // namespace matrix_solvers
}  // namespace nm
