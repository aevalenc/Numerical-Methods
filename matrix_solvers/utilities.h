/*
 * Author: Alejandro Valencia
 * Update: April 1, 2024
 *
 * Utility functions for matrix solvers
 */

#ifndef MATRIX_SOLVERS_UTILITIES_H
#define MATRIX_SOLVERS_UTILITIES_H

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

namespace nm
{

namespace matrix
{

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

/// @brief Matrix alias template
///
/// @param T: template-parameter-typename
template <typename T>
// using Matrix = std::vector<std::vector<T>>;
class Matrix : public std::vector<std::vector<T>>
{
  private:
    std::int32_t m_{};
    std::int32_t n_{};
    std::int32_t p_{};

  public:
    // Default constructor
    Matrix() = default;

    // Initializer-list constructor
    Matrix(std::initializer_list<std::vector<T>> init) : std::vector<std::vector<T>>(init)
    {
        m_ = static_cast<std::int32_t>(this->size());
        if (!this->at(0).empty())
        {
            n_ = this->at(0).size();
        }
        else
        {
            n_ = 1;
        }
    }

    // Resize constuctor
    Matrix(const std::int32_t rows, const std::int32_t columns)
    {
        assert(rows > 0);
        assert(columns > 0);

        this->resize(rows);
        for (std::int32_t i{0}; i < rows; ++i)
        {
            this->at(i).resize(columns);
        }
        m_ = rows;
        n_ = columns;
    }

    // Copy constructor
    Matrix(const Matrix& other) : std::vector<std::vector<T>>(other)
    {
        m_ = static_cast<std::int32_t>(this->size());
        if (m_ > 0)
        {
            n_ = static_cast<std::int32_t>(this->at(0).size());
        }
        else
        {
            n_ = 1;
        }
    }

    // Copy assignment operator
    Matrix& operator=(const Matrix& other)
    {
        std::vector<std::vector<T>>::operator=(other);
        m_ = static_cast<std::int32_t>(this->size());
        if (!this->at(0).empty())
        {
            n_ = this->at(0).size();
        }
        else
        {
            n_ = 1;
        }
        return *this;
    }

    // Move Constructor
    Matrix(Matrix<T>&& other) noexcept : std::vector<std::vector<T>>(std::move(other))
    {
        m_ = static_cast<std::int32_t>(this->size());
        if (!this->empty())
        {
            n_ = this->at(0).size();
        }
        else
        {
            n_ = 0;
        }
    }

    // Other constructors and operators
    Matrix(const std::vector<std::vector<T>>& other) { this->assign(other.begin(), other.end()); }
    Matrix(T* array_ptr, const std::int32_t number_of_rows, const std::int32_t number_of_columns)
    {
        assert(array_ptr != nullptr);
        assert(number_of_rows > 0);
        assert(number_of_columns > 0);

        this->resize(number_of_rows);
        for (std::int32_t i{0}; i < number_of_rows; ++i)
        {
            this->at(i).resize(number_of_columns);
            this->at(i) = std::vector<T>(array_ptr + (number_of_columns * i),
                                         array_ptr + (number_of_columns * i + number_of_columns));
        }
    }

    std::int32_t NumberOfRows() const { return m_; }
    std::int32_t NumberOfColumns() const { return n_; }

    Matrix<T> operator+(const Matrix<T>& other) const
    {
        const auto m = static_cast<std::int32_t>(this->size());
        const auto n = static_cast<std::int32_t>(this->at(0).size());
        const auto other_m = static_cast<std::int32_t>(other.size());
        const auto other_n = static_cast<std::int32_t>(other.at(0).size());
        if (m != other_m || n != other_n)
        {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        Matrix<T> result = *this;
        for (std::int32_t i{0}; i < m; ++i)
        {
            result.at(i) = AddVectors(this->at(i), other.at(i));
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& other) const
    {
        const auto m = static_cast<std::int32_t>(this->size());
        const auto n = static_cast<std::int32_t>(this->at(0).size());
        const auto other_m = static_cast<std::int32_t>(other.size());
        const auto other_n = static_cast<std::int32_t>(other.at(0).size());

        if (m != other_m || n != other_n)
        {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        Matrix<T> result = *this;
        for (std::int32_t i{0}; i < m; ++i)
        {
            result.at(i) = AddVectors(this->at(i), ScalarMultiply(-1, other.at(i)));
        }
        return result;
    }

    void TransposeInPlace()
    {
        const auto rows = static_cast<std::int32_t>(this->size());
        assert(rows > 0);

        const auto columns = static_cast<std::int32_t>(this->at(0).size());
        assert(columns > 0);

        for (std::int32_t i{0}; i < rows; ++i)
        {
            for (std::int32_t j{i}; j < columns; ++j)
            {
                if (i == j)
                {
                    continue;
                }
                else
                {
                    const auto tmp = this->at(i).at(j);
                    this->at(i).at(j) = this->at(j).at(i);
                    this->at(j).at(i) = tmp;
                }
            }
        }
    }

    Matrix<T> Transpose() const
    {
        const auto rows = static_cast<std::int32_t>(this->size());
        assert(rows > 0);

        const auto columns = static_cast<std::int32_t>(this->at(0).size());
        assert(columns > 0);

        Matrix<T> result{};
        result.resize(columns);

        for (std::int32_t i{0}; i < rows; ++i)
        {
            for (std::int32_t j{0}; j < columns; ++j)
            {
                result.at(j).resize(rows);
                if (i == j)
                {
                    result.at(i).at(j) = this->at(i).at(j);
                }
                else
                {
                    result.at(j).at(i) = this->at(i).at(j);
                }
            }
        }
        return result;
    }
};

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

    Matrix<T> I(size, size);
    for (std::int32_t i{0}; i < size; ++i)
    {
        I.at(i).at(i) = static_cast<T>(1);
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

/// @brief Converts a vector into a Matrix by re-ordering its elements column-wise
///
/// @param a The vector to be devectorized
/// @param column_length The length of the columns for the new matrix
/// @return Matrix<double> The resulting matrix containing the elements of the vector
Matrix<double> Devectorize(const std::vector<double>& a, const std::int32_t column_length);

/// @brief Multiplies a matrix by a scalar value
///
/// @param scalar_value The scalar multiplier
/// @param A The matrix to be scaled
/// @return Matrix<double> The scaled matrix
Matrix<double> ScalarMultiply(const double scalar_value, const nm::matrix::Matrix<double>& A);

template <typename T>
std::vector<T> ToStdVectorRowBased(const Matrix<T>& A)
{
    const auto m = static_cast<std::int32_t>(A.size());
    assert(m > 0);

    const auto n = static_cast<std::int32_t>(A.at(0).size());
    assert(n > 0);

    std::vector<T> result{};
    result.reserve(m * n);

    for (std::int32_t i{0}; i < m; ++i)
    {
        std::transform(
            A.at(i).cbegin(), A.at(i).cend(), std::back_inserter(result), [](const T& value) { return value; });
    }
    return result;
}

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_UTILITIES_H
