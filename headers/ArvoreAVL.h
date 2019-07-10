#ifndef _ARVAVL_H_
#define _ARVAVL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Arquivos.h"
#include "Base.h"
#include <time.h>

//----STRUCTS--------
typedef struct NoAVL tNoAVL;
typedef tNoAVL* ArvAVL;
typedef struct NoAVL{ 
    int altura;
    tPalavra *palavra;
    ArvAVL esq, dir;
} tNoAVL;

//----FUNCOES-------
ArvAVL* cria_ArvAVL();
char insere_ArvAVL(ArvAVL* raiz, char* palavra, int byte, char arq);
void destroi_ArvAVL(ArvAVL *raiz);
char consulta_ArvAVL(ArvAVL *raiz, char* palavra);
void emOrdem_ArvAVL(ArvAVL *raiz);
char strings_IguaisAVL(char *str1, char *str2);
int desempenho_ArvAVL(int argc, char *argv[]);

#endif 