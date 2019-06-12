#ifndef _PALAVRA_H_
#define _PALAVRA_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Palavra{
    char* pal;
    char tamPal;
} tPalavra;

tPalavra *cria_Palavra(char *pal);

char destroi_Palavra(tPalavra *pal);

char compara_Palavra(tPalavra *pal1, tPalavra *pal2);

char igual_Palavra(tPalavra *pal1, tPalavra *pal2);

char print_Palavra(tPalavra *pal);

#endif
