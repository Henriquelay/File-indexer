#ifndef _ARQUIVOS_H_
#define _ARQUIVOS_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NPAL 100  //tamanho máximo da string (buffer da função de leitura)

//------ Structs --------
// Para não ter que ficar realocando vetor de posições das palavra
typedef struct Indice tIndiceLista;
typedef struct Indice {
    int ind;
    tIndiceLista *prox, *ultimo;
} tIndiceLista;

// Para percorrer e 
typedef struct ListaNaoTratada tListaNaoTratada;
typedef struct ListaNaoTratada{
    char *palavra;
    tListaNaoTratada *prox, *ultimo;
    int qtd;
} tListaNaoTratada;

// ------ Funçoes -------
char abre_Arquivo(char *path, FILE **arquivo);
char fecha_Arquivo(FILE *arquivo);
char pega_Palavra(FILE *arquivo, char *str, int *byte);

// ------ Lista de Ocorrências da palavra -------
char insere_Indice(tIndiceLista **l, int byte);
void imprime_Indices(tIndiceLista *l);
void destroi_Indices(tIndiceLista *l);

// ------ Lista não tratada de palavras (para o programa testador) ------
char insere_ListaNaoTratada(tListaNaoTratada *l, char *str);
void destroi_ListaNaoTratada(tListaNaoTratada *l);

#endif
