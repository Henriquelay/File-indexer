#include "../headers/lista.h"
#include "../headers/arquivos.h"
#include <time.h>

int main(int argc, char *argv[]){
    if(argc <= 2 || atoi(argv[1]) < 1 ){
        printf("#Usagem do programa:\n#./LEIA_O_MAKEFILE [nPalavras] [arquivos..]\n#\tOnde:\n#nPalavras = numeros de palavras a aleatorias a ser pesquisada em cada estrutura\n#arquivos = Os arquivo que serao passados para o programa indexar, separados por espaço.\n");
        return 0;
    }
    int nBuscas = atoi(argv[1]);
    tListaSent *l[argc - 2];            //os 2 primeiros são o nome do executável e o n de palavras
    char pal[NPAL];                     //tamanho arbitrariamente grande
    int byte = 0;
    FILE *arquivo = NULL;

    for(int i = 0; i < argc - 2; i++)
        l[i] = inicia_ListaSent();
    size_t sizes[argc - 2];
    clock_t t, tAll;
    tAll = 0;

    for(int i = 2; i < argc; i++){
        if(abre_Arquivo(argv[i], &arquivo) != 1){
            printf("Erro ao abrir o arquivo %s!\n", argv[i]);
            return 0;
        }
        sizes[i - 2] = tamanhoArquivo(arquivo);
        t = clock();
        while(pega_Palavra(arquivo, pal, &byte) == 1){
            insere_Lista(l[i-2], pal, byte);
        }
        tAll += clock() - t;  
        fecha_Arquivo(arquivo);
        arquivo = NULL;
    }

    double time_taken = ((double)tAll)/CLOCKS_PER_SEC; // in seconds 
    printf("%lf ", time_taken);

    //copia nBuscas palavras aleatórias da estrutura de lista não tratada para um vetor estático (para ter acesso O(1)) e não impactar tanto na medida busca.
    srand(time(NULL));
    char palavras[nBuscas][NPAL];
    char arq = 0;
    for(int i = 0; i < nBuscas; i++){
        arq = rand() % (argc - 2);
        if(abre_Arquivo(argv[(int) arq], &arquivo) != 1) printf("Deu bosta ao abrir o arquivo %s!\n", argv[(int) arq]);
        fseek(arquivo, 0, rand() % sizes[(int) arq]);
        while(eValido(fgetc(arquivo)));
        pega_Palavra(arquivo, palavras[i], &byte);
        fecha_Arquivo(arquivo);
        arquivo = NULL;
    }

    puts("Vetor estatico de busca:");
    for(int i = 0; i < nBuscas; i++)
        printf("%s ",palavras[i]);
    //sorteia as palavras a serem pesquisadas.
    //Coloca tudo em um vetor estático, sorteia um valor dentro dele e lê a palavra. Então, tenta buscar ela na estrutura.
/*     srand(rand());
    t = clock();
    for(int i = 0; i < nBuscas; i++)
        for(int y = 0; y < argc - 2; y++)
            consulta_Lista(l[y], seletor[i]);

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("%lf\n", time_taken);
 */

    for(int i = 0; i < argc - 2; i++){
        destroi_Lista(l[i]);
    }

    return 0;
}
