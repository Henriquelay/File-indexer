#include "lista.h"

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

    novo->palavra = pal;
    novo->ocorrencias = 1;
    novo->coluna = novo->linha = NULL;
    novo->prox = NULL;
    return novo;
} 

char insere_Lista(tListaSent *l, char *str){
    if(str == NULL) return 0;
    if(tListaSent == NULL) l = inicia_ListaSent();

    tPalavra pal = cria_Palavra(str);
    for(Lista *aux = l->ini; aux != NULL; aux = aux->prox)
        if(igual_Palavra(aux->palavra, str)){
            aux->ocorrencias++;
            /*
             * ANOTAR TAMBEM A 
             * COLUNA E LINHA 
             * DA OCORRENCIA
             */
            return 1;
        }
    tLista *no = novo_no_Lista(pal){
    }
    
     
}

