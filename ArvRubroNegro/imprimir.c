#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubroNegro.h"
#include "imprimir.h"


void imprimirLinhas(Linhas *no){
    if(no){
        printf("%d ", no->linha);
        imprimirLinhas(no->prox);
    }

}

void imprimeNo(Rubro *no){
    printf("Palavra: %s, cor: %d, linhas: ", no->info->palavra, cor(no));
    imprimirLinhas(no->info->ListaNum);
    printf("\n");
}

void imprimirAvr(Rubro *raiz){
    if(raiz){
        imprimirAvr(raiz->esq);
        imprimeNo(raiz);
        imprimirAvr(raiz->dir);
    }
}