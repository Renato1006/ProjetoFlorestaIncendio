#!/bin/bash
date
gcc IncendioFloresta.c -lm -o floresta.out
time ./floresta.out

rm -r Gif

mkdir Gif

t="$(cat TempoFinal.dat)"

for i in $(seq 0 $t)
do
 	mv  Malha$i.dat Gif
done

cp G.gp Gif

cd Gif
gnuplot G.gp

for i in $(seq 0 $t)
do
 	rm  Malha$i.dat
done
rm G.gp
cd ..

date
