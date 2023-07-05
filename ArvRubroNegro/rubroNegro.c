#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubroNegro.h"

#define RED 1
#define BLACK 0

int cor(Rubro *raiz){
    int c;
    if(raiz == NULL)
        c = BLACK;
    else
        c = raiz->cor;
    return c;
}

void inserirLinha(Linhas **no, int linha, int inseriu[]){
    if(*no == NULL){
        *no = (Linhas*) malloc(sizeof(Linhas));

        if(*no != NULL){
            (*no)->linha = linha;
            (*no)->prox = NULL;
            // inseriu[1] indica que inseriu o numero na lista ou não, 1 para sim 0 para não
            inseriu[1] = 1;
        }else
            inseriu[1] = 0;
    }else
        inserirLinha(&((*no)->prox), linha, inseriu);
}

Rubro *criaNo(char palavra[], int linha, int inseriu[]){
    Rubro *novo;
    novo = (Rubro*) malloc(sizeof(Rubro));
    if(novo != NULL){
        novo->info = (Info*) malloc(sizeof(Info));

        strcpy(novo->info->palavra, palavra);
        inserirLinha(&(novo->info->ListaNum), linha, inseriu);

        novo->cor = RED;
        novo->esq = NULL;
        novo->dir = NULL;
        // inseriu[0] indica que inseriu, não inseriu ou já esta na arvore. 1 para sim, 0 para não e 2 para já existe. 
        inseriu[0] = 1;
    }else
        inseriu[0] = 0;

    return novo;
}

void inserirPalavra(Rubro **raiz, char *palavra, int linha, int inseriu[]){
    if((*raiz) == NULL){
        *raiz = criaNo(palavra, linha, inseriu);
    }
    // verificar se o valor está na arvore, se estiver colocar o numero da linha na lista de numeros.
    else if(strcmp((*raiz)->info->palavra, palavra) == 0){
        inseriu[0] = 2;
        inserirLinha(&((*raiz)->info->ListaNum), linha, inseriu);

    }else if(strcmp((*raiz)->info->palavra, palavra) > 0)
        inserirPalavra(&((*raiz)->dir), palavra, linha, inseriu); 

    else
        inserirPalavra(&((*raiz)->esq), palavra, linha, inseriu);

    if(cor((*raiz)->dir) == RED && cor((*raiz)->esq) == BLACK)
        rotacaoEsq(raiz);

    if(cor((*raiz)->esq) == RED && cor((*raiz)->esq->esq) == RED){
        rotacaoDir(raiz);
    }
        

    if(cor((*raiz)->esq) == RED && cor((*raiz)->dir) == RED)
        trocaCor(*raiz);
}

void inserirRubro(Rubro **raiz, char *palavra, int linha, int inseriu[]){
    inserirPalavra(raiz, palavra, linha, inseriu);
    if(*raiz)
        (*raiz)->cor = BLACK;
}

void imprimirLinhas(Linhas *no){
    if(no){
        printf("%d ", no->linha);
        imprimirLinhas(no->prox);
    }

}

void imprimirAvr(Rubro *raiz){
    if(raiz){
        printf("Palavra: %s e linhas: ", raiz->info->palavra);
        imprimirLinhas(raiz->info->ListaNum);
        printf("\n");
        imprimirAvr(raiz->esq);
        imprimirAvr(raiz->dir);
    }
}

void trocaCor(Rubro *raiz){
    if(raiz){
        raiz->cor = !raiz->cor;
        if(raiz->dir)
            raiz->dir->cor = !raiz->dir->cor;
        else if(raiz->esq)
            raiz->esq->cor = !raiz->esq->cor; 
    }
}

void rotacaoEsq(Rubro **raiz){
    Rubro *aux;

    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;

}

void rotacaoDir(Rubro **raiz){
    Rubro *aux;

    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}