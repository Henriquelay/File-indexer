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


typedef struct ListaNaoTratadaSent{
    tListaNaoTratada *ini, *fim;
    int qtd;
} tListaNaoTratadaSent;



// ------ Funçoes -------
char abre_Arquivo(char *path, FILE **arquivo);
int tamanhoArquivo(FILE *arquivo);
char fecha_Arquivo(FILE *arquivo);
char pega_Palavra(FILE *arquivo, char *str, int *byte);
char pega_PalavraPraBusca(FILE *fp, char *s, int *byte);
char eValido(char c);


#endif
