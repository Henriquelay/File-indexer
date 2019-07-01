#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../headers/arquivos.h"

//---- Structs -----
//Lista de ocorrências das palavras
typedef struct Lista tLista;
typedef struct Lista {
    char *palavra;
    int ocorrencias;
    tIndiceLista *indices;
    tLista *prox;
} tLista;

typedef struct ListaSent{
    int qtd;
    tLista *ini, *fim;
} tListaSent;


//------- Funções --------
tListaSent *inicia_ListaSent(void);
tLista *novo_no_Lista(char *str, int byte);
char insere_Lista(tListaSent *l, char *str, int byte);
char busca_Lista(char *pal, tListaSent *l);
char print_Lista(tListaSent *l);
char destroi_No(tLista *no);
char destroi_Lista(tListaSent *l);

#endif
