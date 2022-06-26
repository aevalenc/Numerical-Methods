/*
 * Author: Alejandro Valencia
 * Project: Backwards Substitution Matrix Solver
 *
 * This function performs a backwards substitution algorithm to solve
 * the matrix equation Ax = b, where A is an UPPER triangular matrix.
 *
 * This function requires the following inputs
 *
 *     A: The upper triangular matrix (square n x n)
 *     x: The array where the results will be placed (column n x 1)
 *     b: The right hand side of the matrix equation (column n x 1)
 *
 */

#include "backwards_substitution.h"

namespace nm {

namespace matrix {

void BackwardsSubstitution(const std::vector<std::vector<double>> &A,
                           std::vector<double> &x,
                           const std::vector<double> &b) {

  const auto n = static_cast<int>(A.size());
  for (int i = n - 1; i > -1; i--) {
    x[i] = b[i];

    if (i != n - 1) {
      for (int j = i + 1; j < n; j++) {
        x[i] = x[i] - A[i][j] * x[j];
      } // end for j

    } // end if

    x[i] = x[i] / A[i][i];

  } // end for i
}

} // namespace matrix

} // namespace nm
