#ifndef _HASH_H_
#define _HASH_H

#include "arquivos.h"
#include "ArvoreAVL.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <ctype.h>

#define TAMDAHASH 93911

//---- Structs -----
typedef struct Hash{
    ArvAVL *hash[TAMDAHASH];
    int colisoes, qtd;
    int *pesos;
} tHash;


//------- Funções --------
tHash *cria_TabelaHash(void);
int* pesos_Lista(void);
int hash(int *pesos, char *str);
char insere_Hash(tHash *hashtable, char *palavra, int byte, char arq);

#endif
