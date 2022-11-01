#!/bin/bash


compilers="clang gcc"
N_list="16 32 64 128"

mkdir -p data
mkdir -p png
mkdir -p data/compiler
mkdir -p data/func
rm -Rf png/*.png

for cc in $compilers; do
    
    for N in $N_list; do
        
        echo "$cc"
        make -B CC=${cc}
        
        echo "$N"
        ./dgemm ${N} 10 > data/${N}_${cc}_dgemm.dat
    done
done


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

file=data/16_gcc_dgemm.dat
tmpfile=data/func/tmp.dat


funcs=$(awk -F ';' "{print \$1 }" ${file} |  tr -s "\n" ";" | cut -d ';' -f 2- | tr -s ";" " ")
i=2
for f in $funcs; do
    out=data/func/${f}_dgemm.dat
    cut -d ';' -f1 data/compiler/gcc_dgemm.dat > ${out}
    for cc in $compilers; do
        cut -d ';' -f${i} data/compiler/${cc}_dgemm.dat | sed -e "1 s/^[^\n]*/${cc}/" | paste -d ";" ${out} - > ${tmpfile}
        cat ${tmpfile} > ${out} 
    done 
    i=$((i+1))
done
rm ${tmpfile}
gnuplot -e "funcs='${funcs}'" plot2.gp






