/*
 * LU decomposition methods
 *
 * Author: Alejandro Valencia
 * Update: September 9th, 2025
 */

#include "matrix_solvers/decomposition_methods/lu_decomposition.h"
#include "matrix_solvers/utilities.h"
#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace nm
{

namespace matrix
{

std::pair<Matrix<double>, Matrix<double>> Doolittle(const Matrix<double>& A)
{

    /* Declarations */
    double tempu{};
    double templ{};
    double sumu{};
    double suml{};
    const auto m = static_cast<std::int32_t>(A.size());

    /* Set Identity Matrix */
    auto L = CreateIdentityMatrix<double>(m);
    auto U = CreateIdentityMatrix<double>(m);

    /* Main Algorithm */
    for (std::int32_t k{0}; k < m; ++k)
    {

        // Upper Triangular Matrix
        for (std::int32_t q = k; q < m; ++q)
        {
            sumu = 0.0;
            for (std::int32_t j = 0; j < k; ++j)
            {
                tempu = L.at(k).at(j) * U.at(j).at(q);
                sumu = sumu + tempu;
            }

            U.at(k).at(q) = A.at(k).at(q) - sumu;
        }

        // Lower Triangular Matrix
        //  Recall principle diagonal (i,i) are 1s
        for (std::int32_t i = k + 1; i < m; ++i)
        {
            suml = 0.0;
            for (std::int32_t j = 0; j < k; ++j)
            {
                templ = L.at(i).at(j) * U.at(j).at(k);
                suml = suml + templ;
            }

            L.at(i).at(k) = (A.at(i).at(k) - suml) / U.at(k).at(k);
        }
    }

    return std::make_pair(L, U);
}

Matrix<double> CholeskyDecomposition(const Matrix<double>& A)
{
    const std::int32_t n = static_cast<std::int32_t>(A.size());
    Matrix<double> G{A};
    double sum{0.0};
    for (std::int32_t j{0}; j < n; ++j)
    {
        for (std::int32_t i{0}; i < n; ++i)
        {
            if (i < j)
            {
                G.at(i).at(j) = 0;
                continue;
            }

            sum = 0.0;
            for (std::int32_t k{0}; k < j; ++k)
            {
                sum += G.at(i).at(k) * G.at(j).at(k);
            }

            if ((A.at(i).at(i) - sum) < 0)
            {
                throw std::invalid_argument("Matrix A is not positive definite!");
            }

            if (i == j)
            {
                G.at(i).at(j) = std::sqrt(A.at(j).at(j) - sum);
            }
            else
            {
                G.at(i).at(j) = 1 / G.at(j).at(j) * (A.at(i).at(j) - sum);
            }
        }
    }

    return G;
}

}  // namespace matrix

}  // namespace nm
