/*
 * Author: Alejandro Valencia
 * Update: April 6, 2024
 *
 * Utility functions for matrix solvers
 */

#include "matrix_solvers/utilities.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <tuple>

namespace nm
{

namespace matrix
{

Matrix<double> MatMult(const Matrix<double>& A, const Matrix<double>& B)
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

    Matrix<double> result{};
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

std::vector<double> MatMult(const Matrix<double>& A, const std::vector<double>& b)
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

double L2Norm(const std::vector<double>& vector)
{
    std::vector<double> vector_squared{};

    std::transform(
        std::cbegin(vector), std::cend(vector), std::back_inserter(vector_squared), [](const auto& vector_element) {
            return vector_element * vector_element;
        });

    return std::sqrt(std::accumulate(std::cbegin(vector_squared), std::cend(vector_squared), 0.0));
}

double Dot(const std::vector<double>& vector_1, const std::vector<double>& vector_2)
{

    if (vector_1.empty())
    {
        throw std::length_error("Input vector 1 is empty");
    }

    if (vector_2.empty())
    {
        throw std::length_error("Input vector 2 is empty");
    }

    if (vector_1.size() != vector_2.size())
    {
        throw std::length_error("Vectors are not of the same length");
    }

    std::vector<double> vectors_multiplied{};

    std::ignore = std::transform(
        std::cbegin(vector_1),
        std::cend(vector_1),
        std::cbegin(vector_2),
        std::back_inserter(vectors_multiplied),
        [](const auto& vector_1_element, const auto& vector_2_element) { return vector_1_element * vector_2_element; });

    return std::accumulate(std::cbegin(vectors_multiplied), std::cend(vectors_multiplied), 0.0);
}

std::vector<double> CalculateResidual(const Matrix<double>& A,
                                      const std::vector<double>& b,
                                      const std::vector<double>& x,
                                      const std::int32_t n)
{
    std::vector<double> residual{};
    residual.resize(n);
    const auto Ax = MatMult(A, x);
    for (std::int32_t i = 0; i < n; ++i)
    {
        residual.at(i) = (b.at(i) - Ax.at(i));
    }
    return residual;
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
