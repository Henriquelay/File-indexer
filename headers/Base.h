#ifndef _BASE_H_
#define _BASE_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NPAL 100

// Para não ter que ficar realocando vetor de posições das palavra

typedef struct Indice tIndiceLista;
typedef struct Indice {
    size_t ind;
    tIndiceLista *prox, *ultimo;
} tIndiceLista;

typedef struct arquivo tArquivo;
typedef struct arquivo{
    char arquivo; //indice no argv onde está o nome do arquivo
    int qtd;
    tIndiceLista *ocorrencias;
    tArquivo *prox;
} tArquivo;

typedef struct Palavra {
    char *pal;
    tArquivo *arquivos;
} tPalavra;

// ------ Struct de Palavra --------
tPalavra *cria_Palavra(char *str, char arquivo, int ocorrencia);
void destroi_Palavra(tPalavra *pal);
char adiciona_IndicePal(tPalavra *pal, int byte, char arq);

// ------ Lista de Ocorrências da palavra no arquivo -------
char insere_Indice(tIndiceLista **l, int byte);
void imprime_Indices(tIndiceLista *l);
void destroi_Indices(tIndiceLista *l);

// ------ Lista de Arquivos da palavra -------
char insere_Arquivo(tArquivo **l, char arq);
void imprime_Arquivos(tArquivo *l);
void destroi_Arquivos(tArquivo *l);


#endif