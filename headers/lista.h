#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    char *palavra;
    int ocorrencias;
    tListaInt *indices;
    tLista *prox;
} tLista;

typedef struct ListaSent{
    int qtd;
    tLista *ini, *fim;
} tListaSent;

//------- Funções --------
tListaSent *inicia_ListaSent(void);
tLista *novo_no_Lista(char *str);
char insere_Lista(tListaSent *l, char *str);
char print_Lista(tListaSent *l);
char destroi_No(tLista *no);
char destroi_Lista(tListaSent *l);
#endif
