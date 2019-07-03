#include "../headers/arquivos.h"

char abre_Arquivo(char *path, FILE **arquivo){
    *arquivo = NULL;
    *arquivo = fopen(path, "r");
    if(*arquivo == NULL)
        return 0;
    return 1;
}

char fecha_Arquivo(FILE *arquivo){
    if(arquivo == NULL) return 1;
    return !fclose(arquivo);
}

char eValido(char c){
    switch(c){
        case '\'':
        case '\n':
        case '(':
        case ')':
        case '.':
        case ',':
        case '"':
        case '/':
        case ' ':
        case '?':
        case '!':
        case ';':
        case ':':
        case '-':
            return 0;
        default:
            return 1;
    }
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
        printf("%d", aux->ind);
        if(aux->prox != NULL)
            printf(", ");
    }
    return;
}

void destroi_Indices(tIndiceLista *l){
    for(tIndiceLista *aux = l; l != NULL; aux = l){
        if(l != NULL)
        l = l->prox;
        free(aux);
    }
}

tListaNaoTratadaSent *inicia_ListaNaoTratadaSent(void){
    tListaNaoTratadaSent *nova = (tListaNaoTratadaSent*) malloc(sizeof(tListaNaoTratadaSent));
    if(nova == NULL) return NULL;
    nova->ini = nova->fim = NULL;
    nova->qtd = 0;
    return nova;
}

tListaNaoTratada *novo_NaoTratada(char *str){
    tListaNaoTratada *no = (tListaNaoTratada*) malloc(sizeof(tListaNaoTratada));
    if(no == NULL) return NULL;

    no->palavra = (char*) malloc(sizeof(char) * (strlen(str) + 1));
    if(no->palavra == NULL) return NULL;

    strcpy(no->palavra, str);
    no->prox = NULL;
    return no;
}

char insere_ListaNaoTratadaSent(tListaNaoTratadaSent *l, char *str){
    if(l == NULL) return 0;
    if(l->fim == NULL){
        l->ini = l->fim = novo_NaoTratada(str);
        l->qtd++;
        return 1;
    }
    l->fim->prox = novo_NaoTratada(str);
    if(l->fim->prox == NULL) return 0;
    l->fim = l->fim->prox;
    l->qtd++;
    return 1;
}

void destroi_ListaNaoTratadaSent(tListaNaoTratadaSent *l){
    if(l == NULL) return;
    for(tListaNaoTratada *aux = l->ini; aux != NULL; aux = l->ini){
        l->ini = l->ini->prox;
        free(aux->palavra);
        free(aux);
    }
    free(l);
}

//Retirado de: Prova1 ED1 2019 - Vinícius Mota
//E alterado
char pega_Palavra(FILE *fp, char *s, int *byte){
    if(fp == NULL) return 0;
    int i = 0;
    int c;
    while((c = fgetc(fp)) != EOF){
            if (eValido(c))
            break;
    }
    if(c == EOF)
        return 0;

    s[i++] = tolower(c);
    *byte = ftell(fp);
        
    while(i < NPAL - 1 && (c = fgetc(fp)) != EOF && (eValido(c))){
        s[i++] = tolower(c);
    }
    
    s[i] = '\0';
    return 1;
}
