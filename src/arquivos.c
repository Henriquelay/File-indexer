#include "../headers/arquivos.h"

char abre_Arquivo(char *path, FILE *arquivo){
    arquivo = NULL;
    arquivo = fopen(path);
    if(arquivo == NULL)
        return 0;
    return 1;
}

char fecha_Arquivo(FILE *arquivo){
    return !fclose(arquivo);
}

//Retirado de: Prova1 ED1 2019 - Vinícius Mota
//E alterado
char pega_Palavra( FILE *fp, char *s){
    int i = 0;
    int c;
    while ((c = fgetc(fp)) != EOF){
        if (isalpha(c)||isdigit(c))
            break;
    }
    if (c == EOF)
        return 0;
    else
        s[i++] = c;
    while (i < NPAL - 1 && (c = fgetc(fp)) != EOF && (isalpha(c)||isdigit(c)))
        s[i++] = c;
    s[i] = '\0';
    return 1;
}
