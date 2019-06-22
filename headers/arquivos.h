#ifndef _ARQUIVOS_H_
#define _ARQUIVOS_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define NPAL 100  //tamanho máximo da string (buffer da função de leitura)


// ------ Funçoes -------

char abre_Arquivo(char *path, FILE **arquivo);

char fecha_Arquivo(FILE *arquivo);

char pega_Palavra(FILE *arquivo, char *str, int *byte);

#endif
