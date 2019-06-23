#include "../headers/lista.h"

tListaSent *inicia_ListaSent(void){
    tListaSent *novo = (tListaSent*) malloc(sizeof(tListaSent));
    if(novo == NULL) return NULL;

    novo->qtd = 0;
    novo->ini = novo->fim = NULL;
    return novo;
}

tIndiceLista *novo_Indice(int byte){
    tIndiceLista *novo_Ind = (tIndiceLista*) malloc(sizeof(tIndiceLista));
    if(novo_Ind == NULL) return NULL;
    novo_Ind->ind = byte;
    novo_Ind->prox = NULL;
    return novo_Ind;
}

tLista *novo_no_Lista(char *str, int byte){
    if(str == NULL) return NULL;

    tLista *novo = (tLista*) malloc(sizeof(tLista));
    if(novo == NULL) return NULL;
    novo->prox = NULL;
    novo->palavra = (char*) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(novo->palavra, str);
    novo->ocorrencias = 1;
    novo->indices = novo_Indice(byte);
    return novo;
} 

char insere_Indice(tLista *no, int byte){
    if(no == NULL) return 0;
    if(no->indices == NULL) return 0;
    tIndiceLista *novo = (tIndiceLista*) malloc(sizeof(tIndiceLista));
    if(novo == NULL) return 0;
    novo->ind = byte;
    novo->prox = no->indices;
    no->indices = novo;
    return 1;
}

void imprime_Indices(tLista *no){
    if(no == NULL) return;
        tIndiceLista *aux = no->indices;
    do{
        printf("%d", aux->ind);
        aux = aux->prox;
        if(aux != NULL)
            printf(", ");
    } while(aux != NULL);
    return;
}

char insere_Lista(tListaSent *l, char *str, int byte){
    if(str == NULL) return 0;
    if(l == NULL) return 0;

    //Procura a palavra na lista
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
        if(strlen(aux->palavra) == strlen(str))
            if(strcasecmp(aux->palavra, str) == 0){ //encontra a palavra na lista
                aux->ocorrencias++;
                insere_Indice(aux, byte);
                return 1;
            }
    }
    //Não foi encontrado a palavra na lista
    tLista *no = novo_no_Lista(str, byte);
    no->prox = l->ini;
    l->ini = no;
    if(l->fim == NULL)
        l->fim = no;
    l->qtd++;
    return 1;     
}

char print_Lista(tListaSent *l){
    if(l == NULL) return 0;
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
        printf("%s %d: ", aux->palavra, aux->ocorrencias);
        imprime_Indices(aux);
        printf("\n");
    }
    return 1;
}

char destroi_No(tLista *no){
    if(no == NULL) return 1;

    free(no->palavra);
    tIndiceLista *next = NULL;
    for(tIndiceLista *aux = no->indices; aux != NULL; aux = next){
        next = aux->prox;
        free(aux);
    }
    free(no);
    return 1;
}

char destroi_Lista(tListaSent *l){
    if(l == NULL) return 1;

    for(tLista *no = l->ini; no != NULL; no = l->ini){
        l->ini = l->ini->prox;
        destroi_No(no);
        l->qtd--;
    }

    free(l);
    return 1;
}

