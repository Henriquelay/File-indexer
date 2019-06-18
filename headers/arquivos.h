#ifndef _ARQUIVOS_H_
#define _ARQUIVOS_H_

#include <stdlib.h>
#include <stdio.h>

// ------ Funçoes -------

char abre_Arquivo(char *path, FILE *arquivo);

char fecha_Arquivo(FILE *arquivo);

char *pega_Palavra(FILE *arquivo);

#endif
