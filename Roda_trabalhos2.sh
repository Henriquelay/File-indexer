#!/bin/bash

buscasRequest=(100 50000 100000 500000 1000000)

#for i in ${buscasRequest[@]}; do
#    ./LEIA_O_README ${i} data/APRENDE.txt | tee aprende_result.txt
#done

#for i in ${buscasRequest[@]}; do
#    ./LEIA_O_README ${i} data/CommunistManifesto-KarlMarx.txt | tee manifesto_result.txt
#done

for i in ${buscasRequest[@]}; do
     ./LEIA_O_README ${i} data/Bible.txt | tee biblia_result.txt
done

for i in ${buscasRequest[@]}; do
     ./LEIA_O_README ${i} data/BibliusMaximus.txt | tee bibliamaxima_result.txt
done
