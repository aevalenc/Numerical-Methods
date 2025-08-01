/*
 * Jacobi iteration implementation
 */

#ifndef JACOBI_JACOBI_H
#define JACOBI_JACOBI_H

#define ROOT_PROCESS_LABEL 0

#include <cstdint>

void JacobiMPI(double *A, double *b, double *x, const std::int32_t n,
               const std::int32_t max_iter, const double tolerance,
               const std::int32_t world_rank, const std::int32_t world_size,
               const std::int32_t rows_for_this_process,
               const std::int32_t start_row, const std::int32_t *sendcounts_b,
               const std::int32_t *displacements_b);

#endif // JACOBI_JACOBI_H
