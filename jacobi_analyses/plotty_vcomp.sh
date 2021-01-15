#!/bin/gnuplot

set terminal png enhanced size 1000,600
set output 'vcomp.png'

#set multiplot layout 1,2 #title "Beautiful plots"

set xlabel "Matrix Size"
set xtics [1:16]
set ytics [1:16]
set ylabel "Time"
set title "Compare Performance of Version 3 and 4"
plot "v3_data" using 1:2 title "Version3" with lp,\
     "v4_data" using 1:2 title "Version4" with lp

     


#pause mouse close
# This last line is to avoid the terminal to close 
# when you are not outputting to a file
