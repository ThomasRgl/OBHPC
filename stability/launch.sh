#!/bin/bash

N="100000"
core=$(grep -c ^processor /proc/cpuinfo)
samples="10000"

make -B CC=clang

./oneCore ${N} 1 ${samples} > data/oneCore.dat



for ((id = 1 ; id < ${core} ; id++)); do
    ./multiCore ${N} 5000 ${id} > data/${id}_Core.dat
     
    # c=1
    # 
    # file=data/${id}_Core.dat
    # out=data/${id}_t_Core.dat
    # # num_lines=$(wc -l < "$file")
    # echo ""> ${out}
    # num_column=$(head -1 ${file} | sed 's/[^;]//g' | wc -c)
    # for ((i=0; i<num_column - 1; i++)) {
    #     awk -F ';' "{print \$(( ${i}+1 )) }" ${file} | tr -s "\n" ";" | tr -s " " " " >> ${out} 
    #     echo >> ${out}
    # }

done

gnuplot -e "core=${core}" stability.gp 




