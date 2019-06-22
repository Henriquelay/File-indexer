#	A Flag -c diz para gerar o arquivo de objeto, o -o $@ diz para colocar a saída da compilação no arquivo nomeado no lado esquerdo do :, o $< é o primeiro item na lista de dependências, e o A macro CFLAGS é definida como acima.
#	Como simplificação final, vamos usar as macros especiais $@ e $^, que são os lados esquerdo e direito de :, respectivamente, para tornar a regra geral de compilação mais geral. 
#	No exemplo abaixo, todos os arquivos de inclusão devem ser listados como parte da macro DEPS e todos os arquivos de objetos devem ser listados como parte da macro OBJ.

#Flags interessantes
#-Wall dispara todos os warnings em seu código
#-g necessário para avaliar o código do valgrind (permite o valgrind dizer em que linha dá merda)
#-lm obrigatorio caso utilize a biblioteca math.h

CC=gcc
CFLAGS=-Wall -g
DEPS=lista.h arquivos.h
DEPSDIR= headers
_DEPS=$(patsubst %,${DEPSDIR}/%,${DEPS})
OBJ=lista.o arquivos.o main.o
OBJDIR=src
_OBJ=$(patsubst %,${OBJDIR}/%,${OBJ})
EXEC=LEIA_O_MAKEFILE

${OBJDIR}/%.o: %.c ${_DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

all: ${_OBJ}
	${CC} -o ${EXEC} $^ ${CFLAGS}
	rm -f ${OBJDIR}/*.o

run: 
	make all
	./${EXEC} 1 data/Teste-SA.txt

valzin: 
	make all
	valgrind ./${EXEC} 1 data/Teste-SA.txt

val:
	make all
	valgrind --leak-check=full ./${EXEC} 1 data/Teste-SA.txt

valzao:
	make all
	valgrind --leak-check=full --show-leak-kinds=all ./${EXEC} 1 data/Teste-SA.txt

clear:
	rm -f *.o
	rm -f ${OBJDIR}/*.o
	rm -f ${EXEC}
	#rm -f main
	clear

push:
	gitPusher ${msg}
