#!/bin/bash

#BSUB -q hpcintro 
#BSUB -W 30
#BSUB -n 24

for ((i=1; i<=16; i++))
do
    for((j=50; j<=125; j=j+75))
    do
	echo "Size" $j
	echo "Threads" $i
	export OMP_NUM_THREADS=$i OMP_SCHEDULE=static,1
	time ./poisson_gs_second $j 1500 5 0 0 
    done
done
