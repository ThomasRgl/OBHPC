#!/bin/bash

# declare -a flags_list=("-O0 -march=native -mtune=native" "-O1 -march=native -mtune=native" "-O3 -march=native -mtune=native" "-Ofast -march=native -mtune=native" "-O2 -march=native -mtune=native" )
declare -a flags_list=("-O2 -march=native -mtune=native" "-O3 -march=native -mtune=native" "-Ofast -march=native -mtune=native" "-O1 -march=native -mtune=native" )
compilers="clang gcc aocc icx"
N_list="16 32 64 128"
nb_cc=$(echo ${compilers} | wc -w)

# nb_flags=$(echo ${flags_list} | wc -w)
# nb_flags= ${#flags_list[@]}

nb_flags=0;
for flags in "${flags_list[@]}" 
do
    nb_flags=$((nb_flags+1))
done
echo "nb_flags=${nb_flags}"

rm -Rf data/*
mkdir -p data
mkdir -p png
mkdir -p data/compiler
mkdir -p data/func
mkdir -p data/flags
rm -Rf png/*.png

for cc in $compilers; do
    
    echo "$cc"
    make -B CC=${cc}
    for N in $N_list; do
        
        
        echo "$N"
        taskset -c 4 ./dgemm ${N} 10 > data/${N}_${cc}_dgemm.dat
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
rm -Rf ${tmpfile}




i=1
for flags in "${flags_list[@]}"
do
    for cc in $compilers; do

        echo "$cc $i ${flags} "
        make -B CC=${cc} "OFLAGS=${flags}"

        for N in $N_list; do

            echo "$N"
            taskset -c 4 ./dgemm ${N} 10 > data/flags/${N}_${cc}_${i}_dgemm.dat
        done
    done
    i=$((i+1))
done

gnuplot -e "funcs='${funcs}';nb_cc=${nb_cc}"  plot2.gp



file=data/16_gcc_dgemm.dat
funcs=$(awk -F ';' "{print \$1 }" ${file} |  tr -s "\n" ";" | cut -d ';' -f 2- | tr -s ";" " ")
i=2

header="N"
for ((i = 1 ; i <= nb_flags ; i++)); do
    header="${header}; ${i}"
done

allFlags=""
for flags in "${flags_list[@]}"; do
    tmp=$(echo ${flags} | tr -s " " ",,")
    allFlags="${allFlags} ${tmp}"
done

ifunc=1
for func in $funcs; do
    mkdir -p data/flags/${func}
    for cc in $compilers; do
        out=data/flags/${func}/${cc}_dgemm.dat
        echo ${header} > ${out}
        for N in $N_list; do
            line="${N}"
            iflag=1
            for flags in "${flags_list[@]}"; do
                file=data/flags/${N}_${cc}_${iflag}_dgemm.dat
                line="${line};"
                # echo ";" >> ${out}
                val=$(awk -F ';' "{print \$11 }" ${file} | tr -s "\n" ";" | awk -F ';' "{print \$$((ifunc + 1)) }" )
                line="${line} ${val}"
                iflag=$((iflag+1))
            done
            echo ${line} >> ${out}
        done
    done
    ifunc=$((ifunc+1))
    echo ${allFlags}
    gnuplot -e "func='${func}';nb_cc='${nb_cc}';compilers='${compilers}';nb_flags='${nb_flags}';flags='${allFlags}'"  plot3.gp
done







