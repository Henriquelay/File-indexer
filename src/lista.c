#include "../headers/lista.h"

tListaSent *inicia_ListaSent(void){
    tListaSent *novo = (tListaSent*) malloc(sizeof(tListaSent));
    if(novo == NULL) return NULL;

    novo->qtd = 0;
    novo->ini = novo->fim = NULL;
    return novo;
}

tLista *novo_no_Lista(tPalavra *pal){
    if(pal == NULL) return NULL;

    tLista *novo = (tLista*) malloc(sizeof(tLista));
    if(novo == NULL) return NULL;
    novo->prox = NULL;
    novo->palavra = pal;
    novo->ocorrencias = 1;
    novo->coluna = novo->linha = NULL;
            /* TODO ADICIONAR TAMBEM QUAL O BYTE NO ARQUIVO ONDE HA AS OCORRENCIAS */
    return novo;
} 

char insere_Lista(tListaSent *l, char *str){
    if(str == NULL) return 0;
    if(l == NULL) l = inicia_ListaSent();

    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
            if(igual_Palavra(aux->palavra, str))
                aux->ocorrencias++;
            /* TODO ADICIONAR TAMBEM QUAL O BYTE NO ARQUIVO ONDE HA AS OCORRENCIAS */
            return 1;
    }
    tPalavra *pal = cria_Palavra(str);
    tLista *no = novo_no_Lista(pal);
    no->prox = l->ini;
    l->ini = no;
    return 1;     
}

char print_Lista(tListaSent *l){
    if(l == NULL) return 0;
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox)
        print_Palavra(aux->palavra);
    return 1;
}

char destroi_No(tLista *no){
    if(no == NULL) return 1;

    /*TODO Adicionar o free da lista de ocorrenciar ao ser implementada*/
    destroi_Palavra(no->palavra);
    free(no);
    return 1;
}

char destroi_Lista(tListaSent *l){
    if(l == NULL) return 1;

    for(tLista *no = l->ini; no != NULL; no = no->prox)
        destroi_No(no);

    free(l);
    return 1;
}

