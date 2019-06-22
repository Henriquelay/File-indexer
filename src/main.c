#include "../headers/lista.h"
#include "../headers/arquivos.h"

#define NPAL 100    //tamanho máximo da string (buffer da função de leitura)

int main(int argc, char *argv[]){
    if(argc >= 2){
        printf("#Usagem do programa:\n#./LEIA_O_MAKEFILE [nPalavras] [arquivos..]\n#\tOnde:\n#nPalavras = numeros de palavras a aleatorias a ser pesquisada em cada estrutura\n#arquivos = Os arquivo que serao passados para o programa indexar, separados por espaço.\n");
        return 0;
    }
    tListaSent *l[argc - 2];    //os 2 primeiros são o nome do executável e o n de palavras
    char pal[NPAL]; //tamanho arbitrariamente grande

    for(int i = 0; i < argc - 2; i++)
        l[i] = inicia_ListaSent();
    for(int i = 2; i < argc; i++){
        FILE* arquivo = NULL;
        if(abre_Arquivo(argv[i], arquivo) != 1)
            printf("Erro ao abrir o arquivo %s!\n", argv[i]);

        while(pega_Palavra(arquivo, pal)) 
            insere_Lista(l[i-2], pal);

        puts("LISTA TODA:");
        print_Lista(l[i-2]);
    }

    for(int i = 0; i < argc - 2; i++)
        destroi_Lista(l[i]);

    return 0;
}
