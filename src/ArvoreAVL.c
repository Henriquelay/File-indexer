#include <stdio.h>
#include <stdlib.h>
#include "../headers/ArvoreAVL.h"

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

int altura_NO(struct NO* no){
    if(no == NULL)  return -1;
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int a, int b){
    if(a > b)   return a;
    else        return b;
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

/* Para caso precise printar a Arvore */

//    void preOrdem_ArvAVL(ArvAVL *raiz){
//        if(raiz == NULL)
//            return;
//        if(*raiz != NULL){
//            printf("No %d: %d\n",(*raiz)->info,altura_NO(*raiz));
//            preOrdem_ArvAVL(&((*raiz)->esq));
//            preOrdem_ArvAVL(&((*raiz)->dir));
//        }
//    }

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("%s\n",(*raiz)->info);
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

//    void posOrdem_ArvAVL(ArvAVL *raiz){
//        if(raiz == NULL)
//            return;
//        if(*raiz != NULL){
//            posOrdem_ArvAVL(&((*raiz)->esq));
//            posOrdem_ArvAVL(&((*raiz)->dir));
//            printf("%d\n",(*raiz)->info);
//        }
//    }

int SelecionaMenorString(char* palavra1, char* palavra2){
    if(palavra1 == NULL || palavra2 == NULL)    return 0;
    int tam_pal1 = strlen(palavra1), tam_pal2 = strlen(palavra2);
    if(tam_pal1 < tam_pal2) return tam_pal1;
    return tam_pal2;
}

char consulta_ArvAVL(ArvAVL *raiz, char* palavra){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    int tam_menor = SelecionaMenorString(palavra, (*raiz)->info);
    int compara = strncmp(palavra, atual->info, tam_menor) > 0;
    while(atual != NULL){
        if(strings_Iguais(palavra, atual->info)){
            return 1;
        }
        if(compara > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

/*====================ROTACOES DE BALANCEAMENTO====================*/
/*
    Rotacao simples a esquerda
*/
void RotacaoLL(ArvAVL *A){
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

/*
    Rotacao simples a direita
*/
void RotacaoRR(ArvAVL *A){
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

/*
    Rotacao Dupla a direita
*/
void RotacaoLR(ArvAVL *A){
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

/*
    Rotacao Dupla a esquerda
*/
void RotacaoRL(ArvAVL *A){
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

char insere_ArvAVL(ArvAVL *raiz, char* palavra/* , int byte*/){
    /* Verifica se Arvore Vazia ou se eh NO folha */
    if(*raiz == NULL){
        struct NO *novo;
        novo = (ArvAVL)malloc(sizeof(tNO));
        if(novo == NULL)
            return 0;

        novo->info = malloc(sizeof(char) * (strlen(palavra) + 1));
        strcpy(novo->info, palavra);
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        // novo->l = byte;
        *raiz = novo;
        return 1;
    }
    
    /**/
    int tam_menor = SelecionaMenorString(palavra, (*raiz)->info);
    if(!tam_menor)  return 0;
    int compara = strncmp(palavra, (*raiz)->info, tam_menor) > 0;
    ArvAVL atual = *raiz;

    if(compara > 0){
        if((insere_ArvAVL(&(atual->esq), palavra))){
            if(fatorBalanceamento_NO(atual) >= 2){    
                    if(strncmp(palavra, (*raiz)->esq->info, tam_menor)){
                        RotacaoLL(raiz);
                    }else{
                        RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(compara < 0){
            if((insere_ArvAVL(&(atual->dir), palavra))){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info < palavra){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return 1;
}

char strings_Iguais(char *str1, char *str2){
    if(str1 == NULL || str2 == NULL) return 0;
    if(strlen(str1) == strlen(str2))
        if(strcasecmp(str1, str2) == 0)
            return 1;
    return 0;
}

/* Funcoes para liberar a estrutura da memoria */
void libera_NO(ArvAVL no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no->info);
    destroi_Indices(no->indices);
    free(no);
    no = NULL;
}

void destroi_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada no
    free(raiz);//libera a raiz
    raiz = NULL;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}
