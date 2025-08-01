#! /bin/bash

NUMBER_OF_PROCESSES=4
if [ -n "$1" ]; then
  NUMBER_OF_PROCESSES=$1
fi

ls -lh
if [ ! -f jacobi/main ]; then
  echo "Error: main executable not found. Please build the project first."
  exit 1
fi

mpiexec -n $NUMBER_OF_PROCESSES ./jacobi/main
