#ifndef _ARVBIN_H_
#define _ARVBIN_H_

#include "arquivos.h"
#include "base.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//----STRUCTS--------
typedef struct NO tNo;
typedef tNo* ArvBin;
typedef struct NO{ 
    tPalavra *palavra;
    ArvBin esq, dir;
} tNo;

//----FUNCOES-------
ArvBin* cria_ArvBin();
char insere_ArvBin(ArvBin* raiz, char* palavra, int byte, char arq);
void destroi_ArvBin(ArvBin *raiz);
char consulta_ArvBin(ArvBin *raiz, char* palavra);
void emOrdem(ArvBin *raiz);

#endif
