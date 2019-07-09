#ifndef _LISTA_H_
#define _LISTA_H_

#include "arquivos.h"
#include "base.h"

//---- Structs -----
typedef struct Lista tCelula;
typedef struct Lista {
    tPalavra *palavra;
    tCelula *prox;
} tCelula;

typedef struct ListaSent{
    int qtd;
    tCelula *ini, *fim;
} tLista;


//------- Funções --------
tLista *inicia_Lista(void);
tCelula *novo_no_Lista(char *str, int byte, char arq);
char insere_Lista(tLista *l, char *str, int byte, char arq);
char consulta_Lista(tLista *l, char* pal);
char print_Lista(tLista *l);
char destroi_No(tCelula *no);
char destroi_Lista(tLista *l);

#endif
