#include "../headers/arquivos.h"

char abre_Arquivo(char *path, FILE **arquivo){
    *arquivo = NULL;
    *arquivo = fopen(path, "r");
    if(*arquivo == NULL)
        return 0;
    return 1;
}

int tamanhoArquivo(FILE *arquivo){
    if(arquivo == NULL) return 0;
    // size_t lugar = ftell(arquivo);
    fseek(arquivo, 0, SEEK_END);
    int tam = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    return tam;
}

char fecha_Arquivo(FILE *arquivo){
    if(arquivo == NULL) return 1;
    char resp = fclose(arquivo);
    return resp;
}

char eValido(char c){
    if(isalnum(c))
        return 1;
    return 0;
}

char pega_PalavraPraBusca(FILE *fp, char *s, int *byte){
    if(fp == NULL) return 0;
    int c;
    while((c = fgetc(fp)) != EOF){
        // printf("c eh %c\n", c);
        if(!eValido(c)) break;
    }

    if(c == EOF) rewind(fp);
    // else fseek(fp, -1, SEEK_CUR);
    return pega_Palavra(fp, s, byte);
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
    if(c == EOF){
        s[0] = '\0';
        return 0;
    }

    s[i++] = tolower(c);
    *byte = ftell(fp);
        
    while(i < NPAL - 1 && (c = fgetc(fp)) != EOF && (eValido(c))){
        s[i++] = tolower(c);
    }
    
    s[i] = '\0';
    return 1;
}
