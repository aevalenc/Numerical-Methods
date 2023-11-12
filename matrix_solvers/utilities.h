/*
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 *
 * Utility functions for matrix solvers
 */

#include <cstdint>
#include <vector>

namespace nm
{

namespace matrix
{

std::vector<std::vector<double>> CreateIdentityMatrix(std::int32_t size);
void PrintMatrix(std::vector<std::vector<double>> matrix);
void PrintVector(const std::vector<double> vector);

}  // namespace matrix

}  // namespace nm
