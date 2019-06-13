#include "../headers/lista.h"

int main(void){
    printf("TAMPAL\n");
    tListaSent *l = inicia_ListaSent();

    if(insere_Lista(l, "thomas")) puts("Inseriu");



    destroi_Lista(l);
    return 0;
}
