#! /bin/bash

NUMBER_OF_PROCESSES=4
if [ -n "$1" ]; then
  NUMBER_OF_PROCESSES=$1
fi

ls -lh
if [ ! -f matrix_solvers/iterative_solvers/jacobi_mpi/main ]; then
  echo "Error: main executable not found. Please build the project first."
  exit 1
fi

mpiexec -n $NUMBER_OF_PROCESSES ./matrix_solvers/iterative_solvers/jacobi_mpi/main
