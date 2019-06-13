#include "../headers/palavra.h"

tPalavra *cria_Palavra(char *pal){
    if(pal == NULL) return NULL;
    tPalavra *novaPalavra = (tPalavra*) malloc(sizeof(tPalavra));
    if(novaPalavra == NULL) return NULL;

    novaPalavra->tamPal = strlen(pal);
    novaPalavra->pal = (char*) malloc(sizeof(char) * novaPalavra->tamPal);
    //copia a string sem o caractere terminador
    int i = 0;
    for(char c = pal[0]; i < novaPalavra->tamPal; i++, c = pal[i])
        novaPalavra->pal[i] = c;
    return novaPalavra;
}

char destroi_Palavra(tPalavra *pal){
    if(pal == NULL) return 1;

    free(pal->pal);
    free(pal);
    return 1;
}

//jamais entrar com ponteiro NULO aqui
char compara_Palavra(tPalavra *pal1, tPalavra *pal2){
    if(pal1 == NULL || pal2 == NULL) return 0;
    char menor = 0;
    if(pal1->tamPal > pal2->tamPal)
        menor = pal2->tamPal;
    else
        menor = pal1->tamPal;

    return strcasecmp(pal1->pal, pal2->pal);
}

char igual_Palavra(tPalavra *pal1, char *str){
    if(pal1 == NULL || str == NULL) return 0;
    //Retorna falso se são de tamanhos diferentes
    if(pal1->tamPal != strlen(str)) return 0;
    tPalavra *pal2 = cria_Palavra(str);
    if(compara_Palavra(pal1, pal2) != 0) return 0;
    destroi_Palavra(pal1);
    return 1;
}

char print_Palavra(tPalavra *pal){
    if(pal == NULL) return 0;
    if(pal->tamPal < 0) return 1;
    for(int i = 0; i < pal->tamPal; i++)
        printf("%c", pal->pal[i]);
    printf("\n");
    return 1;
}
