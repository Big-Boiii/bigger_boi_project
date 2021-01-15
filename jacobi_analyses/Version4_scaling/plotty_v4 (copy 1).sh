#!/bin/gnuplot

set terminal png enhanced size 1000,600
set output 'overhead.png'

#set multiplot layout 1,2 #title "Beautiful plots"

set xlabel "Number of Threads"
set xrange [1:16]
#set yrange [1:16]
#set xtics 1,16
#set ytics 1,16
set ylabel "Scaling factor"
set title "Scaling of the function"
plot "version4_data" using 1:(6.048/$2) title "size100"  with lp,\
     "version4_data" using 1:(1/((0.97/$1)-0.97)) title "Theoretical" with lp
    


#pause mouse close
# This last line is to avoid the terminal to close 
# when you are not outputting to a file
