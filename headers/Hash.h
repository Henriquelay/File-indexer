#ifndef _HASH_H_
#define _HASH_H

#include "Arquivos.h"
#include "ArvoreAVL.h"
#include "Base.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <ctype.h>

#define TAMDAHASH 93911
//um número primo grande arbitrário, se provou bem equilibrado independente do tamanho de arquivo trabalhado

//---- Structs -----
typedef struct Hash{
    ArvAVL *hash[TAMDAHASH];
    int colisoes, qtd;
    int *pesos;
} tHash;


//------- Funções --------
tHash *cria_Hash(void);
int* pesos_Lista(void);
int hash(int *pesos, char *str);
char insere_Hash(tHash *hashtable, char *palavra, int byte, char arq);
char consulta_Hash(tHash *hashtable, char *str);
void imprime_Hash(tHash *hashtable);
void destroi_Hash(tHash *hash);
int desempenho_Hash(int argc, char *argv[]);


#endif
