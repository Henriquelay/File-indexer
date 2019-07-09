#include "../headers/hash.h"

tHash *cria_TabelaHash(void){
    tHash *nova = (tHash*) malloc(sizeof(tHash));
    if(nova == NULL) return NULL;
    for(int i = 0; i < TAMDAHASH; i++)
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
    
    int insercao = hash(hashtable->pesos, palavra);
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
            emOrdem(hashtable->hash[i]);
        }
    printf("Quantidade; %d\nColisoes: %d\nTaxa de colisao: %d\n", hashtable->qtd, hashtable->colisoes, hashtable->colisoes/hashtable->qtd);
    }
}

char consulta_Hash(tHash *hashtable, char *str){
    if(hashtable == NULL || str == NULL) return 0;
    if(hashtable->pesos == NULL || hashtable->hash == NULL) return 0;
    
    int indice = hash(hashtable->pesos);
    if(indice < 0 ) indice *= -1;
    return consulta_ArvAVL(hashtable->hash[indice], str);
}