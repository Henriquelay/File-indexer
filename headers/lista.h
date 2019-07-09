#ifndef _LISTA_H_
#define _LISTA_H_

#include "arquivos.h"
#include "base.h"

//---- Structs -----
typedef struct Lista tLista;
typedef struct Lista {
    tPalavra *palavra;
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
char consulta_Lista(tListaSent *l, char* pal);
char print_Lista(tListaSent *l);
char destroi_No(tLista *no);
char destroi_Lista(tListaSent *l);

#endif
