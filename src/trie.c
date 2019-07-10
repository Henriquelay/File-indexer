#include "../headers/trie.h"

ArvTrie* cria_No_Trie(){
    ArvTrie *nova = (ArvTrie*) malloc(sizeof(ArvTrie));
	if(nova == NULL) return NULL;
	int i = 0;
    
	nova->ehFolha = 0;
	nova->arquivos = NULL;
	for( i = 0 ; i < ALFABETO ; i++ )
		nova->caractere[i] = NULL;

    return nova;
}

char insere_Trie(ArvTrie **raiz, char *palavra, char arq, int indice){
    if(raiz == NULL || palavra == NULL) return 0;
	if(*raiz == NULL || *palavra == '\0') return 0;

    ArvTrie *arvore = *raiz;
    int proximo;

    while(*palavra){
		// configura os indices ASCII para o resultado de "*palavra - 'a'" também funcionar para números
		if(!isalnum(*palavra)) return 0;
		if(isdigit(*palavra))
			*palavra += 49;
        proximo = *palavra - ('a'-10);
		// printf("Inserindo: %c. Antes possivemente %c. proximo = %i\n", *palavra, *palavra-74, proximo);
        if(arvore->caractere[proximo] == NULL)
            arvore->caractere[proximo] = cria_No_Trie();
        arvore = arvore->caractere[proximo];
        palavra++;
    }

    insere_Arquivo(&arvore->arquivos, arq);
	insere_Indice(&arvore->arquivos->ocorrencias, indice);

    arvore->ehFolha++;
	return 1;
}

char consulta_Trie(ArvTrie **raiz, char *palavra){
    if(raiz == NULL) return 0;
	if(*raiz == NULL) return 0;

    ArvTrie *arvore = *raiz;

    while(*palavra){
        arvore = arvore->caractere[*palavra - 'a'];
        if(arvore == NULL) return 0;
        palavra++;
    }

    return arvore->ehFolha;
}

char tem_galho_True(ArvTrie *raiz){
    if(raiz == NULL) return 0;

    for(int i = 0 ; i < ALFABETO ; i++)
        if(raiz->caractere[i]) return 1;

    return 0;
}

void destroi_Trie(ArvTrie **raiz){
    if(raiz == NULL) return;
    if(*raiz == NULL) return;

    for(int i = 0 ; i < ALFABETO ; i++ ){
        destroi_Trie(&((*raiz)->caractere[i]));
    }

    if((*raiz)->ehFolha) destroi_Arquivos((*raiz)->arquivos);
    
    free(*raiz);
	raiz = NULL;
}