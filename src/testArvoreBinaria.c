#include "../headers/ArvoreBinaria.h"
#include "../headers/arquivos.h"
#include <time.h>

int main(int argc, char *argv[]){
    if(argc <= 2 || atoi(argv[1]) < 1 ){
        printf("#Usagem do programa:\n#./LEIA_O_MAKEFILE [nPalavras] [arquivos..]\n#\tOnde:\n#nPalavras = numeros de palavras a aleatorias a ser pesquisada em cada estrutura\n#arquivos = Os arquivo que serao passados para o programa indexar, separados por espaço.\n");
        return 0;
    }
    int nBuscas = atoi(argv[1]);
    ArvBin *arvore[argc - 2];                //os 2 primeiros são o nome do executável e o n de palavras
    char pal[NPAL];                     //tamanho arbitrariamente grande
    int byte = 0;
    FILE *arquivo;

    for(int i = 0; i < argc - 2; i++)
        arvore[i] = cria_ArvBin();
    tListaNaoTratadaSent *holder = inicia_ListaNaoTratadaSent();
    clock_t t; 
    t = clock();

    for(int i = 2; i < argc; i++){
        arquivo = NULL;
        if(abre_Arquivo(argv[i], &arquivo) != 1){
            printf("Erro ao abrir o arquivo %s!\n", argv[i]);
            return 0;
        }
        while(pega_Palavra(arquivo, pal, &byte)){
            insere_ArvBin(arvore[i-2], pal, byte);
            if(!insere_ListaNaoTratadaSent(holder, pal)){
                puts("##CARALHO CAGUEI ALGUMA COISA, VOU QUITAR");
                return 0;
            }
        }
        fecha_Arquivo(arquivo);
    }

    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("%lf ", time_taken);

    //copia nBuscas palavras aleatórias da estrutura de lista não tratada para um vetor estático (para ter acesso O(1)) e não impactar tanto na medida busca.
    srand(time(NULL));
    int ind = 0;
    tListaNaoTratada *palselec = NULL;
    char *seletor[nBuscas];
    for(int i = 0; i < nBuscas; i++){
        palselec = holder->ini;
        ind = rand() % holder->qtd;
        for(int y = 0; y < ind; y++){
            palselec = palselec->prox;
        }
        
        seletor[i] = palselec->palavra;
    }

    //sorteia as palavras a serem pesquisadas.
    //Coloca tudo em um vetor estático, sorteia um valor dentro dele e lê a palavra. Então, tenta buscar ela na estrutura.
    srand(time(NULL));
    t = clock();
    for(int i = 0; i < nBuscas; i++)
        for(int y = 0; y < argc - 2; y++)
            consulta_ArvBin(arvore[y], seletor[i]);

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("%lf\n", time_taken);
    
/* 
    for(int i = 2; i < argc; i++){
        printf("--------%s----------------\n", argv[i]);
        emOrdem(arvore[i - 2]);
    }
 */

    for(int i = 0; i < argc - 2; i++){
        destroi_ArvBin(arvore[i]);
    }
    destroi_ListaNaoTratadaSent(holder);

    return 0;
}
