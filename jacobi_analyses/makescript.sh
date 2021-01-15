#!/bin/bash

rm -f mxv_omp

# Needs the -xreduction in order to work properly
cc -g -fast -xrestrict -xautopar -xloopinfo -xreduction -o mxv_omp mxv.c

echo "1 Thread"
time OMP_NUM_THREADS=1 ./mxv_omp 1000000 1000000
echo "2 Threads"
time OMP_NUM_THREADS=2 ./mxv_omp 1000000 1000000 
echo "4 Threads"
time OMP_NUM_THREADS=4 ./mxv_omp 1000000 1000000
