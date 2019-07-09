#include "../headers/ArvoreBinaria.h"

/*
OBJETIVO: Funcao que Cria e aloca na memória um nó principal chamado raiz e retorna a mesma com seu conteúdo nulo.
IMPUTS: Nenhum.
OUTPUTS: Um ponteiro do tipo ArvBin.
*/
ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

/*
OBJETIVO: Funcao que libera da memória um ponteiro do tipo tNO, junto com seus NOs a esquerda e direita.
IMPUTS: Um ponteiro do tipo ArvBin 'raiz'.
OUTPUTS: Nenhum.
*/
void libera_NO(ArvBin no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no->info);
    destroi_Indices(no->indices);
    free(no);
    no = NULL;
}

/*
OBJETIVO: Funcao que libera da memória um ponteiro do tipo tArvBin, junto com todos os seus NOs da arvore.
IMPUTS: Um ponteiro do tipo ArvBin 'raiz'.
OUTPUTS: Nenhum.
*/
void destroi_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada no
    free(raiz);//libera a raiz
}

/*
OBJETIVO: Funcao que avalia e retorna se duas strings são iguais.
IMPUTS: Um ponteiro do tipo char para 'str1' e um ponteiro do tipo char para 'str2'.
OUTPUTS: 1 se as strings de entrada são iguais e 0 caso contrário.
*/
char strings_Iguais(char *str1, char *str2){
    if(str1 == NULL || str2 == NULL) return 0;
    if(strlen(str1) == strlen(str2))
        if(strcasecmp(str1, str2) == 0)
            return 1;
    return 0;
}

/*
OBJETIVO: Funcao que insere uma palavra na arvore binária e guarda aonde a palavra se localiza no arquivo fonte.
IMPUTS: Um ponteiro do tipo ArvBin para 'raiz', um ponteiro do tipo char para 'palavra' e uma variavel do tipo int para 'byte'.
OUTPUTS: 1 se a palavra foi inserida corretamente e 0 caso contrário.
*/
char insere_ArvBin(ArvBin* raiz, char* palavra, int byte){
    if(raiz == NULL || palavra == NULL) return 0;

    ArvBin aux = *raiz, anterior = NULL;
    while(aux != NULL && !strings_Iguais(aux->info, palavra)){
        anterior = aux;
        if(strcasecmp((*raiz)->info, palavra) > 0)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    //encontrei ou lugar vazio ou no pra adicionar
    if(aux != NULL){        //lugar preenchido, adicionar indice
        aux->ocorrencias++;
        insere_Indice(&aux->indices, byte);
    } 
    else{        //lugar vazio
        aux = (ArvBin) malloc(sizeof(tNo));
        if(aux == NULL) return 0;
        aux->info = malloc(sizeof(char) * (strlen(palavra) + 1));
        strcpy(aux->info, palavra);
        aux->dir = aux->esq = NULL;
        aux->indices = NULL;
        insere_Indice(&aux->indices, byte);
        aux->ocorrencias = 1;
        if(anterior != NULL){
            if(strcasecmp((*raiz)->info, palavra) > 0)
                anterior->esq = aux;
            else
                anterior->dir = aux;
        }
        if(*raiz == NULL)
            *raiz = aux;
    }
    return 1;
}

/*
OBJETIVO: Funcao que verifica se uma palavra de entrada está inserida na arvore binária.
IMPUTS: Um ponteiro do tipo ArvBin para 'raiz' e um ponteiro do tipo char para 'palavra'.
OUTPUTS: 1 se a palavra foi encontrada e 0 caso contrário.
*/
char consulta_ArvBin(ArvBin *raiz, char* palavra){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    int compara = strncpm(palavra, atual->info), tam_menor) > 0;
    while(atual != NULL){
        if(string_Iguais(palavra, atual->info))){
            return 1;
        }
        if(compara > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

/*
OBJETIVO: Funcao que imprime a arvore binária em ordem crescente.
IMPUTS: Um ponteiro do tipo ArvBin para 'raiz'.
OUTPUTS: Nenhum.
*/
void emOrdem(ArvBin *raiz){
    if(raiz == NULL) return;
    if(*raiz == NULL) return;
    emOrdem(&(*raiz)->esq);
    printf("%s (%d): ", (*raiz)->info, (*raiz)->ocorrencias);
    imprime_Indices((*raiz)->indices);
    emOrdem(&(*raiz)->dir);
}
