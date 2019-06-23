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

char eValido(char c){
    switch(c){
        case '(':
        case ')':
        case '.':
        case ',':
        case '"':
        case '\'':
        case ' ':
        case '\n':
        case '?':
        case '!':
            return 0;
        default:
            return 1;
    }
}

//Retirado de: Prova1 ED1 2019 - Vinícius Mota
//E alterado
char pega_Palavra(FILE *fp, char *s, int *byte){
    if(fp == NULL) return 0;
    int i = 0;
    int c;
    while((c = fgetc(fp)) != EOF){
            if (eValido(c))
            break;
    }
    if(c == EOF)
        return 0;

    s[i++] = tolower(c);
    *byte = ftell(fp);
        
    while(i < NPAL - 1 && (c = fgetc(fp)) != EOF && (eValido(c))){
        s[i++] = tolower(c);
    }
    
    s[i] = '\0';
    return 1;
}
