#	A Flag -c diz para gerar o arquivo de objeto, o -o $@ diz para colocar a saída da compilação no arquivo nomeado no lado esquerdo do :, o $< é o primeiro item na Lista de dependências, e o A macro CFLAGS é definida como acima.
#	Como simplificação final, vamos usar as macros especiais $@ e $^, que são os lados esquerdo e direito de :, respectivamente, para tornar a regra geral de compilação mais geral. 
#	No exemplo abaixo, todos os Arquivos de inclusão devem ser listados como parte da macro DEPS e todos os Arquivos de objetos devem ser listados como parte da macro OBJ.

#Flags interessantes
#-Wall dispara todos os warnings em seu código
#-g necessário para avaliar o código do valgrind (permite o valgrind dizer em que linha dá merda)
#-lm obrigatorio caso utilize a biblioteca math.h

CC			=gcc
CFLAGS		=-Wall -g -lm -O3
DEPS		=Lista.h Arquivos.h ArvoreBinaria.h ArvoreAVL.h Hash.h Base.h Trie.h
DEPSDIR		=headers
_DEPS		=$(patsubst %,${DEPSDIR}/%,${DEPS})
OBJDIR		=src

ARQUIVO		=data/APRENDE.txt
BUSCAS		=10
EXEC		=menu

OBJLISTA	=Arquivos.o Base.o Lista.o
_OBJLISTA	=$(patsubst %,${OBJDIR}/%,${OBJLISTA})

OBJARVBIN	=Arquivos.o Base.o ArvoreBinaria.o
_OBJARVBIN	=$(patsubst %,${OBJDIR}/%,${OBJARVBIN})

OBJARVAVL	=Arquivos.o testArvoreAVL.o Base.o ArvoreAVL.o
_OBJARVAVL	=$(patsubst %,${OBJDIR}/%,${OBJARVAVL})

OBJHASH		=Arquivos.o testHash.o Base.o ArvoreAVL.o Hash.o
_OBJHASH	=$(patsubst %,${OBJDIR}/%,${OBJHASH})

OBJTRIE		=Arquivos.o testTrie.o Base.o Trie.o
_OBJTRIE	=$(patsubst %,${OBJDIR}/%,${OBJTRIE})

OBJMENU		=menu.o Base.o Arquivos.o Lista.o ArvoreBinaria.o ArvoreAVL.o Hash.o Trie.o
_OBJMENU	=$(patsubst %,${OBJDIR}/%,${OBJMENU})




${OBJDIR}/%.o: %.c ${_DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

all: menu #ArvBin ArvAVL Hash Trie Lista
	rm src/*.o

Lista: ${_OBJLISTA} 
	${CC} -o Lista $^ ${CFLAGS}

ArvBin: ${_OBJARVBIN} 
	${CC} -o ArvBin $^ ${CFLAGS}

ArvAVL: ${_OBJARVAVL} 
	${CC} -o ArvAVL $^ ${CFLAGS}

Hash: ${_OBJHASH} 
	${CC} -o Hash $^ ${CFLAGS}

Trie: ${_OBJTRIE} 
	${CC} -o Trie $^ ${CFLAGS}

menu: ${_OBJMENU}
	${CC} -o LEIA_O_README $^ ${CFLAGS}

valzin: 
	make all
	valgrind ./${EXEC} ${BUSCAS} ${ARQUIVO}

val:
	make all
	valgrind --leak-check=full ./${EXEC} ${BUSCAS} ${ARQUIVO} 

valzao:
	make all
	valgrind --leak-check=full --show-leak-kinds=all ./${EXEC} ${BUSCAS} ${ARQUIVO}

clear:
	rm -f *.o
	rm -f ${OBJDIR}/*.o
	rm -f menu
	rm -f Trie
	rm -f Hash
	rm -f ArvBin
	rm -f ArvAVL
	rm -f Lista
	clear
	make
	rm -f *.o

push:
	gitPusher ${msg}
