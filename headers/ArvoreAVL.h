#ifndef _ARVAVL_H_
#define _ARVAVL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arquivos.h"
#include "base.h"

//----STRUCTS--------
typedef struct NO tNO;
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
char insere_ArvAVL(ArvAVL* raiz, char* palavra /*, int byte*/);
void destroi_ArvAVL(ArvAVL *raiz);
char consulta_ArvAVL(ArvAVL *raiz, char* palavra);
void emOrdem(ArvAVL *raiz);
char strings_Iguais(char *str1, char *str2);

#endif