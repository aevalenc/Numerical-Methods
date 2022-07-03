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
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>

namespace nm
{

namespace matrix
{

void BackwardsSubstitution(const std::vector<std::vector<double>> &A,
                           std::vector<double> &x, const std::vector<double> &b)
{

  auto n = static_cast<int>(x.size() - 1);
  x[n] = b[n] / A[n][n];

  auto i_row_of_A = std::crbegin(A);
  int j{};
  for (auto i = n - 1; i > -1; i--)
  {
    i_row_of_A++;
    j = (i - 1);
    const auto sum =
        std::inner_product(std::cbegin(*i_row_of_A) + j, std::cend(*i_row_of_A),
                           std::cbegin(x) + j, 0.0);
    x[i] = (b[i] - sum) / A[i][i];
  }
}

} // namespace matrix

} // namespace nm
