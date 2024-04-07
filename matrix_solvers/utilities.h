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

/// @brief Matrix Multiplication Function for 2 Matrices of type Matrix<double>
///
/// @param A: mxn Matrix of doubles
/// @param B: nxp Matrix of doubles
///
/// @return C: a mxp Matrix of doubles
Matrix<double> MatMult(const Matrix<double>& A, const Matrix<double>& B);

/// @brief Matrix Multiplication between a Matrix and a vector
///
/// @param A: mxn Matrix of doubles
/// @param b: nx1 std::vector of doubles
///
/// @return
std::vector<double> MatMult(const Matrix<double>& A, const std::vector<double>& b);

/// @brief Calculate the L2 norm of a vector
///
/// @param vector: std::vector of doubles
///
/// @return L2 norm computed value
double L2Norm(const std::vector<double>& vector);

/// @brief Performs the dot (scalar) product
///
/// @param vector_1: std::vector of doubles
/// @param vector_2: std::vector of doubles
///
/// @return dot product result
double Dot(const std::vector<double>& vector_1, const std::vector<double>& vector_2);

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_UTILITIES_H
