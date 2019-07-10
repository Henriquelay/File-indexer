#include "../headers/ArvoreBinaria.h"
#include "../headers/arquivos.h"
#include "../headers/base.h"
#include <time.h>

int desempenhoArvBin(int nBuscas, char *argv[]){
    if(argc <= 2 || atoi(argv[1]) < 1 ){
        printf("#Usagem do programa:\n#./LEIA_O_MAKEFILE [nPalavras] [arquivos..]\n#\tOnde:\n#nPalavras = numeros de palavras a aleatorias a ser pesquisada em cada estrutura\n#arquivos = Os arquivo que serao passados para o programa indexar, separados por espaço.\n");
        return 0;
    }
    ArvBin *a;            //os 2 primeiros são o nome do executável e o n de palavras
    char pal[NPAL];                     //tamanho arbitrariamente grande
    int byte = 0;
    FILE *arquivo = NULL;

        a = cria_ArvBin();
    int sizes[argc - 2];
    clock_t t, tAll;
    tAll = 0;

    for(int i = 0; i < argc - 2; i++){
        if(abre_Arquivo(argv[i + 2], &arquivo) != 1){
            printf("Erro ao abrir o arquivo %s!\n", argv[i + 2]);
            return 0;
        }
        sizes[i] = tamanhoArquivo(arquivo);
        t = clock();
        while(pega_Palavra(arquivo, pal, &byte) == 1){
            insere_ArvBin(a, pal, byte, i);
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
    int pos = 0 ;
    for(int i = 0; i < nBuscas; i++){
        arq = (rand() % (argc - 2)) + 2;
        pos = rand() % sizes[(int) arq - 2];
        // printf("Abrindo arquivo %s, indice %d.\n", argv[(int) arq], (int) arq);
        // printf("Local onde navegar pro arquivo = %d\n", pos);
        if(abre_Arquivo(argv[(int) arq], &arquivo) != 1) printf("Deu bosta ao abrir o arquivo %s!\n", argv[(int) arq]);
        fseek(arquivo, pos, 0);
        while(eValido(fgetc(arquivo)));
        pega_Palavra(arquivo, palavras[i], &byte);
        // printf("Palavra pegada: %s\n", palavras[i]);
        fecha_Arquivo(arquivo);
        arquivo = NULL;
    }

    /*  puts("Vetor pra busca");
    for(int i = 0; i < nBuscas; i++){
        printf("%s ", palavras[i]);

    } */

    //sorteia as palavras a serem pesquisadas.
    //Coloca tudo em um vetor estático, sorteia um valor dentro dele e lê a palavra. Então, tenta buscar ela na estrutura.
    srand(rand());

    t = clock();
    for(int i = 0; i < nBuscas; i++)
            consulta_ArvBin(a, palavras[i]);
    t = clock() - t;

    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%lf\n", time_taken);
    

    destroi_ArvBin(a);

    return 0;
}
