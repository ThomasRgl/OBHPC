#
set datafile separator ";"

set xlabel "cores"
set ylabel "GHZ" 


#####################################################

img1 = "core.png"
title1 = "mesure de la stabilité cpu"

##
set terminal "png" size 800,400
set output img1

#
set datafile separator ";"

# set xrange auto */
set auto x

#
set grid

#
#set title title1
#set key autotitle columnhead
set xlabel "cores id"
set ylabel "GHZ" 


plot "data/oneCore.dat" using 1:5 notitle
