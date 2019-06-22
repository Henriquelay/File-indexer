#include "../headers/arquivos.h"

char abre_Arquivo(char *path, FILE **arquivo){
    *arquivo = NULL;
    *arquivo = fopen(path, "r");
    if(*arquivo == NULL)
        return 0;
    return 1;
}

char fecha_Arquivo(FILE *arquivo){
    if(arquivo == NULL) return 1;
    return !fclose(arquivo);
}

//Retirado de: Prova1 ED1 2019 - Vinícius Mota
//E alterado
char pega_Palavra(FILE *fp, char *s, int *byte){
    if(fp == NULL) return 0;
    int i = 0;
    int c;
    while((c = fgetc(fp)) != EOF){
        (*byte)++;
        if (isalnum(c))
            break;
    }
    if(c == EOF)
        return 0;
    else
        s[i++] = tolower(c);
    while(i < NPAL - 1 && (c = fgetc(fp)) != EOF && (isalnum(c))){
        (*byte)++;
        s[i++] = tolower(c);
    }
    
    s[i] = '\0';
    return 1;
}
