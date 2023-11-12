/*
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 *
 * Utility functions for matrix solvers
 */

#include "matrix_solvers/utilities.h"
#include <iostream>

namespace nm
{
namespace matrix
{
std::vector<std::vector<double>> CreateIdentityMatrix(std::int32_t size)
{

    std::vector<std::vector<double>> I{};
    I.resize(size);
    for (std::int32_t i{0}; i < size; ++i)
    {
        I.at(i).resize(size);
        I.at(i).at(i) = 1.0;
    }

    return I;
}

void PrintVector(const std::vector<double> vector)
{
    for (const auto& element : vector)
    {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

void PrintMatrix(std::vector<std::vector<double>> matrix)
{
    for (const auto& row : matrix)
    {
        PrintVector(row);
    }
}

}  // namespace matrix

}  // namespace nm
