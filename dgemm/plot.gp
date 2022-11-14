#
set datafile separator ";"

#
set grid

#
set key autotitle columnhead
set ylabel "MiB/s"
set xlabel "size" 

#set key right top

set style data histogram
set style fill solid border -1
set boxwidth 0.5



set xtic rotate by -45 scale 0 

img1 = "png/".cc.".png"
title1 = "DGEMM : Comparaison des différentes fonctions compilées avec ". cc

##
set terminal "png" size 800,400
set output img1

plot for [i=2:10] source using i:xtic(1) 

    





