#ifndef _LISTA_H_
#define _LISTA_H_

#include "palavra.h"


//------ Structs --------
// Para não ter que ficar realocando vetor de posições das palavras
typedef struct ListaInt tListaInt;
typedef struct ListaInt{
    int info;
    tListaInt *prox;
} tListaInt;

//Lista de ocorrências das palavras
typedef struct Lista tLista;
typedef struct Lista {
    tPalavra palavra;
    int ocorrencias;
    tListaInt *coluna, *linha;
    tLista *prox;
} tLista;

typedef struct ListaSent{
    int qtd;
    tLista *ini, *fim;
} tListaSent;

//------- Funções --------
tListaSent *inicia_ListaSent(void);
tLista *novo_no_Lista(tPalavra *pal);
char insere_Lista(tListaSent *l, char *str);
#endif
