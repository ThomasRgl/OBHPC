#!/bin/bash


mkdir -p data
mkdir -p png

rm -Rf data/*.dat
rm -Rf png/*.png

make -B 
# ./stability 10 
taskset -c 4 ./stability 1 > data/data.dat

gnuplot plot.gp
