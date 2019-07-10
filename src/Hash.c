#include "../headers/Hash.h"

tHash *cria_Hash(void){
    tHash *nova = (tHash*) malloc(sizeof(tHash));
    if(nova == NULL) return NULL;
    for(int i = 0; i < TAMDAHASH; i++)
        nova->hash[i] = cria_ArvAVL();
    nova->colisoes = 0;
    nova->qtd = 0;
    nova->pesos = pesos_Lista();
    return nova;
}

int* pesos_Lista(void){
    struct timeval t;
    int *pesos = (int*) malloc(sizeof(int) * NPAL);
    if(pesos == NULL) return NULL;
    gettimeofday(&t, NULL);
    srand((unsigned int) t.tv_usec);

    for(int i = 0; i < NPAL; i++)
        pesos[i] = rand() % 69420;
    
    return pesos;
}

int hash(int *pesos, char *str){
    if(str == NULL || pesos == NULL) return -1;
    int result = 0;
    int len = strlen(str);
    for(int i = 0; i < len; i++)
        result += pesos[i] * str[i];
    return result % TAMDAHASH;
}

char insere_Hash(tHash *hashtable, char *palavra, int byte, char arq){
    if(hashtable == NULL || palavra == NULL) return 0;
    if(hashtable->pesos == NULL || hashtable->hash == NULL) return 0;

    
    int insercao = hash(hashtable->pesos, palavra);
    // printf("atual = %d\n", hashtable->hash[insercao] == NULL);
    if(insercao < 0) insercao *= -1;
    if(*hashtable->hash[insercao] != NULL) hashtable->colisoes++;
    insere_ArvAVL(hashtable->hash[insercao], palavra, byte, arq);
    hashtable->qtd++;
    return 1;
}

void imprime_Hash(tHash *hashtable){
    if(hashtable == NULL) return;
    if(hashtable->hash == NULL) return;
    for(int i = 0; i < TAMDAHASH; i++){
        if(*hashtable->hash[i] != NULL){
            printf("------------------------------\nArvore numero %d:\n", i);
            emOrdem_ArvAVL(hashtable->hash[i]);
        }
    printf("Quantidade; %d\nColisoes: %d\nTaxa de colisao: %d\n", hashtable->qtd, hashtable->colisoes, hashtable->colisoes/hashtable->qtd);
    }
}

char consulta_Hash(tHash *hashtable, char *str){
    if(hashtable == NULL || str == NULL) return 0;
    if(hashtable->pesos == NULL || hashtable->hash == NULL) return 0;

    // printf("Buscando por %s\n", str);
    
    int indice = hash(hashtable->pesos, str);
    if(indice < 0 ) indice *= -1;
    return consulta_ArvAVL(hashtable->hash[indice], str);
}

void destroi_Hash(tHash *hash){
    if(hash == NULL) return;
    for(int i = 0; i < TAMDAHASH; i++)
        destroi_ArvAVL(hash->hash[i]);
    free(hash->pesos);
    free(hash);
    hash = NULL;
}
int desempenho_Hash(int argc, char *argv[]){
    int nBuscas = atoi(argv[1]);
    if(argc < 2 || nBuscas < 1 ){
        printf("#Usagem do programa:\n#./LEIA_O_MAKEFILE [nPalavras] [arquivos..]\n#\tOnde:\n#nPalavras = numeros de palavras a aleatorias a ser pesquisada em cada estrutura\n#arquivos = Os arquivo que serao passados para o programa indexar, separados por espaço.\n");
        return 0;
    }
    tHash *h;
    char pal[NPAL];
    // tamanho arbitrariamente grande
    int byte = 0, nArquivos = argc - 2;
    FILE *arquivo = NULL;
    h = cria_Hash();
    int sizes[nBuscas - 2];
    clock_t t, tAll = 0;

    for(int i = 0; i < nArquivos; i++){
        if(abre_Arquivo(argv[i + 2], &arquivo) != 1){
            printf("Erro ao abrir o arquivo %s!\n", argv[i + 2]);
            return 1;
        }
        sizes[i] = tamanhoArquivo(arquivo);
        t = clock();
        while(pega_Palavra(arquivo, pal, &byte) == 1){
            if(!insere_Hash(h, pal, byte, i)) printf("Erro ao tentar inserir %s! ", pal);
        }
        tAll += clock() - t;  
        fecha_Arquivo(arquivo);
        arquivo = NULL;
    }

    double time_taken = ((double)tAll)/CLOCKS_PER_SEC; // in seconds 
    printf("%lf ", time_taken);

    
    // Lê palavras aletórias dentro de arquivos aleatórios dentro dos de entrada.
    srand(time(NULL));
    char palavras[nBuscas][NPAL];
    char arq = 0;
    int pos = 0 ;
    for(int i = 0; i < nBuscas; i++){
        arq = (rand() % (argc - 2)) + 2;
        pos = rand() % sizes[(int) arq - 2];
        if(abre_Arquivo(argv[(int) arq], &arquivo) != 1) printf("Deu ruim ao abrir o arquivo %s!\n", argv[(int) arq]);
        fseek(arquivo, pos, 0); // Aponta o ponteiro de stream (arquivo) para a posição "pos" (aleatóriamente gerada)
        while(eValido(fgetc(arquivo)));
        if(!pega_Palavra(arquivo, palavras[i], &byte)){
            rewind(arquivo);
            pega_Palavra(arquivo, palavras[i], &byte);
        }
        fecha_Arquivo(arquivo);
        arquivo = NULL;
    }

    // Carrega palavras aleatórias do vetor gerado previamente e busca elas na estrutura
    srand(rand());
    t = clock();
    for(int i = 0; i < nBuscas; i++)
            consulta_Hash(h, palavras[i]);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%lf\n", time_taken);

    destroi_Hash(h);

    return 0;
}
