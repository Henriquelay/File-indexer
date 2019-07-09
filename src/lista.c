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
    novo->palavra = cria_Palavra(str, arq, byte);
    novo->prox = NULL;
    return novo;
} 

char insere_Lista(tListaSent *l, char *str, int byte, char arq){
    if(str == NULL) return 0;
    if(l == NULL) return 0;

    //Procura a palavra na lista
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
        if(strlen(aux->palavra->pal) == strlen(str))
            if(strcasecmp(aux->palavra->pal, str) == 0){ //encontra a palavra na lista
                if(!adiciona_IndicePal(aux->palavra, byte, arq)) puts("Deu ruim ao inserir indice");
                return 1;
            }
    }
    //Não foi encontrado a palavra na lista
    tLista *no = novo_no_Lista(str, byte, arq);
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
        if(aux->palavra == NULL) break;
        if(aux->palavra->pal == NULL) break;
        if(strlen(aux->palavra->pal) == strlen(pal))
            if(strcasecmp(aux->palavra->pal, pal) == 0) //encontra a palavra na lista
                return 1;
    }
    return 0;

}

char print_Lista(tListaSent *l){
    if(l == NULL) return 0;
    int somaocor = 0;
    for(tLista *aux = l->ini; aux != NULL; aux = aux->prox){
        somaocor = 0;
        for(tArquivo *arqaux = aux->palavra->arquivos; arqaux != NULL; arqaux = arqaux->prox){
            somaocor += arqaux->qtd;
        }
        printf("%s (%d): ", aux->palavra->pal, somaocor);
        imprime_Arquivos(aux->palavra->arquivos);
    }
    return 1;
}

char destroi_Lista(tListaSent *l){
    if(l == NULL) return 1;

    for(tLista *no = l->ini; no != NULL; no = l->ini){
        l->ini = l->ini->prox;
        destroi_Palavra(no->palavra);
        free(no);
        l->qtd--;
    }

    free(l);
    return 1;
}

