#include "../headers/lista.h"
#include "../headers/arquivos.h"

int main(int argc, char *argv[]){
    if(argc >= 2) return 0;
    tListaSent *l[argc - 2];

    for(int i = 2; i < argc; i++){
        tListaSent *l[i] = inicia_ListaSent();
        FILE* arquivo;
        if(abre_Arquivo(argv[i], arquivo) != 1)
            printf("Erro ao abrir o arquivo %s!\n", argv[i]);

        while(arquivo != EOF) 
            insere_Lista(l[i], pega_Palavra(arquivo));

        puts("LISTA TODA:");
        print_Lista(l);
    }


    destroi_Lista(l);
    return 0;
}
