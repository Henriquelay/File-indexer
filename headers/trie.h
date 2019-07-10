#ifndef _TRIE_H_
#define _TRIE_H_

#include "arquivos.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALFABETO 36


//---- Structs -----
typedef struct Trie ArvTrie;
typedef struct Trie{
	int ehFolha;
	ArvTrie *caractere[ALFABETO];
	tArquivo *arquivos;
} ArvTrie;

//------- Funções --------
ArvTrie *cria_No_Trie();
void destroi_Trie(ArvTrie **raiz);
char consulta_Trie(ArvTrie **raiz, char *str);
char tem_galho_True(ArvTrie *raiz);
char insere_Trie(ArvTrie **raiz, char *str, char arq, int indice);

#endif
