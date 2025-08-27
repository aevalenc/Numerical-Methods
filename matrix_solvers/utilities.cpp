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

// std::vector<double> Vectorize(const Matrix<double>& A)
// {
//     const auto m = A.size();
//     const auto n = A.at(0).size();

//     std::vector<double> result{};
//     result.resize(m * n);

//     // ptrdiff_t offset{};
//     // for (std::int32_t i{0}; i < A.size(); ++i)
//     // {
//     //     offset = i + A.at(0).size();
//     std::transform(A.at(i).begin(), A.at(i).end(), result.begin(), );
//     // }
//     return result;
// }

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
