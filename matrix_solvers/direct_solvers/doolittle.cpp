/*
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 *
 * Doolittle decomposition of linear system of equations
 */

#include "matrix_solvers/direct_solvers/doolittle.h"
#include "matrix_solvers/utilities.h"

namespace nm
{

namespace matrix
{

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> Doolittle(
    const std::vector<std::vector<double>>& A)
{

    /* Declarations */
    int m, i, j;
    double tempu, templ, sumu, suml;

    /* Set Identity Matrix */
    auto L = CreateIdentityMatrix(static_cast<std::int32_t>(A.size()));
    auto U = CreateIdentityMatrix(static_cast<std::int32_t>(A.size()));

    /* Main Algorithm */
    for (std::int32_t k{0}; k < A.size(); ++k)
    {

        // Upper Triangular Matrix
        for (m = k; m < A.size(); ++m)
        {
            sumu = 0.0;
            for (j = 0; j < k; ++j)
            {
                tempu = L.at(k).at(j) * U.at(j).at(m);
                sumu = sumu + tempu;
            }

            U.at(k).at(m) = A.at(k).at(m) - sumu;
        }

        // Lower Triangular Matrix
        //  Recall principle diagonal (i,i) are 1s
        for (i = k + 1; i < A.size(); i++)
        {
            suml = 0.0;
            for (j = 0; j < k; j++)
            {
                templ = L.at(i).at(j) * U.at(j).at(k);
                suml = suml + templ;
            }

            L.at(i).at(k) = (A.at(i).at(j) - suml) / U.at(k).at(k);
        }
    }

    return std::make_pair(L, U);
}

}  // namespace matrix

}  // namespace nm
