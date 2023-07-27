#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arv23.h"

int main(){
    Arv23 *raiz;
    raiz = NULL;

    Info *infoSobe, *aux;
    aux = NULL;
    
    char path[200], palavra[50], nomeArquivo[50], resultado[100];
    int inseriu[4] = {0}, op = -1, linha = 0, sinalization = -1;

    lerArquivo("arquivo.txt", &raiz, resultado);

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
                    // remover23(NULL, &raiz, palavra, resultado);
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