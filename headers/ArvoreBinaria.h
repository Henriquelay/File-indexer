#ifndef _ARVBIN_H_
#define _ARVBIN_H_

#include "Arquivos.h"
#include "Base.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

//----STRUCTS--------
typedef struct NOBin tNoBin;
typedef tNoBin* ArvBin;
typedef struct NOBin{ 
    tPalavra *palavra;
    ArvBin esq, dir;
} tNoBin;

//----FUNCOES-------
ArvBin* cria_ArvBin();
char insere_ArvBin(ArvBin* raiz, char* palavra, int byte, char arq);
void destroi_ArvBin(ArvBin *raiz);
char consulta_ArvBin(ArvBin *raiz, char* palavra);
void emOrdem(ArvBin *raiz);
int desempenho_ArvBin(int argc, char *argv[]);

#endif
