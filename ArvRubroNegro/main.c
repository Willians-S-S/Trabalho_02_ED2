#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rubroNegro.h"


int main(){
    Rubro *raiz;
    raiz = NULL;
    int inseriu[2];
    // inserirRubro(&raiz, "opa", 1, inseriu);
    // inserirRubro(&raiz, "opa", 2, inseriu);
    // inserirRubro(&raiz, "amanha", 1, inseriu);
    // inserirRubro(&raiz, "lavamonos", 1, inseriu);

    lerArquivo("arquivo.txt", &raiz, inseriu);
    if(inseriu[0] == 1){
        printf("Inseriu\n");
    }

    imprimirAvr(raiz);

    return 0;
}