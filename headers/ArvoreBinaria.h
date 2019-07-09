#ifndef _ARVBIN_H_
#define _ARVBIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arquivos.h"
#include "base.h"

//----STRUCTS--------
typedef struct NO tNo;
typedef tNo* ArvBin;
typedef struct NO{ 
    char* info; 
    ArvBin esq, dir;
    int ocorrencias;
    tIndiceLista *indices;
} tNo;

//----FUNCOES-------
ArvBin* cria_ArvBin();
char insere_ArvBin(ArvBin* raiz, char* palavra, int byte);
void destroi_ArvBin(ArvBin *raiz);
char consulta_ArvBin(ArvBin *raiz, char* palavra);
void emOrdem(ArvBin *raiz);

#endif
