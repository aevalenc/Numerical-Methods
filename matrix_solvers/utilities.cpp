/*
 * Author: Alejandro Valencia
 * Update: April 6, 2024
 *
 * Utility functions for matrix solvers
 */

#include "matrix_solvers/utilities.h"
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <vector>

namespace nm
{

namespace matrix
{

std::vector<double> Vectorize(const Matrix<double>& A)
{
    const auto m = static_cast<std::int32_t>(A.size());
    const auto n = static_cast<std::int32_t>(A.at(0).size());

    std::vector<double> result{};

    // Loop through columns
    for (std::int32_t j{0}; j < n; ++j)
    {
        // Within each column grab the corresponding value in that row
        for (std::int32_t i{0}; i < m; ++i)
        {
            result.emplace_back(A.at(i).at(j));
        }
    }
    return result;
}

std::vector<double> AddVectors(const std::vector<double>& a, const std::vector<double>& b)
{
    // assert(a.size() != b.size());
    std::vector<double> result{a};
    for (std::int32_t i{0}; i < static_cast<int32_t>(a.size()); ++i)
    {
        result[i] += b[i];
    }
    return result;
}

std::vector<double> ScalarMultiply(const double scalar_value, const std::vector<double>& a)
{
    std::vector<double> result{a};
    for (std::int32_t i{0}; i < static_cast<int32_t>(a.size()); ++i)
    {
        result[i] *= scalar_value;
    }
    return result;
}

nm::matrix::Matrix<double> ScalarMultiply(const double scalar_value, const nm::matrix::Matrix<double>& A)
{
    nm::matrix::Matrix<double> result{A};
    for (std::int32_t i{0}; i < static_cast<int32_t>(A.size()); ++i)
    {
        for (std::int32_t j{0}; j < static_cast<std::int32_t>(A.at(0).size()); ++j)
        {
            result.at(i).at(j) *= scalar_value;
        }
    }
    return result;
}

}  // namespace matrix

}  // namespace nm
