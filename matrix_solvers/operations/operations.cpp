/*
 * Author: Alejandro Valencia
 * Update: April 6, 2024
 *
 * Utility functions for matrix solvers
 */

#include "matrix_solvers/operations/operations.h"
#include "matrix_solvers/utilities.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <numeric>
#include <tuple>
#include <vector>

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

Matrix<double> ScalarProduct(const Matrix<double>& A, const double value)
{
    Matrix<double> result{A};
    for (std::int32_t i{0}; i < static_cast<std::int32_t>(A.size()); ++i)
    {
        for (std::int32_t j{0}; j < static_cast<std::int32_t>(A.size()); ++j)
        {
            result.at(i).at(j) = A.at(i).at(j) * value;
        }
    }
    return result;
}

std::vector<double> ScalarProduct(const std::vector<double>& A, const double value)
{
    std::vector<double> result{A};
    for (std::int32_t i{0}; i < static_cast<std::int32_t>(A.size()); ++i)
    {
        result.at(i) = A.at(i) * value;
    }
    return result;
}

// Matrix<double> KroneckerProduct(const Matrix<double>& A, const Matrix<double>& B)
double* KroneckerProduct(const Matrix<double>& A, const Matrix<double>& B)
{
    const std::int32_t m = static_cast<std::int32_t>(A.size());
    const std::int32_t n = static_cast<std::int32_t>(A.at(0).size());
    const std::int32_t p = static_cast<std::int32_t>(B.size());
    const std::int32_t q = static_cast<std::int32_t>(B.at(0).size());

    auto C = static_cast<double*>(malloc(m * n * p * q * sizeof(double)));

    for (std::int32_t i{0}; i < m; ++i)
    {
        for (std::int32_t j{0}; j < n; ++j)
        {
            for (std::int32_t k{0}; k < p; ++k)
            {
                for (std::int32_t l{0}; l < q; ++l)
                {
                    const auto index = (l + 2 * j) + (p * q) * (k + 2 * i);
                    const auto product = A.at(i).at(j) * B.at(k).at(l);
                    C[index] = product;
                }
            }
        }
    }

    return C;
}

}  // namespace matrix

}  // namespace nm
