#include "../headers/lista.h"

tListaSent *inicia_ListaSent(void){
    tListaSent *novo = (tListaSent*) malloc(sizeof(tListaSent));
    if(novo == NULL) return NULL;

    novo->qtd = 0;
    novo->ini = novo->fim = NULL;
    return novo;
}

tLista *novo_no_Lista(char *str, int byte, char arq){
    if(str == NULL) return NULL;

    tLista *novo = (tLista*) malloc(sizeof(tLista));
    if(novo == NULL) return NULL;
    novo->palavra = nova_Palavra(str, arq, byte);
    novo->prox = NULL;
    return novo;
} 

char insere_Lista(tListaSent *l, char *str, int byte){
    if(str == NULL) return 0;
    if(l == NULL) return 0;

    //Procura a palavra na lista
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
        if(strlen(aux->palavra) == strlen(str))
            if(strcasecmp(aux->palavra, str) == 0){ //encontra a palavra na lista
                aux->ocorrencias++;
                insere_Indice(&aux->indices, byte);
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
    return 2;
}

char consulta_Lista(tListaSent *l, char* pal){
    if(pal == NULL || l == NULL) return 0;
    
    //Procura a palavra na lista
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
        if(strlen(aux->palavra) == strlen(pal))
            if(strcasecmp(aux->palavra, pal) == 0) //encontra a palavra na lista
                return 1;
    }
    return 0;

}

char print_Lista(tListaSent *l){
    if(l == NULL) return 0;
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
        printf("%s (%d): ", aux->palavra, aux->ocorrencias);
        imprime_Indices(aux->indices);
        printf("\n");
    }
    return 1;
}

char destroi_No(tLista *no){
    if(no == NULL) return 1;

    free(no->palavra);
    destroi_Indices(no->indices);
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

