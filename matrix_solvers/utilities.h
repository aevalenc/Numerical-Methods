/*
 * Author: Alejandro Valencia
 * Update: April 1, 2024
 *
 * Utility functions for matrix solvers
 */

#include <cstdint>
#include <iostream>
#include <vector>

#ifndef MATRIX_SOLVERS_UTILITIES_H
#define MATRIX_SOLVERS_UTILITIES_H

namespace nm
{

namespace matrix
{

/// @brief Matrix alias template
///
/// @param T: template-parameter-typename
template <typename T>
using Matrix = std::vector<std::vector<T>>;

/// @brief Identity Square Matrix Constructor
///
/// @param size: Size of matrix to be constructed
///
/// @return Matrix<T>: A matrix with the same typename used for function call
template <typename T>
Matrix<T> CreateIdentityMatrix(const std::int32_t size)
{
    if (size <= 0)
    {
        throw std::exception{};
    }

    Matrix<T> I{};
    I.resize(size);
    for (std::int32_t i{0}; i < size; ++i)
    {
        I.at(i).resize(size);
        I.at(i).at(i) = 1.0;
    }

    return I;
}

/// @brief Print a std vector
///
/// @param vector: a std::vector
template <typename T>
void PrintVector(const std::vector<T>& vector)
{
    for (const auto& element : vector)
    {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

/// @brief Print a Matrix
///
/// @param matrix: a Matrix
template <typename T>
void PrintMatrix(const Matrix<T>& matrix)
{
    for (const auto& row : matrix)
    {
        PrintVector(row);
    }
};

/// @brief Converts a matrix into a vector by stacking its elements column-wise
///
/// @param A The matrix to be vectorized
/// @return std::vector<double> The resulting vector containing the elements of the matrix
std::vector<double> Vectorize(const Matrix<double>& A);

nm::matrix::Matrix<double> ScalarMultiply(const double scalar_value, const nm::matrix::Matrix<double>& A);
/// @brief Adds two vectors element-wise
///
/// @param a First std::vector of doubles
/// @param b Second std::vector of doubles
/// @return std::vector<double> The element-wise sum of a and b
std::vector<double> AddVectors(const std::vector<double>& a, const std::vector<double>& b);

/// @brief Multiplies a vector by a scalar value
///
/// @param scalar_value The scalar multiplier
/// @param a The std::vector of doubles to be scaled
/// @return std::vector<double> The scaled vector
std::vector<double> ScalarMultiply(const double scalar_value, const std::vector<double>& a);

/// @brief Multiplies a matrix by a scalar value
///
/// @param scalar_value The scalar multiplier
/// @param A The matrix to be scaled
/// @return Matrix<double> The scaled matrix
nm::matrix::Matrix<double> ScalarMultiply(const double scalar_value, const nm::matrix::Matrix<double>& A);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_UTILITIES_H
