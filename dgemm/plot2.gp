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
set boxwidth 0.75




img1 = "png/funcs.png"
title1 = "Il va falloir trouver un vrai titre"

set yrange [0:5000]

##
set terminal "png" size 1600,1600
set output img1


#
set multiplot layout 3,3 rowsfirst title title1 
#set multiplot 


set xtic rotate by -45 scale 0 

do for [i=1:words(funcs)] { 
    set title  ''.word(funcs, i).'' 
    plot for [j=2:3] 'data/func/'.word(funcs, i).'_dgemm.dat' using j:xtic(1) 
    
    }
    

unset multiplot




