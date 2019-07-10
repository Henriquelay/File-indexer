#include "../headers/lista.h"

/*
OBJETIVO: Funcao que cria e aloca na memória uma lista com inicio e fim nulos.
INPUTS: Nenhum.
OUTPUTS: Um ponteiro do tipo tLista.
*/
tLista *inicia_Lista(void){
    tLista *novo = (tLista*) malloc(sizeof(tLista));
    if(novo == NULL) return NULL;

    novo->qtd = 0;
    novo->ini = novo->fim = NULL;
    return novo;
}

/*
OBJETIVO: Funcao que cria e aloca na memória uma celula com o prox NULL.
INPUTS: Um ponteiro char para 'str', uma variavel int para 'byte' e uma variavel char para 'arq'.
OUTPUTS: Um ponteiro do tipo tCelula.
*/
tCelula *novo_no_Lista(char *str, int byte, char arq){
    if(str == NULL) return NULL;

    tCelula *novo = (tCelula*) malloc(sizeof(tCelula));
    if(novo == NULL) return NULL;
    novo->palavra = cria_Palavra(str, arq, byte);
    novo->prox = NULL;
    return novo;
} 

/*
OBJETIVO: Funcao que insere uma palavra na lista encadeada.
INPUTS: Um ponteiro tLista para 'l', um ponteiro char para 'str', uma variavel int para 'byte' e uma variavel char para 'arq'.
OUTPUTS: 1 se a palavra foi inserida corretamente e 0 caso contrario.
*/
char insere_Lista(tLista *l, char *str, int byte, char arq){
    if(str == NULL || l == NULL) return 0;
    //Procura a palavra na lista
    for(tCelula *aux = l->ini; aux != NULL; aux = aux->prox)
        if(strlen(aux->palavra->pal) == strlen(str))
            if(strcasecmp(aux->palavra->pal, str) == 0){
                //palavra encontrada na lista
                adiciona_IndicePal(aux->palavra, byte, arq);
                return 1;
            }
    //Não foi encontrado a palavra na lista
    //Será criada um novo nó com a palavra
    tCelula *no = novo_no_Lista(str, byte, arq);
    no->prox = l->ini;
    l->ini = no;
    if(l->fim == NULL)
        l->fim = no;
    l->qtd++;
    return 2;
}

/*
OBJETIVO: Funcao que verifica se uma palabvra de entrada esta inserida na lista.
INPUTS: Um ponteiro tLista para 'l', um ponteiro char para 'pal'.
OUTPUTS: 1 se a palavra foi inserida corretamente e 0 caso contrario.
*/
char consulta_Lista(tLista *l, char* pal){
    if(pal == NULL || l == NULL) return 0;
    
    //Procura a palavra na lista
    for(tCelula *aux = l->ini; aux != NULL; aux = aux->prox){
        if(aux->palavra == NULL) break;
        if(aux->palavra->pal == NULL) break;
        if(strlen(aux->palavra->pal) == strlen(pal))
            if(strcasecmp(aux->palavra->pal, pal) == 0) //encontra a palavra na lista
                return 1;
    }
    return 0;

}

/*
OBJETIVO: Funcao que printa uma lista encadeada.
INPUTS: Um ponteiro tLista para 'l'.
OUTPUTS: 1 se a palavra foi printada corretamente e 0 caso a lista nao existe.
*/
char print_Lista(tLista *l){
    if(l == NULL) return 0;
    int somaocor = 0;
    for(tCelula *aux = l->ini; aux != NULL; aux = aux->prox){
        somaocor = 0;
        for(tArquivo *arqaux = aux->palavra->arquivos; arqaux != NULL; arqaux = arqaux->prox){
            somaocor += arqaux->qtd;
        }
        printf("%s (%d): ", aux->palavra->pal, somaocor);
        imprime_Arquivos(aux->palavra->arquivos);
    }
    return 1;
}

/*
OBJETIVO: Funcao que libera da memória uma lista encadeada.
INPUTS: Um ponteiro do tipo tLista 'l'.
OUTPUTS: Nenhum.
*/
char destroi_Lista(tLista *l){
    if(l == NULL) return 1;

    for(tCelula *no = l->ini; no != NULL; no = l->ini){
        l->ini = l->ini->prox;
        destroi_Palavra(no->palavra);
        free(no);
        l->qtd--;
    }

    free(l);
    return 1;
}

