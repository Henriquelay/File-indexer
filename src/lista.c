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
    novo->ocorrencias = 1;
    novo->palavra = pal;
    novo->coluna = novo->linha = NULL;
    /*TODO
     * ADICIONAR TAMBEM A
     * COLUNA E LINHA
     * DA OCORRENCIA
     */
    return novo;
} 

char insere_Lista(tListaSent *l, char *str){
    if(str == NULL) return 0;
    if(l == NULL) l = inicia_ListaSent();

    for(tLista *aux = l->ini; !igual_Palavra(aux->palavra, str) || aux == NULL; aux = aux->prox){
            aux->ocorrencias++;
            /* TODO
            :wa
            :wa
             * ADICIONAR TAMBEM A 
             * COLUNA E LINHA 
             * DA OCORRENCIA
             */
            return 1;
    }
    tPalavra *pal = cria_Palavra(str);
    tLista *no = novo_no_Lista(pal);
    no->prox = l->ini;
    l->ini = no;
    return 1;     
}

char destroi_No(tLista *no){
    if(no == NULL) return 1;
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

