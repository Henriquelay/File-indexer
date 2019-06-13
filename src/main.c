#include "../headers/lista.h"

int main(void){
    printf("TAMPAL\n");
    tListaSent *l = inicia_ListaSent();

    insere_Lista(l, "thomas");
    insere_Lista(l, "thoMASERrpan");
    insere_Lista(l, "thomaserrpan");
    insere_Lista(l, "thomasaralho");
    insere_Lista(l, "thomanocu");

    if(!print_Lista(l)) puts("Nao consegui printar a lista");


    destroi_Lista(l);
    return 0;
}
