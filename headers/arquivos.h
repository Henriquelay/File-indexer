#ifndef _ARQUIVOS_H_
#define _ARQUIVOS_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NPAL 100  //tamanho máximo da string (buffer da função de leitura)

//------ Structs --------
// Para percorrer e selecionar palavras aleatorias
typedef struct ListaNaoTratada tListaNaoTratada;
typedef struct ListaNaoTratada{
    char *palavra;
    tListaNaoTratada *prox;
} tListaNaoTratada;

// Para não ter que ficar realocando vetor de posições das palavra
typedef struct Indice tIndiceLista;
typedef struct Indice {
    size_t ind;
    tIndiceLista *prox, *ultimo;
} tIndiceLista;

typedef struct ListaNaoTratadaSent{
    tListaNaoTratada *ini, *fim;
    int qtd;
} tListaNaoTratadaSent;

typedef struct arquivo tArquivo;
typedef struct arquivo{
    char arquivo; //indice no argv onde está o nome do arquivo
    int qtd;
    tIndiceLista *ocorrencias;
    tArquivo *prox;
} tArquivo;

// ------ Funçoes -------
char abre_Arquivo(char *path, FILE **arquivo);
int tamanhoArquivo(FILE *arquivo);
char fecha_Arquivo(FILE *arquivo);
char pega_Palavra(FILE *arquivo, char *str, int *byte);
char eValido(char c);

// ------ Lista de Ocorrências da palavra no arquivo -------
char insere_Indice(tIndiceLista **l, int byte);
void imprime_Indices(tIndiceLista *l);
void destroi_Indices(tIndiceLista *l);

// ------ Lista de Arquivos da palavra -------
char insere_Arquivo(tArquivo **l, char arq);
void imprime_Arquivos(tArquivo *l);
void destroi_Arquivos(tArquivo *l);

// ------ Lista não tratada de palavras (para o programa testador) ------
char insere_ListaNaoTratadaSent(tListaNaoTratadaSent *l, char *str);
void destroi_ListaNaoTratadaSent(tListaNaoTratadaSent *l);
tListaNaoTratadaSent *inicia_ListaNaoTratadaSent(void);

#endif
