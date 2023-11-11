/*
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 *
 * Doolittle decomposition of linear system of equations
 */

#include "matrix_solvers/direct_solvers/doolittle.h"

namespace nm
{
namespace matrix_solvers
{

int Doolittle(std::vector<double>& A, std::vector<double>& L, std::vector<double>& U)
{

    /* Declarations */
    int k, m, i, j;
    double tempu, templ, sumu, suml;

    /* Set Identity Matrix */
    eye(L, n);

    /* Main Algorithm */
    for (k = 0; k < n; k++)
    {

        // Upper Triangular Matrix
        for (m = k; m < n; m++)
        {
            sumu = 0.0;
            for (j = 0; j < k; j++)
            {
                tempu = L[j + n * k] * U[m + n * j];
                sumu = sumu + tempu;
            }  // end for j

            U[m + n * k] = A[m + n * k] - sumu;
        }  // end for m

        // Lower Triangular Matrix
        //  Recall principle diagonal (i,i) are 1s
        for (i = k + 1; i < n; i++)
        {
            suml = 0.0;
            for (j = 0; j < k; j++)
            {
                templ = L[j + n * i] * U[k + n * j];
                suml = suml + templ;
            }  // end for j

            L[k + n * i] = (A[k + n * i] - suml) / U[k + n * k];
        }  // end for i

    }  // end for k

    return 0;
}
}  // namespace matrix_solvers
}  // namespace nm
