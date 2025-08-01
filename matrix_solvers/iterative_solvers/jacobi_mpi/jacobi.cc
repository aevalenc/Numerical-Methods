/*
 * Jacobi iteration implementation
 */

#include "jacobi/jacobi.h"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <mpi.h>

void JacobiMPI(double *A, double *b, double *x, const std::int32_t n,
               const std::int32_t max_iter, const double tolerance,
               const std::int32_t world_rank, const std::int32_t world_size,
               const std::int32_t rows_for_this_process,
               const std::int32_t start_row, const std::int32_t *sendcounts_b,
               const std::int32_t *displacements_b)
{
  // Allocate memory for local solution vector
  double *local_x = new double[rows_for_this_process];
  std::int32_t global_index{0};
  bool converged{false};
  for (std::int32_t iter = 0; iter < max_iter; ++iter)
  {
    double local_sum = 0.0;
    for (std::int32_t i = 0; i < rows_for_this_process; ++i)
    {
      double sum = b[i];

      global_index = start_row + i;
      for (std::int32_t j = 0; j < n; ++j)
      {
        if (j != global_index)
        {
          sum -= A[i * n + j] * x[j];
        }
      }

      local_x[i] = sum / A[i * n + global_index];
      local_sum += std::abs(x[global_index] - local_x[i]);

      x[global_index] = local_x[i];
    }

    // Gather results from all processes
    double global_sum;
    MPI_Allreduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM,
                  MPI_COMM_WORLD);

    // Check convergence
    if (global_sum < tolerance && world_rank == ROOT_PROCESS_LABEL)
    {
      std::cout << "Jacobi iteration converged after " << iter + 1
                << " iterations." << std::endl;
      converged = true;
    }
    else if (world_rank == ROOT_PROCESS_LABEL)
    {
      std::cout << std::fixed << std::setprecision(4);
      std::cout << "Iteration: " << std::setw(4) << iter + 1
                << " | Global Sum Residual: " << global_sum << "\n";
    }
    MPI_Bcast(&converged, 1, MPI_C_BOOL, ROOT_PROCESS_LABEL, MPI_COMM_WORLD);

    if (world_rank == ROOT_PROCESS_LABEL && iter == max_iter - 1)
    {
      std::cout << "Maximum iterations reached (" << max_iter << ")."
                << "\n";
    }

    // Share the updated solution vector
    MPI_Allgatherv(x + start_row, rows_for_this_process, MPI_DOUBLE, x,
                   sendcounts_b, displacements_b, MPI_DOUBLE, MPI_COMM_WORLD);

    if (converged)
    {
      break;
    }
  }

  delete[] local_x;
}
