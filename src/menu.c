#include "../headers/Lista.h"
#include "../headers/ArvoreBinaria.h"
#include "../headers/ArvoreAVL.h"
#include "../headers/Hash.h"
#include "../headers/Trie.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        puts("Faltam argumentos!");
        return 1;
    }
    int nBuscas = atoi(argv[1]);
    if(nBuscas < 1) {puts("Deu ruim ae"); return 1;}
    puts("Lista:");
    desempenho_Lista(argc, argv);
    puts("ArvBin");
    desempenho_ArvBin(argc, argv);
    puts("ArvAVL:");
    desempenho_ArvAVL(argc, argv);
    puts("Hash:");
    desempenho_Hash(argc, argv);
    puts("ArvTrie:");
    desempenho_Trie(argc, argv);
    return 0;
}