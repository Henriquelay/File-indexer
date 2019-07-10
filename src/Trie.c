#include "../headers/Trie.h"

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

int desempenho_Trie(int argc, char *argv[]){
    int nBuscas = atoi(argv[1]);
    if(argc < 2 || nBuscas < 1 ){
        printf("#Usagem do programa:\n#./LEIA_O_MAKEFILE [nPalavras] [arquivos..]\n#\tOnde:\n#nPalavras = numeros de palavras a aleatorias a ser pesquisada em cada estrutura\n#arquivos = Os arquivo que serao passados para o programa indexar, separados por espaço.\n");
        return 0;
    }
    ArvTrie *T;
    char pal[NPAL];
    // tamanho arbitrariamente grande
    int byte = 0, nArquivos = argc - 2;
    FILE *arquivo = NULL;
    T = cria_No_Trie();
    int sizes[nBuscas - 2];
    clock_t t, tAll = 0;

    for(int i = 0; i < nArquivos; i++){
        if(abre_Arquivo(argv[i + 2], &arquivo) != 1){
            printf("Erro ao abrir o arquivo %s!\n", argv[i + 2]);
            return 1;
        }
        sizes[i] = tamanhoArquivo(arquivo);
        t = clock();
        while(pega_Palavra(arquivo, pal, &byte) == 1){
            if(!insere_Trie(&T, pal, byte, i)) printf("Erro ao tentar inserir %s! ", pal);
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
            consulta_Trie(&T, palavras[i]);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%lf\n", time_taken);

    destroi_Trie(&T);

    return 0;
}
