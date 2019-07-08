#include "../headers/ArvoreBinaria.h"

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

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

void destroi_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada no
    free(raiz);//libera a raiz
}

char strings_Iguais(char *str1, char *str2){
    if(str1 == NULL || str2 == NULL) return 0;
    if(strlen(str1) == strlen(str2))
        if(strcasecmp(str1, str2) == 0)
            return 1;
    return 0;
}

char insere_ArvBin(ArvBin* raiz, char* valor, int byte){
    if(raiz == NULL || valor == NULL) return 0;

    ArvBin aux = *raiz, anterior = NULL;
    while(aux != NULL && !strings_Iguais(aux->info, valor)){
        anterior = aux;
        if(strcasecmp((*raiz)->info, valor) > 0)
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
        aux->info = malloc(sizeof(char) * (strlen(valor) + 1));
        strcpy(aux->info, valor);
        aux->dir = aux->esq = NULL;
        aux->indices = NULL;
        insere_Indice(&aux->indices, byte);
        aux->ocorrencias = 1;
        if(anterior != NULL){
            if(strcasecmp((*raiz)->info, valor) > 0)
                anterior->esq = aux;
            else
                anterior->dir = aux;
        }
        if(*raiz == NULL)
            *raiz = aux;
    }
    return 1;
}

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

void emOrdem(ArvBin *raiz){
    if(raiz == NULL) return;
    if(*raiz == NULL) return;
    emOrdem(&(*raiz)->esq);
    printf("%s (%d): ", (*raiz)->info, (*raiz)->ocorrencias);
    imprime_Indices((*raiz)->indices);
    emOrdem(&(*raiz)->dir);
}
