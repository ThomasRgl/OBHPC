#!/bin/bash


compilers="clang gcc"
N_list="16 32 64 128"

mkdir -p data
mkdir -p png
rm png/*.png

for cc in $compilers; do
    
    for N in $N_list; do
        
        echo "$cc"
        make -B CC=${cc}
        
        echo "$N"
        ./dgemm ${N} 10 > data/${N}_${cc}_dgemm.dat
    done
done

mkdir -p data/compiler

for cc in $compilers; do
    
    out=data/compiler/${cc}_dgemm.dat
    awk -F ';' "{print \$1 }" data/16_${cc}_dgemm.dat |\
        tr -s "\n" ";" | tr -s " " " " |\
        sed -e '1 s/^[^;]*/N/' > ${out}

    echo "" >> ${out}
    
    for N in $N_list; do
        file=data/${N}_${cc}_dgemm.dat
        
        awk -F ';' "{print \$11 }" ${file} |\
            tr -s "\n" ";" | tr -s " " " " |\
            sed -e "1 s/^[^;]*/${N}/" >> ${out}
        echo "" >> ${out}
    
    done
    
    gnuplot -e "source='${out}';cc='${cc}'" plot.gp

done


#
# make -B CC=gcc
#
# echo "128"
# ./dgemm 128 10 > data/128_gcc_dgemm.dat
#
# echo "64"
# ./dgemm 64 10 > data/128_gcc_dgemm.dat
#
# echo "32"
# ./dgemm 32 10 > data/128_gcc_dgemm.dat
#
# echo "16"
# ./dgemm 16 10 > data/128_gcc_dgemm.dat
#
#
# graph pour clang chaque fonction 16 128
# graph pour gcc chaque fonction 16 128
#

