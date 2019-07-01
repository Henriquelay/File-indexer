#include "../headers/ArvoreBinaria.h"
#include "../headers/arquivos.h"
#include <time.h>

int main(int argc, char *argv[]){
    if(argc <= 2 || atoi(argv[1]) < 1 ){
        printf("#Usagem do programa:\n#./LEIA_O_MAKEFILE [nPalavras] [arquivos..]\n#\tOnde:\n#nPalavras = numeros de palavras a aleatorias a ser pesquisada em cada estrutura\n#arquivos = Os arquivo que serao passados para o programa indexar, separados por espaço.\n");
        return 0;
    }

    ArvBin *a[argc - 2];    //os 2 primeiros são o nome do executável e o n de palavras
    char pal[NPAL]; //tamanho arbitrariamente grande
    int byte = 0;
    FILE *arquivo;

    for(int i = 0; i < argc - 2; i++)
        a[i] = cria_ArvBin();

    clock_t t; 
    t = clock(); 


    for(int i = 2; i < argc; i++){
        arquivo = NULL;
        if(abre_Arquivo(argv[i], &arquivo) != 1){
            printf("Erro ao abrir o arquivo %s!\n", argv[i]);
            return 0;
        }

        while(pega_Palavra(arquivo, pal, &byte))
            insere_ArvBin(a[i-2], pal);

        fecha_Arquivo(arquivo);

        //printf("========LISTA %d:========\n", i - 1);
        //print_Lista(l[i-2]);
    }

    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

    printf("%lf ", time_taken);


/*
    //sorteia as palavras a serem pesquisadas.
    //escolhe primeiro a lista, e aí acessa um número aleatório na lista e trás somente a palavra
    srand(time(NULL));
    t = clock();
    for(int i = 0; i < atoi(argv[1]); i++){
        srand(rand());
        ArvBin ArvSelec = a[rand() % (argc - 2)];
        srand(rand());
        int indSelec = rand() % ListaSelec->qtd;
        tLista *noSelec = ListaSelec->ini;
        for(int y = 0; y < indSelec; y++)
            noSelec = noSelec->prox;
    }
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("%lf\n", time_taken);
*/
    for(int i = 0; i < argc - 2; i++){
        printf("\nArv%d:", i);
        emOrdem(a[i]);
        destroi_ArvBin(a[i]);
    }

    return 0;
}
