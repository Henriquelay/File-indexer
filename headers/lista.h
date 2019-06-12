#ifndef _LISTA_H_
#define _LISTA_H_

#include "palavra.h"

// Para não ter que ficar realocando vetor de posições das palavras
typedef struct ListaInt ListaInt;
typedef struct ListaInt{
    int info;
    ListaInt *prox;
}

//Lista de ocorrências das palavras
typedef struct Lista Lista;
typedef struct Lista {
    tPalavra palavra;
    int ocorrencias;
    ListaInt *coluna, *linha;
    Lista *prox;
} tLista;

typedef struct ListaSent{
    int qtd;
    Lista *ini, *fim;
} tListaSent
#endif
