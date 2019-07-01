#ifndef _ARQUIVOS_H_
#define _ARQUIVOS_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define NPAL 100  //tamanho máximo da string (buffer da função de leitura)

//------ Structs --------
// Para não ter que ficar realocando vetor de posições das palavra
typedef struct Indice tIndiceLista;
typedef struct Indice {
    int ind;
    tIndiceLista *prox, *ultimo;
} tIndiceLista;

// ------ Funçoes -------
char abre_Arquivo(char *path, FILE **arquivo);
char fecha_Arquivo(FILE *arquivo);
char pega_Palavra(FILE *arquivo, char *str, int *byte);

// ------ Lista de Ocorreências da palavra -------
char insere_Indice(tIndiceLista **l, int byte);
void imprime_Indices(tIndiceLista *l);
void destroi_Indices(tIndiceLista *l);

#endif
