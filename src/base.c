#include "../headers/base.h"

tPalavra *cria_Palavra(char *str, char arquivo, int ocorrencia){
    if(str == NULL) return NULL;

    tPalavra *nova = (tPalavra*) malloc(sizeof(tPalavra));
    if(nova == NULL) return NULL;
    nova->pal = (char*) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(nova->pal, str);
    nova->arquivos = NULL;
    insere_Arquivo(&nova->arquivos, arquivo);
    insere_Indice(&nova->arquivos->ocorrencias, ocorrencia);
    return nova;
}

void destroi_Palavra(tPalavra *pal){
    if(pal == NULL) return;
    destroi_Arquivos(pal->arquivos);
    free(pal);
    pal = NULL;
}

tIndiceLista *novo_Indice(int byte){
    tIndiceLista *novo_Ind = (tIndiceLista*) malloc(sizeof(tIndiceLista));
    if(novo_Ind == NULL) return NULL;
    novo_Ind->ind = byte;
    novo_Ind->ultimo = novo_Ind->prox = NULL;
    return novo_Ind;
}

char insere_Indice(tIndiceLista **l, int byte){
    if(l == NULL) return 0;
    if(*l == NULL){  //criar lista
        *l = novo_Indice(byte);
        (*l)->ultimo = *l;
        return 1;
    }
    tIndiceLista *novo = novo_Indice(byte);
    if(novo == NULL) return 0;
    (*l)->ultimo->prox = novo;
    (*l)->ultimo = novo;
    return 1;
}

void imprime_Indices(tIndiceLista *l){
    for(tIndiceLista *aux = l; aux != NULL; aux = aux->prox){
        printf("%lu", aux->ind);
        if(aux->prox != NULL)
            printf(", ");
    }
    printf("\n");
    return;
}

void destroi_Indices(tIndiceLista *l){
    for(tIndiceLista *aux = l; l != NULL; aux = l){
        if(l != NULL)
        l = l->prox;
        free(aux);
    }
}

tArquivo *novo_Arq(char arq){
    tArquivo *novo_Arq = (tArquivo*) malloc(sizeof(tArquivo));
    if(novo_Arq == NULL) return NULL;
    novo_Arq->arquivo = arq;
    novo_Arq->ocorrencias = NULL;
    novo_Arq->prox = NULL;
    novo_Arq->qtd = 0;
    return novo_Arq;
}

char insere_Arquivo(tArquivo **l, char arq){
    if(l == NULL) return 0;
    if(*l == NULL){  //criar lista
        *l = novo_Arq(arq);
        return 1;
    }
    tArquivo *novo = novo_Arq(arq);
    if(novo == NULL) return 0;
    novo->prox = *l;
    *l = novo;
    return 1;
}

void imprime_Arquivos(tArquivo *l){
    for(tArquivo *aux = l; aux != NULL; aux = aux->prox){
        printf("%c ", aux->arquivo);
        if(aux->prox != NULL)
            printf(", ");
    }
    printf("\n");
    return;
}

void destroi_Arquivos(tArquivo *l){
    for(tArquivo *aux = l; l != NULL; aux = l){
        if(l != NULL)
        l = l->prox;
        destroi_Indices(aux->ocorrencias);
        free(aux);
    }
}