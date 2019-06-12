#include "../headers/lista.h"

tListaSent *inicia_ListaSent(void){
    tListaSent *novo = (tListaSent*) malloc(sizeof(tListaSent));
    if(novo == NULL) return NULL;

    novo->qtd = 0;
    novo->ini = novo->fim = NULL;
    return novo;
}

tLista *novo_no_Lista(char *str){
    if(pal == NULL) return NULL;

    tLista *novo = (tLista*) malloc(sizeof(tLista));
    if(novo == NULL) return NULL;
    tPalavra *pal = nova_Palavra(str);

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
    for(Lista *aux = l->ini; !igual_Palavra(aux->palavra, pal) || aux == NULL; aux = aux->prox)
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

char destroi_No(tLista *no){
    if(no == NULL) return 1;
    destroi_Palavra(no->palavra);
    free(no);
    return 1;
}

char destroi_Lista(tListaSetn *l){
    if(l == NULL) return 1;

    for(tLista *no = l->ini; no != NULL; no = no->prox)
        destroi_No(no);

    free(l);
    return 1;
}

