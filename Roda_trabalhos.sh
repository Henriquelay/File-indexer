#!/bin/bash

buscasRequest=(100 50000 500000)

#for i in ${buscasRequest[@]}; do
#    echo Aprende com ${i} buscas | tee --append aprende_result.txt
#    ./LEIA_O_README ${i} data/APRENDE.txt | tee --append aprende_result.txt
#done

for i in ${buscasRequest[@]}; do
    echo Manifesto com ${i} buscas | tee --append manifesto_result.txt
    ./LEIA_O_README ${i} data/CommunistManifesto-KarlMarx.txt | tee --append manifesto_result.txt
done

for i in ${buscasRequest[@]}; do
    echo Biblia com ${i} buscas | tee --append manifesto_result.txt
    ./LEIA_O_README ${i} data/Bible.txt | tee --append biblia_result.txt
done

 for i in ${buscasRequest[@]}; do
    echo Biblia Maxima com ${i} buscas | tee --append manifesto_result.txt
     ./LEIA_O_README ${i} data/BibliusMaximus.txt | tee --append bibliamaxima_result.txt
 done
