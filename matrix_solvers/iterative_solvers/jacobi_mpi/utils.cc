/*
 * Utility functions for the Jacobi method
 */

#include "jacobi/utils.h"
#include <cmath>

double *InitializeLaplaceMatrix(const std::int32_t N)
{
  double *host_A = new double[N * N];

  for (std::int32_t i = 0; i < N; ++i)
  {
    for (std::int32_t j = 0; j < N; ++j)
    {
      if (i == j)
      {
        host_A[j + N * i] = 2; // Diagonal elements
      }
      else if (std::abs(i - j) == 1 || std::abs(i - j) == N)
      {
        host_A[j + N * i] = -1; // Adjacent elements
      }
      else
      {
        host_A[j + N * i] = 0; // Other elements
      }
    }
  }
  return host_A;
}
