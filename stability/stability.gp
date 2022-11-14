#core=12
img1 = "multicore.png"
title1 = "mesure de stabilité sur n cpu en parallèle"

##
set terminal "png" size 800,400
set output img1

#
set datafile separator ";"

#
set grid

#
#set title title1
#set key autotitle columnhead
set xlabel "cores"
set ylabel "GHZ" 

#
set xrange [0:core]
set yrange [0:5]

#set key right top

#set style data histogram
#set style fill solid border -1
#set boxwidth 0.5


#set xtic rotate by -45 scale 0 

demiCore=core/2
quartCore=core/4
set multiplot layout quartCore,4 rowsfirst title title1 


#plot  "data/3_Core.dat" using 1:5 
do for [i=1:core-1] {
    plot "data/".i."_Core.dat" using 1:5 notitle lw 2
    } 
unset multiplot


#####################################################

img1 = "core.png"
title1 = "mesure de stabilité cpu"

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
set title title1
#set key autotitle columnhead
set xlabel "cores id"
set ylabel "GHZ" 


plot "data/oneCore.dat" using 1:5 notitle
