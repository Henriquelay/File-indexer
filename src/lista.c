#include "../headers/lista.h"

tListaSent *inicia_ListaSent(void){
    tListaSent *novo = (tListaSent*) malloc(sizeof(tListaSent));
    if(novo == NULL) return NULL;

    novo->qtd = 0;
    novo->ini = novo->fim = NULL;
    return novo;
}

tLista *novo_no_Lista(char *str){
    if(str == NULL) return NULL;

    tLista *novo = (tLista*) malloc(sizeof(tLista));
    if(novo == NULL) return NULL;
    novo->prox = NULL;
    novo->palavra = str;
    novo->ocorrencias = 1;
    novo->indices = NULL;
            /* TODO: ADICIONAR TAMBEM QUAL O BYTE NO ARQUIVO ONDE HA AS OCORRENCIAS */
    return novo;
} 

char insere_Lista(tListaSent *l, char *str){
    if(str == NULL) return 0;
    if(l == NULL) return 0;

    //Procura a palavra na lista
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
        if(strlen(aux->palavra) == strlen(str))
            if(strcasecmp(aux->palavra, str) == 0){
                aux->ocorrencias++;
                printf("%s eh igual a %s.\n", aux->palavra, str);
                /* TODO: ADICIONAR TAMBEM QUAL O BYTE NO ARQUIVO ONDE HA AS OCORRENCIAS */
                return 1;
            }
    }
    //deixa a string de entrada toda minúscula
    //TODO

    //Não foi encontrado a palavra na lista
    tLista *no = novo_no_Lista(str);
    no->prox = l->ini;
    l->ini = no;
    if(l->fim == NULL)
        l->fim = no;
    l->qtd++;
    puts("Criei novo no e adicionei na lista");
    return 1;     
}

char print_Lista(tListaSent *l){
    if(l == NULL) return 0;
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
        printf("Palavra:\t%s\n\tOcorrencias: %d\n", aux->palavra, aux->ocorrencias);
    }
    return 1;
}

char destroi_No(tLista *no){
    if(no == NULL) return 1;

    /*TODO Adicionar o free da lista de indices ao ser implementada*/
//    free(no->palavra);
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

