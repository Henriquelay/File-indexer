#!/bin/bash

buscasRequest=(100 50000)

for i in ${buscasRequest[@]}; do
    ./LEIA_O_README ${i} data/APRENDE.txt > aprende_result.txt
done

for i in ${buscasRequest[@]}; do
    ./LEIA_O_README ${i} data/CommunistManifesto-KarlMarx.txt > manifesto_result.txt
done

# for i in ${buscasRequest[@]}; do
#     ./LEIA_O_README ${i} data/Bible.txt | tee biblia_result.txt
# done

# for i in ${buscasRequest[@]}; do
#     ./LEIA_O_README ${i} data/BibliusMaximus.txt | tee bibliamaxima_result.txt
# done
