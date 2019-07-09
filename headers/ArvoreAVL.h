#ifndef _ARVAVL_H_
#define _ARVAVL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arquivos.h"
#include "base.h"

//----STRUCTS--------
typedef struct NO tNo;
typedef tNo* ArvAVL;
typedef struct NO{ 
    int altura;
    tPalavra *palavra;
    ArvAVL esq, dir;
} tNo;

//----FUNCOES-------
ArvAVL* cria_ArvAVL();
char insere_ArvAVL(ArvAVL* raiz, char* palavra, int byte, char arq);
void destroi_ArvAVL(ArvAVL *raiz);
char consulta_ArvAVL(ArvAVL *raiz, char* palavra);
void emOrdem(ArvAVL *raiz);
char strings_Iguais(char *str1, char *str2);

#endif