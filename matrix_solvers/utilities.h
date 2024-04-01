/*
 * Author: Alejandro Valencia
 * Update: April 1, 2024
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
std::vector<std::vector<double>> MatMult(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B);
std::vector<double> MatMult(std::vector<std::vector<double>> A, std::vector<double> b);
double L2Norm(const std::vector<double>& vector);

}  // namespace matrix

}  // namespace nm
