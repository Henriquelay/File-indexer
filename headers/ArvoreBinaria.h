#ifndef _ARVBIN_H_
#define _ARVBIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//----STRUCTS--------
typedef struct NO* ArvBin;
typedef struct NO{ 
    char* info; 
    struct NO *esq; 
    struct NO *dir; 
} tNo;

//----FUNCOES-------
ArvBin* cria_ArvBin();
char insere_ArvBin(ArvBin* raiz, char* valor);
void destroi_ArvBin(ArvBin *raiz);
char consulta_ArvBin(ArvBin *raiz, char* valor);

#endif
