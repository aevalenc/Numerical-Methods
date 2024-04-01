/*
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 *
 * Utility functions for matrix solvers
 */

#include "matrix_solvers/utilities.h"
#include <cassert>
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

std::vector<std::vector<double>> MatMult(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
    const auto m = static_cast<std::int32_t>(A.size());
    const auto n = static_cast<std::int32_t>(B.size());

    if ((m <= 0) || (n <= 0))
    {
        throw std::length_error("The size of the matrices must be greater 0");
    }
    const auto p = static_cast<std::int32_t>(B.at(0).size());

    if ((static_cast<std::int32_t>(A.at(0).size()) != n))
    {
        throw std::length_error("Input matrix dimension mismatch. Are your matrices compatible?");
    }

    std::vector<std::vector<double>> result{};
    result.resize(m);
    for (auto& row : result)
    {
        row.resize(p);
    }

    double sum{0.0};
    for (std::int32_t i = 0; i < m; ++i)
    {
        for (std::int32_t j = 0; j < p; ++j)
        {
            sum = 0.0;
            for (std::int32_t k = 0; k < n; ++k)
            {
                sum += A.at(i).at(k) * B.at(k).at(j);
            }
            result.at(i).at(j) = sum;
        }
    }
    return result;
}

std::vector<double> MatMult(std::vector<std::vector<double>> A, std::vector<double> b)
{
    const auto m = static_cast<std::int32_t>(A.size());
    const auto n = static_cast<std::int32_t>(b.size());

    if ((m <= 0) || (n <= 0))
    {
        throw std::length_error("The size of the matrices must be greater 0");
    }

    if (m != n)
    {
        throw std::length_error("Input matrix dimension mismatch. Are your matrices compatible?");
    }

    std::vector<double> result{};
    result.resize(n);

    double sum{0.0};
    for (std::int32_t i = 0; i < m; ++i)
    {
        sum = 0.0;
        for (std::int32_t k = 0; k < n; ++k)
        {
            sum += A.at(i).at(k) * b.at(k);
        }
        result.at(i) = sum;
    }
    return result;
}

}  // namespace matrix

}  // namespace nm
