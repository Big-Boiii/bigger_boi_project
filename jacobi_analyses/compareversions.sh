#!/bin/bash
# 02614 - High-Performance Computing, January 2018
# 
# batch script to run collect on a decidated server in the hpcintro
# queue
#
# Author: Bernd Dammann <bd@cc.dtu.dk>
#
#BSUB -J collector
#BSUB -o compare.out
#BSUB -q hpcintro
#BSUB -n 24
#BSUB -R "rusage[mem=2048]"
#BSUB -W 30

# define the driver name to use
# valid values: matmult_c.studio, matmult_f.studio, matmult_c.gcc or
# matmult_f.gcc
#
EXECUTABLE1=poisson_j_3
EXECUTABLE2=poisson_j_4


for ((c=50; c<=500; c=c+50))
do
    echo $c
    time OMP_NUM_THREADS=8 $EXECUTABLE1 $c 1000000 10 0 0
    time OMP_NUM_THREADS=8 $EXECUTABLE2 $c 1000000 10 0 0
    
done


