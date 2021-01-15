#!/bin/bash

#BSUB -q hpcintro 
#BSUB -W 30
#BSUB -n 24 

for ((i=1; i<=16; i++))
do
    for((j=100; j<=175; j=j+75))
    do
	echo "Size" $j
	echo "Threads" $i
	time OMP_NUM_THREADS=$i ./poisson_j_4 $j 1500 5 0 0 
    done
done
