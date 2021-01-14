#!/bin/bash
ARGUMENTS="200 1000 1 0 2"

time ./poisson_j_serial $ARGUMENTS > serial_output.dat

echo "First done!"

export OMP_NUM_THREADS=4
time ./poisson_j $ARGUMENTS > parallel_output.dat

echo "Fuck you, sir."

