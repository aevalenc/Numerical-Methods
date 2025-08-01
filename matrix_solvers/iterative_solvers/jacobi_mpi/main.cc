/*
 * Main program for testing Jacobi iteration
 */

#include "jacobi/jacobi.h"
#include "jacobi/utils.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <mpi.h>
#include <time.h>

const std::int32_t max_iter = 1e6;
const double tolerance = 1e-3;
const std::int32_t n = 501;

int main()
{

  // Initialize MPI
  MPI_Init(NULL, NULL);

  // Get the number of processes
  std::int32_t world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  std::int32_t world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  double *A = nullptr;
  double *b = nullptr;
  double *x = new double[n];
  if (world_rank == 0)
  {
    std::cout << "\n";

    // Example matrix and vectors for Jacobi iteration
    A = InitializeLaplaceMatrix(n);
    b = new double[n];
    for (std::int32_t i = 0; i < n; ++i)
    {
      if (i == 0)
      {
        b[i] = 200.0;
      }
      else if (i == n - 1)
      {
        b[i] = 400.0;
      }
      else
      {
        b[i] = 0.0;
      }
    }

    for (std::int32_t i = 0; i < n; ++i)
    {
      x[i] = 0.0; // Initial guess
    }
  }

  // Divide the work among processes
  std::int32_t base_rows = n / world_size;
  std::int32_t remainder = n % world_size;
  std::int32_t start_row =
      world_rank * base_rows + std::min(world_rank, remainder);
  std::int32_t rows_for_this_process =
      base_rows + (world_rank < remainder ? 1 : 0);
  std::int32_t end_row = start_row + rows_for_this_process;

  std::int32_t *sendcounts_A = new std::int32_t[world_size];
  std::int32_t *displacements_A = new std::int32_t[world_size];
  std::int32_t *sendcounts_b = new std::int32_t[world_size];
  std::int32_t *displacements_b = new std::int32_t[world_size];
  for (std::int32_t i = 0; i < world_size; ++i)
  {
    std::int32_t rows = base_rows + (i < remainder ? 1 : 0);
    sendcounts_A[i] = rows * n;
    displacements_A[i] = (i * base_rows + std::min(i, remainder)) * n;
    sendcounts_b[i] = rows;
    displacements_b[i] = i * base_rows + std::min(i, remainder);
  }

  // Initialize local buffers for submatrix and vector
  const auto local_A = new double[(end_row - start_row) * n];
  const auto local_b = new double[(end_row - start_row)];

  // Send submatrix and vector to each process
  MPI_Scatterv(A, sendcounts_A, displacements_A, MPI_DOUBLE, local_A,
               (end_row - start_row) * n, MPI_DOUBLE, ROOT_PROCESS_LABEL,
               MPI_COMM_WORLD);
  MPI_Scatterv(b, sendcounts_b, displacements_b, MPI_DOUBLE, local_b,
               (end_row - start_row), MPI_DOUBLE, ROOT_PROCESS_LABEL,
               MPI_COMM_WORLD);
  MPI_Bcast(x, n, MPI_DOUBLE, ROOT_PROCESS_LABEL, MPI_COMM_WORLD);

  const auto start = MPI_Wtime();
  JacobiMPI(local_A, local_b, x, n, max_iter, tolerance, world_rank, world_size,
            rows_for_this_process, start_row, sendcounts_b, displacements_b);
  const auto end = MPI_Wtime();
  const double elapsed_time = end - start;
  if (world_rank == ROOT_PROCESS_LABEL)
  {
    std::cout << "Jacobi iteration completed in " << elapsed_time
              << " seconds.\n";
  }

  if (world_rank == ROOT_PROCESS_LABEL)
  {
    delete[] A;
    delete[] b;
  }

  delete[] x;
  delete[] local_A;
  delete[] local_b;
  delete[] sendcounts_A;
  delete[] displacements_A;
  delete[] sendcounts_b;
  delete[] displacements_b;

  // Finalize MPI
  MPI_Finalize();

  return 0;
}
