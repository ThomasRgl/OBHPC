#!/bin/bash

N="100000"
core=$(grep -c ^processor /proc/cpuinfo)
samples="10000"

make -B CC=clang

./oneCore ${N} 1 ${samples} > data/oneCore.dat


gnuplot  stability.gp 




