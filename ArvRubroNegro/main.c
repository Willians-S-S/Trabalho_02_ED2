#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rubroNegro.h"
#include "imprimir.h"

void lerPath(Rubro **raiz, char path[], int inseriu[]){

    // ler arquvio txt
    int sinalizacao;
    sinalizacao = 0;

    printf("Deseja ler arquvio? 1 - sim / 0 - nao");
    scanf(" %d", &sinalizacao);

    if(sinalizacao == 1){

        sinalizacao = 0;

        printf("\nDigite o path e nome do arquivo separado por / e com .txt: ");
        scanf(" %s", path);
        

        while (sinalizacao != 1 ){
            printf("O path %s está correto? Digite 1 - sim / 0 - nao: ", path);
            scanf(" %d", &sinalizacao);

            if(sinalizacao != 1){
                printf("\nDigite o path e nome do arquivo separado por / e com .txt: ");
                scanf(" %s", path);
            }
        }
        
        lerArquivo(path, raiz, inseriu);

        memset(inseriu, 0, sizeof(100));
    }
}

void lerPalavra(Rubro **raiz, char palavra[], int linha, int inseriu[]){
    // inserir palavra
    int sinalizacao;
    sinalizacao = 0;

    printf("Deseja inserir uma palavra? 1 - sim / 0 - nao");
    scanf(" %d", &sinalizacao);

    if(sinalizacao == 1){
        sinalizacao = 0;

        printf("\nDigite a palavra: ");
        scanf(" %s", palavra);

        while (sinalizacao != 1 ){
            printf("\n\nA palavra %s está correto? Digite sim - 1 / nao - 0: ", palavra);
            scanf(" %d", &sinalizacao);

            if(sinalizacao != 1){
                printf("\n\nDigite a palavra: ");
                scanf(" %s", palavra);
            }

        }

        printf("\n\nDigite a linha da palavra: ");
        scanf("%d", &linha);

        sinalizacao = 0;

        while (sinalizacao != 1){
            printf("\n\nA linha %d está correto? Digite sim - 1 / nao - 0: ", linha);
            scanf("%d", &sinalizacao);

             if(sinalizacao != 1 ){
                printf("\n\nDigite a linha da palavra: ");
                scanf("%d", &linha);
            }

        }
        

        inserirRubro(raiz, palavra, linha, inseriu);
        memset(inseriu, 0, 4);
    }
}

void imprimirPalavra(Rubro *raiz, char palavra[], int inseriu[]){
    int sinalizacao;
    sinalizacao = 0;

    printf("Deseja imprimir uma palavra? 1 - sim / 0 - nao");
    scanf(" %d", &sinalizacao);

    if(sinalizacao == 1){
        sinalizacao = 0;

        printf("\nDigite a palavra: ");
        scanf(" %s", palavra);

        int sinalizacao;
        sinalizacao = 0;

        printf("\nDigite a palavra: ");
        scanf(" %s", palavra);

        while (sinalizacao != 1 ){
            printf("\n\nA palavra %s está correto? Digite sim - 1 / nao - 0: ", palavra);
            scanf(" %d", &sinalizacao);

            if(sinalizacao != 1){
                printf("\n\nDigite a palavra: ");
                scanf(" %s", palavra);
            }

        }
        
        Rubro *aux;
        aux = buscarPalavra(raiz, palavra, 0, inseriu);
        if(aux != NULL)
            imprimeNo(aux);
        else
            printf("\nPalavra não encontrada\n");
        memset(inseriu, 0, 4);
    }
}

int main(){
    Rubro *raiz;
    raiz = NULL;
    char path[200], palavra[50];
    int inseriu[4] = {0}, op = -1, linha = 0;
    // inserirRubro(&raiz, "opa", 1, inseriu);
    // inserirRubro(&raiz, "opa", 2, inseriu);
    // inserirRubro(&raiz, "amanha", 1, inseriu);
    // inserirRubro(&raiz, "lavamonos", 1, inseriu);

// O programa deve permitir o usuário
// buscar uma palavra e o programa deve responder em quais linhas do texto ela foi utilizada. Além disso, ele
// deve permitir excluir uma palavra de uma linha bem como acrescentar.

    while (op != 0) {
        printf("\n1 - Ler Arquivo\n2 - Inserir Palavra\n3 - Imprimir Arvore\n4 - Imprimir um No\n5 - Excluir Palavra\nDigite a opcao: ");
        scanf("%d", &op);

        switch (op){
            case 1:
                lerPath(&raiz, path, inseriu);        
                break;
            case 2:
                lerPalavra(&raiz, palavra, linha, inseriu);
                break;
            case 3:
                printf("\n");

                if(raiz != NULL)
                    imprimirAvr(raiz);
                else
                    printf("Não existe palavras na arvore!\n");
                // printf("\n");
                break;
            case 4:
                imprimirPalavra(raiz, palavra, inseriu);
                break;
            case 5:
                int flag;

                printf("\nDigite a palavra: ");
                scanf(" %s", palavra);
                printf("Digite a linha da palavra: ");
                scanf("%d", &linha);

                // 200 -> removeu a palavra e a linha
                // 210 -> removeu somente a linha
                // 300 -> encontrou a palavra, mas não a linha
                // 400 -> não encontrou a palavra
                // 500 -> não removeu a linha
                // 510 -> não removeu a palavra

                flag = auxRemover(&raiz, palavra, linha, inseriu);

                if(flag == 400)
                    printf("\nPalavra não encontrada\n");
                else{
                    if(flag == 300)
                        printf("\nPalavra encontrada, mas a linha informada não.\n");
                    else if(flag == 510)
                        printf("\nNão foi possivel remover a palavra\n");
                    else if(flag == 500)
                        printf("\nNão foi possivel remover a linha\n");
                    else if(flag == 200)
                        printf("\nPalavra e linha foram removidas.\n");
                    else if(flag == 210)
                        printf("A palavra foi removida da linha %d.\n", linha);
                        
                }
                // memset zera o vetor
                memset(inseriu, 0, sizeof(inseriu));
                break;
        default:
            break;
        }
    }
    

    if(inseriu[0] == 1){
        printf("Inseriu\n");
    }

    imprimirAvr(raiz);

    return 0;
}