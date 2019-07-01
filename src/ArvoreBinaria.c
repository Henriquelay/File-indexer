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
    free(no);
    no = NULL;
}

void destroi_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

char insere_ArvBin(ArvBin* raiz, char* valor){
    if(raiz == NULL || valor == NULL) return 0;
    if(*raiz == NULL){
        ArvBin novo;
        novo = (ArvBin) malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;
        
        novo->info = malloc(sizeof(char) * (strlen(valor) + 1));
        strcpy(novo->info, valor);
        novo->dir = NULL;
        novo->esq = NULL;

        *raiz = novo;
    }
    else{
        if(strlen((*raiz)->info) == strlen(valor)){
            if(!strcasecmp((*raiz)->info, valor))
                //TODO:inserir na lista de ocorrencias
                return 0;
        }
        else if( strcasecmp((*raiz)->info, valor) > 0)
            return insere_ArvBin(&(*raiz)->dir, valor);
        else
            return insere_ArvBin(&(*raiz)->esq, valor);

    }
    return 1;
}

char consulta_ArvBin(ArvBin *raiz, char* valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

