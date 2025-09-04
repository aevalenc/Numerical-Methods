/*
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 *
 * Doolittle decomposition of linear system of equations
 */

#include "matrix_solvers/decomposition_methods/doolittle.h"
#include "matrix_solvers/utilities.h"
#include <cstdint>

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

}  // namespace matrix

}  // namespace nm
