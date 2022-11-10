#!/bin/bash
# declare -a flags_list=("-O0 -march=native -mtune=native" "-O1 -march=native -mtune=native" "-O3 -march=native -mtune=native" "-Ofast -march=native -mtune=native" "-O2 -march=native -mtune=native" )
declare -a flags_list=("-O1 -march=native -mtune=native" "-O3 -march=native -mtune=native" "-Ofast -march=native -mtune=native" "-O2 -march=native -mtune=native" )
compilers="clang gcc aocc icx"
# N_list="100 1000 10000 100000"
N_list="1000 10000  100000 1000000 "


# 
nb_cc=$(echo ${compilers} | wc -w)

nb_flags=0;
for flags in "${flags_list[@]}" 
do
    nb_flags=$((nb_flags+1))
done

echo "nb_flags=${nb_flags}"

#
rm -Rf data/*.dat

rm -Rf png/*.png
mkdir -p data
mkdir -p png
mkdir -p data/compiler
mkdir -p data/func
mkdir -p data/flags


i=1
for flags in "${flags_list[@]}"
do
    for cc in $compilers; do

        echo "$cc $i ${flags} "
        make -B CC=${cc} "OFLAGS=${flags}"

        for N in $N_list; do

            echo "$N"
            taskset -c 4 ./dotprod ${N} 10 > data/${N}_${cc}_${i}_dotprod.dat
        done
    done
    i=$((i+1))
done

files=(data/*)
_file="${files[0]}"
funcs=$(awk -F ';' "{print \$1 }" ${_file} |  tr -s "\n" ";" | cut -d ';' -f 2- | tr -s ";" " ")

echo "func: ${funcs}"


for cc in $compilers; do
    
    out=data/compiler/${cc}_dotprod.dat
    awk -F ';' "{print \$1 }" ${_file} |\
        tr -s "\n" ";" | tr -s " " " " |\
        sed -e '1 s/^[^;]*/N/' > ${out}

    echo "" >> ${out}
    
    for N in $N_list; do
        file=data/${N}_${cc}_1_dotprod.dat
         
        awk -F ';' "{print \$12 }" ${file} |\
            tr -s "\n" ";" | tr -s " " " " |\
            sed -e "1 s/^[^;]*/${N}/" >> ${out}
        echo "" >> ${out}
    
    done
    
    gnuplot -e "source='${out}';cc='${cc}'" plot.gp

done





tmpfile=data/func/tmp.dat
files=(data/compiler/*)
__file="${files[0]}"


i=2
for f in $funcs; do
    out=data/func/${f}_dotprod.dat
    cut -d ';' -f1 ${__file} > ${out}
    for cc in $compilers; do
        cut -d ';' -f${i} data/compiler/${cc}_dotprod.dat | sed -e "1 s/^[^\n]*/${cc}/" | paste -d ";" ${out} - > ${tmpfile}
        cat ${tmpfile} > ${out} 
    done 
    i=$((i+1))
done
rm -Rf ${tmpfile}




gnuplot -e "funcs='${funcs}';nb_cc=${nb_cc}"  plot2.gp




###################################################

i=2
header="N"
for ((i = 1 ; i <= nb_flags ; i++)); do
    header="${header}; ${i}"
done



# 
allFlags=""
for flags in "${flags_list[@]}"; do
    tmp=$(echo ${flags} | tr -s " " ",,")
    allFlags="${allFlags} ${tmp}"
done
ifunc=1
for func in $funcs; do
    mkdir -p data/flags/${func}
    for cc in $compilers; do
        out=data/flags/${func}/${cc}_dotprod.dat
        echo ${header} > ${out}
        for N in $N_list; do
            line="${N}"
            iflag=1
            for flags in "${flags_list[@]}"; do
                file=data/${N}_${cc}_${iflag}_dotprod.dat
                line="${line};"
                # echo ";" >> ${out}
                val=$(awk -F ';' "{print \$12 }" ${file} | tr -s "\n" ";" | awk -F ';' "{print \$$((ifunc + 1)) }" )
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







