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

Rubro *criaNo(char *palavra, int linha, int inseriu[]){
    Rubro *novo;
    novo = (Rubro*) malloc(sizeof(Rubro));
    if(novo != NULL){
        novo->info = (Info*) malloc(sizeof(Info));

        novo->info->palavra = (char*) malloc((strlen(palavra) + 1) * sizeof(char)); // Aloca memória para a palavra


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
    int igualMenorMaior;
    
    if(*raiz != NULL)
        igualMenorMaior = strcmp(palavra, (*raiz)->info->palavra);
    

    if((*raiz) == NULL){
        *raiz = criaNo(palavra, linha, inseriu);
    }
    // verificar se o valor está na arvore, se estiver colocar o numero da linha na lista de numeros.
    else if(igualMenorMaior == 0){
        inseriu[0] = 2;
        inserirLinha(&((*raiz)->info->ListaNum), linha, inseriu);

    }else if(igualMenorMaior < 0)
        inserirPalavra(&((*raiz)->esq), palavra, linha, inseriu); 

    else
        inserirPalavra(&((*raiz)->dir), palavra, linha, inseriu);

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

void trocaCor(Rubro *raiz){
    if(raiz){
        raiz->cor = !raiz->cor;
        if(raiz->dir)
            raiz->dir->cor = !raiz->dir->cor;
        if(raiz->esq)
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

void lerArquivo(char *path, Rubro **raiz, int inseriu[]){
    FILE *arquivo;
    arquivo = fopen(path, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.");
    }

    char frase[100], *palavra;

    int linha = 1;

    while(fgets(frase, sizeof(frase), arquivo) != NULL){
        palavra = strtok(frase, " ");

        while (palavra != NULL){
            palavra[strcspn(palavra, "\n")] = '\0'; // strcspn(palavra, "\n") encontra a primeira posição de \n. e substtui por \0
            inserirRubro(raiz, palavra, linha, inseriu);
            palavra = strtok(NULL, " ");
        }
        linha += 1;
    }

}

// achou tem que vim de fora com as duas posições zeradas

int buscaLinha(Linhas *no, int linha, int achou[]){
    int flag = 0;
    if(no){
        if(no->linha == linha)
            // achou[1] = 1;
            flag = 1;
        else
            flag = buscaLinha(no->prox, linha, achou);
    }
    return flag;
}

Rubro *buscarPalavra(Rubro *raiz, char *palavra, int linha, int achou[]){
    Rubro *aux;
    aux = NULL;
    if(raiz){
        int igualMenorMaior;
     
        igualMenorMaior = strcmp(palavra, raiz->info->palavra);

        if(igualMenorMaior == 0){
            // achou[0] = 1;
            aux = raiz;
            // buscaLinha(raiz->info->ListaNum, linha, achou);
        }else if(igualMenorMaior < 0)
           aux = buscarPalavra(raiz->esq, palavra, linha, achou);
        else
           aux = buscarPalavra(raiz->dir, palavra, linha, achou);
    }
    return aux;
}

Rubro *buscarPalavra1(Rubro *raiz, char *palavra, int achou[]){
    Rubro *aux;
    aux = NULL;
    if(raiz){
        int igualMenorMaior;
        igualMenorMaior = strcmp(palavra, raiz->info->palavra);

        if(igualMenorMaior == 0){
            aux = raiz;
        }else if(igualMenorMaior < 0)
           aux = buscarPalavra1(raiz->esq, palavra, achou);
        else
           aux = buscarPalavra1(raiz->dir, palavra, achou);
    }
    return aux;
}

int removeLinha(Linhas **no, int linha, int achou[]){
    int flag;
    flag = 0;
    if(*no){
        if((*no)->linha == linha){
            if((*no)->prox == NULL){// remove o ultimo nó
                free(*no);
                *no = NULL;
                // achou[2] = 1;
                flag = 1;
            }else{ // remove o nó que estar no meio
                Linhas *aux;
                aux = *no;
                *no = (*no)->prox;
                free(aux);
                // achou[2] = 1;
                flag = 1;
            }
        }
        else
            flag = removeLinha(&((*no)->prox), linha, achou);
    }
    return flag;
}

Rubro *procuraMenor(Rubro *raiz){
    Rubro *aux;
    if(raiz){
        if(raiz->esq != NULL)
            aux = procuraMenor(raiz->esq);
        else
            aux = raiz;
    }
    return aux;
}

void removeMenor(Rubro **raiz){
    if((*raiz)->esq == NULL){
        free(*raiz);
        *raiz = NULL;
    }
    if(cor((*raiz)->esq) == BLACK && cor((*raiz)->esq->esq) == BLACK)
        mover2EsqRed(raiz);

    removeMenor(&((*raiz)->esq));
    balancear(raiz);
} 

void mover2EsqRed(Rubro **raiz){
    trocaCor(*raiz);
    if(cor((*raiz)->dir->esq) == RED){
        rotacaoDir(&((*raiz)->dir));
        rotacaoEsq(raiz);
        trocaCor(*raiz);
    }
}

void mover2DirRed(Rubro **raiz){
    trocaCor(*raiz);
    if(cor((*raiz)->esq->esq) == RED){
        rotacaoDir(&((*raiz)->dir));
        trocaCor(*raiz);
    }
}

void balancear(Rubro **raiz){
    if(*raiz != NULL){
        if(cor((*raiz)->dir) == RED)
            rotacaoEsq(raiz);
        
        if((*raiz)->esq != NULL && cor((*raiz)->dir) == RED && cor((*raiz)->esq->esq) == RED)
            rotacaoDir(raiz);

        if(cor((*raiz)->esq) == RED && cor((*raiz)->dir) == RED)
            trocaCor(*raiz);
    }
}

int removePalavra(Rubro **raiz, char *palavra){
/*
Remove uma palavra de uma árvore Rubro Negro.

  Args:
    raiz: Ponteiro para a raiz da árvore.
    palavra: A palavra a ser removida.
    linha: A linha da palavra na lista de palavras.
    achou: Um vetor booleano que indica se a palavra foi encontrada na árvore.

  Returns:
    1: Se a palavra foi encontrada e removida da árvore.
    0: Se a palavra não foi encontrada na árvore.

*/
    
    int igualMenorMaior, flag = 0;

    igualMenorMaior = strcmp(palavra, (*raiz)->info->palavra);
    
    if(igualMenorMaior < 0){
        
        if(cor((*raiz)->esq) == BLACK && (*raiz)->esq->esq == BLACK)
            mover2EsqRed(raiz);

        flag = removePalavra(&((*raiz)->esq), palavra);

    }else{
        if(cor((*raiz)->esq) == RED)
            rotacaoDir(raiz);
        
        if(igualMenorMaior == 0 && ((*raiz)->dir == NULL)){
            free(*raiz);
            *raiz = NULL;
            flag = 1;
        }else{
            if(cor((*raiz)->dir) == BLACK && cor((*raiz)->dir->esq) == BLACK) 
                    mover2DirRed(raiz);
            
            if(igualMenorMaior == 0){
                Rubro *aux;
                aux = procuraMenor((*raiz)->dir);
                strcpy((*raiz)->info->palavra, aux->info->palavra);
                (*raiz)->info->ListaNum = aux->info->ListaNum;
                removeMenor(&((*raiz)->dir));
                flag = 1;
            }else
                flag = removePalavra(&((*raiz)->dir), palavra);
        }
    }
    balancear(raiz);
    return flag;
}

// 200 -> removeu a palavra e a linha
// 210 -> removeu somente a linha
// 300 -> encontrou a palavra, mas não a linha
// 400 -> não encontrou a palavra
// 500 -> não removeu a linha
// 510 -> não removeu a palavra


int auxRemover(Rubro **raiz, char *palavra, int linha, int achou[]){
    int flag = 400; // -> não encontrou a palavra
    
    if(*raiz){
        Rubro *aux;

        aux = buscarPalavra(*raiz, palavra, linha, achou); 
        printf("%s", aux->info->palavra);
        if(aux){ // entra se encontou a palavra
            if(buscaLinha(aux->info->ListaNum, linha, achou)){ // entra se encontou a linha
                if(removeLinha(&aux->info->ListaNum, linha, achou)){ // entra se removeu a linha
                    flag = 210; // -> removeu somente a linha
                    if(aux->info->ListaNum == NULL){ // entra se a palavra não existe em mais nenhuma linha
                        if(removePalavra(raiz, palavra)) // entra se a palavra foi removida
                            flag = 200; // -> removeu a palavra e a linha
                        else
                            flag = 510; // -> não removeu a palavra
                    }
                }else
                    flag = 500; // -> não removeu a linha
            }else
                flag = 300; // -> encontrou a palavra, mas não a linha
        }
    }
    return flag;
}