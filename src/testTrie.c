#include "../headers/trie.h"
#include "../headers/arquivos.h"
#include "../headers/base.h"
#include <sys/time.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]){
    if(argc <= 2 || atoi(argv[1]) < 1 ){
        printf("#Usagem do programa:\n#./LEIA_O_MAKEFILE [nPalavras] [arquivos..]\n#\tOnde:\n#nPalavras = numeros de palavras a aleatorias a ser pesquisada em cada estrutura\n#arquivos = Os arquivo que serao passados para o programa indexar, separados por espaço.\n");
        return 0;
    }
    int nBuscas = atoi(argv[1]), sizes[argc - 2], byte = 0;
    ArvTrie *T = cria_No_Trie();
    char pal[NPAL];                     //tamanho arbitrariamente grande
    FILE *arquivo = NULL;
    clock_t t, tAll = 0;

    for(int i = 0; i < argc - 2; i++){
        if(abre_Arquivo(argv[i + 2], &arquivo) != 1){
            printf("Erro ao abrir o arquivo %s!\n", argv[i + 2]);
            return 0;
        }
        sizes[i] = tamanhoArquivo(arquivo);
        t = clock();
        while(pega_Palavra(arquivo, pal, &byte) == 1){
            // printf("Inserindo %s, ", pal);
            insere_Trie(&T, pal, i, byte);
        }
        tAll += clock() - t;  
        fecha_Arquivo(arquivo);
        arquivo = NULL;
    }

    // print_Lista(t);

    double time_taken = ((double)tAll)/CLOCKS_PER_SEC; // in seconds 
    printf("%lf ", time_taken);

    //copia nBuscas palavras aleatórias da estrutura de lista não tratada para um vetor estático (para ter acesso O(1)) e não impactar tanto na medida busca.
    struct timeval rel;
    gettimeofday(&rel, NULL);
    srand((unsigned int) rel.tv_usec);

    char palavras[nBuscas][NPAL];
    char arq = 0;
    int pos = 0 ;
    int ultimapos = 0;
    for(int i = 0; i < nBuscas; i++){
        arq = (rand() % (argc - 2)) + 2;
        ultimapos = floor((sizes[(int) arq - 2] * 0.8 ));
        pos = rand() % ultimapos;
        // printf("Abrindo arquivo %s, indice %d.\n", argv[(int) arq], (int) arq);
        // printf("Local onde navegar pro arquivo = %d\n", pos);
        if(abre_Arquivo(argv[(int) arq], &arquivo) != 1) printf("Deu bosta ao abrir o arquivo %s!\n", argv[(int) arq]);
        fseek(arquivo, pos, 0);
        pega_PalavraPraBusca(arquivo, palavras[i], &byte);
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
    for(int i = 0; i < nBuscas; i++){
        // printf("Buscando por %s\n", palavras[i]);
        consulta_Trie(&T, palavras[i]);
    }
    t = clock() - t;

    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%lf\n", time_taken);
    
    // printf("Palavras unicas: %d\n", t->qtd);
    destroi_Trie(&T);

    return 0;
}
