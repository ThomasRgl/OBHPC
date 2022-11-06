#
set datafile separator ";"

#
set grid

#
set key autotitle columnhead
set ylabel "cycles"
set xlabel "size" 

set logscale x 2


set xtic rotate by -45 scale 0 

img1 = "png/image.png"
title1 = "jsp"

##
set terminal "png" size 800,400
set output img1

plot \
    "data/data.dat" using 2:7 w lp,\
    "data/data.dat" using 2:8 w lp,\
    "data/data.dat" using 2:9 w lp

    





