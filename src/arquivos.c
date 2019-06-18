#include "../headers/arquivos.h"

char abre_Arquivo(char *path, FILE *arquivo){
    arquivo = NULL;
    arquivo = fopen(path);
    if(arquivo == NULL)
        return 0;
    return 1;
}

char fecha_Arquivo(FILE *arquivo){
    return fclose(arquivo);
}

char *pega_Palavra(FILE *arquivo){
    char *palavra;

}
