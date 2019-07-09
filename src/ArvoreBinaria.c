#include "../headers/ArvoreBinaria.h"

/*
OBJETIVO: Funcao que Cria e aloca na memória um nó principal chamado raiz e retorna a mesma com seu conteúdo nulo.
IMPUTS: Nenhum.
OUTPUTS: Um ponteiro do tipo ArvBin.
*/
ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

/*
OBJETIVO: Funcao que libera da memória um ponteiro do tipo tNO, junto com seus NOs a esquerda e direita.
IMPUTS: Um ponteiro do tipo ArvBin 'raiz'.
OUTPUTS: Nenhum.
*/
void libera_NO(ArvBin no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    destroi_Palavra(no->palavra);
    free(no);
    no = NULL;
}

/*
OBJETIVO: Funcao calcula e retorna o tamanho da menor string.
IMPUTS: Um ponteiro do tipo char para 'str1' e um ponteiro do tipo char para 'str2'.
OUTPUTS: Uma variavel int para o tamanho da menor palavra ou se as palavras forem iguais retorna 0.
*/
int SelecionaMenorString(char* palavra1, char* palavra2){
    if(palavra1 == NULL || palavra2 == NULL)    return 0;
    int tam_pal1 = strlen(palavra1), tam_pal2 = strlen(palavra2);
    if(tam_pal1 < tam_pal2) return tam_pal1;
    return tam_pal2;
}

/*
OBJETIVO: Funcao que libera da memória um ponteiro do tipo tArvBin, junto com todos os seus NOs da arvore.
IMPUTS: Um ponteiro do tipo ArvBin 'raiz'.
OUTPUTS: Nenhum.
*/
void destroi_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada no
    free(raiz);//libera a raiz
}

/*
OBJETIVO: Funcao que avalia e retorna se duas strings são iguais.
IMPUTS: Um ponteiro do tipo char para 'str1' e um ponteiro do tipo char para 'str2'.
OUTPUTS: 1 se as strings de entrada são iguais e 0 caso contrário.
*/
char strings_Iguais(char *str1, char *str2){
    if(str1 == NULL || str2 == NULL) return 0;
    if(strlen(str1) == strlen(str2))
        if(strcasecmp(str1, str2) == 0)
            return 1;
    return 0;
}

/*
OBJETIVO: Funcao que insere uma palavra na arvore binária e guarda aonde a palavra se localiza no arquivo fonte.
IMPUTS: Um ponteiro do tipo ArvBin para 'raiz', um ponteiro do tipo char para 'palavra' e uma variavel do tipo int para 'byte'.
OUTPUTS: 1 se a palavra foi inserida corretamente e 0 caso contrário.
*/
char insere_ArvBin(ArvBin* raiz, char* palavra, int byte, char arq){
    if(raiz == NULL || palavra == NULL) return 0;

    ArvBin aux = *raiz, anterior = NULL;
    while(aux != NULL && !strings_Iguais(aux->palavra->pal, palavra)){
        anterior = aux;
        if(strcasecmp((*raiz)->palavra->pal, palavra) > 0)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    //encontrei ou lugar vazio ou no pra adicionar
    if(aux != NULL){        //lugar preenchido, adicionar indice
        if(!adiciona_IndicePal(aux->palavra, byte, arq))
        puts("Deu ruim ao adicionar ocorrencia na palavra");
    }
    else{        //lugar vazio
        aux = (ArvBin) malloc(sizeof(tNo));
        if(aux == NULL) return 0;
        aux->palavra = cria_Palavra(palavra, arq, byte);
        aux->dir = aux->esq = NULL;
        if(anterior != NULL){
            if(strcasecmp((*raiz)->palavra->pal, palavra) > 0)
                anterior->esq = aux;
            else
                anterior->dir = aux;
        }
        if(*raiz == NULL)
            *raiz = aux;
    }
    return 1;
}

/*
OBJETIVO: Funcao que verifica se uma palavra de entrada está inserida na arvore binária.
IMPUTS: Um ponteiro do tipo ArvBin para 'raiz' e um ponteiro do tipo char para 'palavra'.
OUTPUTS: 1 se a palavra foi encontrada e 0 caso contrário.
*/
char consulta_ArvBin(ArvBin *raiz, char* palavra){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    int tam_menor = SelecionaMenorString(palavra, (*raiz)->palavra->pal);
    int compara = strncmp(palavra, atual->palavra->pal, tam_menor) > 0;
    while(atual != NULL){
        if(strings_Iguais(palavra, atual->palavra->pal)){
            return 1;
        }
        if(compara > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

/*
OBJETIVO: Funcao que imprime a arvore binária em ordem crescente.
IMPUTS: Um ponteiro do tipo ArvBin para 'raiz'.
OUTPUTS: Nenhum.
*/
void emOrdem(ArvBin *raiz){
    if(raiz == NULL) return;
    if(*raiz == NULL) return;
    emOrdem(&(*raiz)->esq);
    int somaocor = 0;
    for(tArquivo *arqaux = (*raiz)->palavra->arquivos; arqaux != NULL; arqaux = arqaux->prox){
        somaocor += arqaux->qtd;
    }
    printf("%s (%d): ", (*raiz)->palavra->pal, somaocor);
    imprime_Arquivos((*raiz)->palavra->arquivos);
    emOrdem(&(*raiz)->dir);
}
