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




img1 = "png/".func.".png"
title1 = "DGEMM : Comparaison des différents Oflag sur ". func

set yrange [0:5000]

##
set terminal "png" size 1600,1600
set output img1


#
set multiplot layout nb_cc,1 rowsfirst title title1 
#set multiplot 


set xtic rotate by -45 scale 0 

do for [i=1:words(compilers)] { 
    set title  ''.word(compilers, i).'' 
    plot for [j=2:nb_flags+1] 'data/flags/'.func.'/'.word(compilers, i).'_dgemm.dat' using j:xtic(1) t word(flags,j-1)
    
    }
    

unset multiplot




