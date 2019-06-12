#include "palavra.h"

tPalavra *cria_Palavra(char *pal){
    if(pal == NULL) return NULL;
    tPalavra *novaPalavra = (tPalavra*) malloc(sizeof(tPalavra));
    if(novaPalavra == NULL) return NULL;

    novaPalavra->tamPal = strlen(pal);
    novaPalavra->pal = (char*) malloc(sizeof(char) * novaPalavra->tamPal);
    return novaPalavra;
}

char libera_Palavra(tPalavra *pal){
    if(pal == NULL) return 1;

    free(pal->pal);
    free(pal);
    return 1;
}

char compara_Palavra(tPalavra *pal1, tPalavra *pal2){
    if(pal1 == NULL || pal2 == NULL) return -1;
    if(pal1->tamPal > pal2->tamPal)
        char menor = pal2->tamPal;
    else
        char menor = pal1->tamPal;

    return strncmp(pal1->pal, pal2->pal, menor);
}

char igual_Palavra(tPalavra *pal1, tPalavra *pal2){
    if(pal1 == NULL || pal2 == NULL) return -1;
    if(pal1->tamPal != pal2->tamPal) return 0;
    if(compara_Palavra(pal1, pal2) != 0) return 0;
    return 1;
}

char print_Palavra(tPalavra *pal){
    if(pal == NULL) return 0;
    if(pal->tamPal < 0) return 0;
    for(int i = 0; i < pal->tamPal; i++)
        printf("%c", pal->pal[i]);
    return 1;
}
