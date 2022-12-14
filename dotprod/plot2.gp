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
title1 = "DOTPROD : comparaison des différents compilateurs"

set yrange [0:15000]

##
set terminal "png" size 1600, 400
set output img1


#
set multiplot layout 1,3 rowsfirst title title1 
#set multiplot 


set xtic rotate by -45 scale 0 

do for [i=1:words(funcs)] { 
    set title  ''.word(funcs, i).'' 
    plot for [j=2:nb_cc+1] 'data/func/'.word(funcs, i).'_dotprod.dat' using j:xtic(1) 
    
    }
    

unset multiplot




