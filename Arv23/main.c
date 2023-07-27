#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "arv23.h"

Info *buscaPalavra1(Arv23 *raiz, char *palavra, Info **aux, int *nos){

    if(raiz != NULL){
        *nos += 1;
        if(strcmp(palavra, raiz->info1->palavra) == 0)
            *aux = raiz->info1;
        if(raiz->numInfo == 2){
            if(strcmp(palavra, raiz->info2->palavra) == 0)
                *aux = raiz->info2;
        }
        
        if(strcmp(palavra, raiz->info1->palavra) < 0)   
            buscaPalavra(raiz->esq, palavra, aux);
        
        else if((raiz->numInfo == 1) || (raiz->numInfo == 2 && strcmp(palavra, raiz->info2->palavra) < 0))
            buscaPalavra(raiz->centro, palavra, aux);

        else
            buscaPalavra(raiz->dir, palavra, aux);
    }
}

int main(){
    Arv23 *raiz;
    raiz = NULL;

    Info *infoSobe, *aux;
    aux = NULL;
    
    char path[200], palavra[50], nomeArquivo[50], resultado[100];
    int inseriu[4] = {0}, op = -1, linha = 0, sinalization = -1, nos = 0;

    // lerArquivo("arquivo.txt", &raiz, resultado);
    lerArquivo("arquivo.txt", &raiz, resultado);
    imprimirArv(raiz);

    clock_t inicio, fim;

// Variáveil para armazenar o tempo

    double tempo = 0.0;

// clock() é uma função que marca um momento da medição
    for(int i = 0; i < 30; i++){
        inicio = clock();
        buscaPalavra(raiz, "texto", &aux);
        // buscaPalavra1(raiz, "texto", &aux, &nos);
        fim = clock();    
        tempo += (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
    }

    if(aux != NULL){
        printf("\n");
        imprimirInfo(aux);
    }else
        printf("\nPalavra não encontrada\n");

    // tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
    tempo = tempo / 30;
    printf("%f\n", tempo);
    printf("%d\n", nos);

    while (op != 0) {
        printf("\n");
        printf("0 - Encerrar\n"
               "1 - Ler arquivo texto\n"
               "2 - Imprimir arvore em ordem\n"
               "3 - Buscar palavra\n"
               "4 - Adicionar palavra\n"
               "5 - Excluir palavra\n"
               "Digite a opcao: ");
        scanf("%d", &op);

        switch (op){
        case 1:
            printf("Deseja ler o arquivo? 1 - sim / 0 - nao: ");
            scanf(" %d", &sinalization);

            if(sinalization == 1){
                printf("Digite o nome do arquivo com .txt no final: ");
                scanf("%s", nomeArquivo);

                lerArquivo(nomeArquivo, &raiz, resultado);
                printf("%s", resultado);
            }

            break;
        case 2:
            printf("Deseja imprimir a arvore? 1 - sim / 0 - nao: ");
            scanf(" %d", &sinalization);

            if(sinalization == 1){
                if(raiz != NULL){
                    imprimirArv(raiz);
                }else{
                    printf("Arvore vazia\n");
                }
            }
            break;
        case 3:

            printf("Deseja buscar uma palavra na arvore? 1 - sim / 0 - nao: ");
            scanf(" %d", &sinalization);

            if(sinalization == 1){
                if(raiz != NULL){
                    printf("Digite a palavra que deseja buscar: ");
                    scanf(" %s", palavra);
                    buscaPalavra(raiz, palavra, &aux);
                    if(aux != NULL){
                        printf("Palavra encontrada\n");
                        imprimirInfo(aux);
                    }else
                        printf("Palavra nao encontrada\n");
                }else{
                    printf("Arvore vazia\n");
                }
            }
            break;
        case 4:
            printf("Deseja inserir uma palavra na arvore? 1 - sim / 0 - nao: ");
            scanf(" %d", &sinalization);

            if(sinalization == 1){
                
                printf("Digite a palavra: ");
                scanf(" %s", palavra);
                printf("Digite a linha: ");
                scanf(" %d", &linha);

                if(linha > 0){
                    auxiliaInsere(&raiz, palavra, linha, NULL, &infoSobe, resultado);
                    printf("%s", resultado);
                    
                }else{
                    printf("Linha invalida\n");
                }
            }
            break;
        case 5:
            printf("Deseja excluir uma palavra na arvore? 1 - sim / 0 - nao: ");
            scanf(" %d", &sinalization);

            if(sinalization == 1){
                if(raiz != NULL){
                    printf("Digite a palavra que deseja excluir: ");
                    scanf(" %s", palavra);
                    printf("Digite a linha: ");
                    scanf(" %d", &linha);
                    auxRemover(&raiz, palavra, linha, resultado);
                    printf("%s", resultado);
                }else{
                    printf("Arvore vazia\n");
                }
            }
            break;
        default:
            break;
        }
    }

    return 0;
}