#ifndef _ARVAVL_H_
#define _ARVAVL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arquivos.h"

//----STRUCTS--------
typedef struct NO{ 
    char* info; 
    int altura;
    struct NO *esq;
    struct NO *dir;
    int ocorrencias;
    tIndiceLista *indices;
} tNo;
typedef tNo* ArvAVL;

//----FUNCOES-------
ArvAVL* cria_ArvAVL();
char insere_ArvAVL(ArvAVL* raiz, char* valor, int byte);
void destroi_ArvAVL(ArvAVL *raiz);
char consulta_ArvAVL(ArvAVL *raiz, char* valor);
void emOrdem(ArvAVL *raiz);

#endif