#include <stdio.h>
#include <stdlib.h>
#include "../headers/ArvoreAVL.h"

/*
OBJETIVO: Funcao que Cria e aloca na memória um nó principal chamado raiz e retorna a mesma com seu conteúdo nulo.
IMPUTS: Nenhum.
OUTPUTS: Um ponteiro do tipo ArvAVL.
*/
ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

/*
OBJETIVO: Funcao que retorna a altura de um NO qualquer na arvore.
IMPUTS: Um ponteiro do tipo NO para 'no'.
OUTPUTS: Uma variavel inteira para altura do NO.
*/
int altura_NO(ArvAVL no){
    if(no == NULL)  return -1;
    return no->altura;
}

/*
OBJETIVO: Funcao que calcula e retorna o fator de balanceamento que eh o modulo da
altura da subArvore a esquerda menos a altura da subArvore a direita.
IMPUTS: Um ponteiro do tipo NO para 'no'.
OUTPUTS: Uma variavel inteira para o fator de balanceamento.
*/
int fatorBalanceamento_NO(ArvAVL no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

/*
OBJETIVO: Funcao que retorna o maior de dois numeros.
IMPUTS: Duas variaveis inteiras para os valores a serem comparados.
OUTPUTS: Uma variavel inteira para o maior.
*/
int maior(int a, int b){
    if(a > b)   return a;
    else        return b;
}

/*
OBJETIVO: Funcao que retorna a altura da arvore.
IMPUTS: Um ponteiro do tipo ArvAVL para 'raiz'.
OUTPUTS: Uma variavel inteira para altura da arvore.
*/
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

/*
OBJETIVO: Funcao que imprime a arvore binária em ordem crescente.
IMPUTS: Um ponteiro do tipo ArvAVL para 'raiz'.
OUTPUTS: Nenhum.
*/
void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("%s\n",(*raiz)->palavra->pal);
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

/*
OBJETIVO: Funcao calcula e retorna o tamanho da menor string.
IMPUTS: Um ponteiro do tipo char para 'str1' e um ponteiro do tipo char para 'str2'.
OUTPUTS: Uma variavel int para o tamanho da menor palavra ou se as palavras forem iguais retorna 0.
*/
int SelecionaMenorStringAVL(char* palavra1, char* palavra2){
    if(palavra1 == NULL || palavra2 == NULL) return 0;
    int tam_pal1 = strlen(palavra1), tam_pal2 = strlen(palavra2);
    if(tam_pal1 < tam_pal2) return tam_pal1;
    return tam_pal2;
}

/*
OBJETIVO: Funcao que verifica se uma palavra de entrada está inserida na arvore binária.
IMPUTS: Um ponteiro do tipo ArvAVL para 'raiz' e um ponteiro do tipo char para 'palavra'.
OUTPUTS: 1 se a palavra foi encontrada e 0 caso contrário.
*/
char consulta_ArvAVL(ArvAVL *raiz, char* palavra){
    if(raiz == NULL)
        return 0;
    ArvAVL atual = *raiz;
    int tam_menor = SelecionaMenorStringAVL(palavra, (*raiz)->palavra->pal);
    int compara = strncmp(palavra, atual->palavra->pal, tam_menor) > 0;
    while(atual != NULL){
        if(strings_IguaisAVL(palavra, atual->palavra->pal)){
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
OBJETIVO: Funcao que faz a rotacao simples a esquerda.
IMPUTS: Um ponteiro do tipo ArvAVL para 'raiz'.
OUTPUTS: Nenhum.
*/
void RotacaoLL(ArvAVL *A){
    tNoAVL *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

/*
OBJETIVO: Funcao que faz a rotacao simples a direita.
IMPUTS: Um ponteiro do tipo ArvAVL para 'raiz'.
OUTPUTS: Nenhum.
*/
void RotacaoRR(ArvAVL *A){
    if(A == NULL) return;
    tNoAVL *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

/*
OBJETIVO: Funcao que faz a rotacao dupla a direita.
IMPUTS: Um ponteiro do tipo ArvAVL para 'raiz'.
OUTPUTS: Nenhum.
*/
void RotacaoLR(ArvAVL *A){
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

/*
OBJETIVO: Funcao que faz a rotacao dupla a esquerda.
IMPUTS: Um ponteiro do tipo ArvAVL para 'raiz'.
OUTPUTS: Nenhum.
*/
void RotacaoRL(ArvAVL *A){
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

/*
OBJETIVO: Funcao que insere uma palavra na arvore AVL e faz o balanceamento da arvore.
IMPUTS: Um ponteiro do tipo ArvAVL para 'raiz', um ponteiro do tipo char para 'palavra'.
OUTPUTS: 1 se a palavra foi inserida corretamente e 0 caso contrário.
*/
char insere_ArvAVL(ArvAVL *raiz, char* palavra, int byte, char arq){
    if(raiz == NULL) return 0;
    /* Verifica se Arvore Vazia ou se eh NO folha */
    if(*raiz == NULL){  //criando novo nó
        ArvAVL novo = (ArvAVL) malloc(sizeof(tNoAVL));
        if(novo == NULL)
            return 0;

        novo->palavra = cria_Palavra(palavra, arq, byte);
        novo->altura = 0;
        novo->esq = novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    ArvAVL atual = *raiz;

    int compara = strcmp((*raiz)->palavra->pal, palavra);
    char inserido = 0;

        if( compara < 0 ){
            if((inserido = insere_ArvAVL(&((*raiz)->esq), palavra, byte, arq)) == 1){
                if(fatorBalanceamento_NO(*raiz) >= 2){
                    if(strcmp(((*raiz)->esq)->palavra->pal, palavra) > 0){
                        RotacaoRR(raiz);
                    } else {
                        RotacaoRL(raiz);
                    }
                }
            }
        } else if( !compara ){ 
            adiciona_IndicePal((*raiz)->palavra, byte, arq);
            return   0;
        }
        else{
            if((inserido = insere_ArvAVL(&((*raiz)->dir), palavra, byte, arq)) == 1){
                if(fatorBalanceamento_NO(*raiz) >= 2){
                    if(strcmp(((*raiz)->dir)->palavra->pal, palavra) < 0){ 
                        RotacaoLL(raiz);
                    } else {
                        RotacaoLR(raiz);
                    }
                } 
            }
        }

        atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return inserido; 
}

/*
OBJETIVO: Funcao que avalia e retorna se duas strings são iguais.
IMPUTS: Um ponteiro do tipo char para 'str1' e um ponteiro do tipo char para 'str2'.
OUTPUTS: 1 se as strings de entrada são iguais e 0 caso contrário.
*/
char strings_IguaisAVL(char *str1, char *str2){
    if(str1 == NULL || str2 == NULL) return 0;
    if(strlen(str1) == strlen(str2))
        if(strcasecmp(str1, str2) == 0)
            return 1;
    return 0;
}

/*
OBJETIVO: Funcao que libera da memória um ponteiro do tipo tNO, junto com seus NOs a esquerda e direita.
IMPUTS: Um ponteiro do tipo ArvAVL 'raiz'.
OUTPUTS: Nenhum.
*/
void libera_NOAVL(ArvAVL no){
    if(no == NULL)
        return;
    libera_NOAVL(no->esq);
    libera_NOAVL(no->dir);
    destroi_Palavra(no->palavra);
    free(no);
    no = NULL;
}

/*
OBJETIVO: Funcao que libera da memória um ponteiro do tipo tArvBin, junto com todos os seus NOs da arvore.
IMPUTS: Um ponteiro do tipo ArvAVL 'raiz'.
OUTPUTS: Nenhum.
*/
void destroi_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NOAVL(*raiz);//libera cada no
    free(raiz);//libera a raiz
    raiz = NULL;
}

/*
OBJETIVO: Funcao que verifica se a arvore esta vazia.
IMPUTS: Um ponteiro do tipo ArvAVL para 'raiz', um ponteiro do tipo char para 'palavra'.
OUTPUTS: 1 se esta vazia e 0 caso contrário.
*/
int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}


int desempenho_ArvAVL(int argc, char *argv[]){
    int nBuscas = atoi(argv[1]);
    if(argc < 2 || nBuscas < 1 ){
        printf("#Usagem do programa:\n#./LEIA_O_MAKEFILE [nPalavras] [arquivos..]\n#\tOnde:\n#nPalavras = numeros de palavras a aleatorias a ser pesquisada em cada estrutura\n#arquivos = Os arquivo que serao passados para o programa indexar, separados por espaço.\n");
        return 0;
    }
    ArvAVL *a;
    char pal[NPAL];
    // tamanho arbitrariamente grande
    int byte = 0, nArquivos = argc - 2;
    FILE *arquivo = NULL;
    a = cria_ArvAVL();
    int sizes[nBuscas - 2];
    clock_t t, tAll = 0;

    int ret = 0;

    for(int i = 0; i < nArquivos; i++){
        if(abre_Arquivo(argv[i + 2], &arquivo) != 1){
            printf("Erro ao abrir o arquivo %s!\n", argv[i + 2]);
            return 1;
        }
        sizes[i] = tamanhoArquivo(arquivo);
        t = clock();
        while(pega_Palavra(arquivo, pal, &byte) == 1){
            if((ret = insere_ArvAVL(a, pal, byte, i)) != 1) printf("Erro ao tentar inserir %s! Retorno = %d    ", pal, ret);
        }
        tAll += clock() - t;  
        fecha_Arquivo(arquivo);
        arquivo = NULL;
    }

    double time_taken = ((double)tAll)/CLOCKS_PER_SEC; // in seconds 
    printf("%lf ", time_taken);

    
    // Lê palavras aletórias dentro de arquivos aleatórios dentro dos de entrada.
    srand(time(NULL));
    char palavras[nBuscas][NPAL];
    char arq = 0;
    int pos = 0 ;
    for(int i = 0; i < nBuscas; i++){
        arq = (rand() % (argc - 2)) + 2;
        pos = rand() % sizes[(int) arq - 2];
        if(abre_Arquivo(argv[(int) arq], &arquivo) != 1) printf("Deu ruim ao abrir o arquivo %s!\n", argv[(int) arq]);
        fseek(arquivo, pos, 0); // Aponta o ponteiro de stream (arquivo) para a posição "pos" (aleatóriamente gerada)
        while(eValido(fgetc(arquivo)));
        if(!pega_Palavra(arquivo, palavras[i], &byte)){
            rewind(arquivo);
            pega_Palavra(arquivo, palavras[i], &byte);
        }
        fecha_Arquivo(arquivo);
        arquivo = NULL;
    }

    // Carrega palavras aleatórias do vetor gerado previamente e busca elas na estrutura
    srand(rand());
    t = clock();
    for(int i = 0; i < nBuscas; i++)
            consulta_ArvAVL(a, palavras[i]);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%lf\n", time_taken);

    destroi_ArvAVL(a);

    return 0;
}
