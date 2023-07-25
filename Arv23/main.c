#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arv23.h"

void lerPath(Arv23 **raiz, char path[], int inseriu[]){

    // ler arquvio txt
    int sinalizacao;
    sinalizacao = 0;

    // printf("Deseja ler arquvio? 1 - sim / 0 - nao");
    // scanf(" %d", &sinalizacao);

    // if(sinalizacao == 1){

    //     sinalizacao = 0;

    //     printf("\nDigite o path e nome do arquivo separado por / e com .txt: ");
    //     scanf(" %s", path);
        

    //     while (sinalizacao != 1 ){
    //         printf("O path %s está correto? Digite 1 - sim / 0 - nao: ", path);
    //         scanf(" %d", &sinalizacao);

    //         if(sinalizacao != 1){
    //             printf("\nDigite o path e nome do arquivo separado por / e com .txt: ");
    //             scanf(" %s", path);
    //         }
    //     }
        
        lerArquivo("texto.txt", raiz, inseriu);

        memset(inseriu, 0, sizeof(100));
    // }
}

int main(){
    Arv23 *raiz;
    raiz = NULL;

    Info *infoSobe;
    
    char path[200], palavra[50];
    int inseriu[4] = {0}, op = -1, linha = 0;

    lerPath(&raiz, path, inseriu);
    
    // imprimirArv(raiz);
    remover23(NULL, &raiz, "texto");
    remover23(NULL, &raiz, "na");
    remover23(NULL, &raiz, "baixo");
    remover23(NULL, &raiz, "a");
    remover23(NULL, &raiz, "cima");

    auxiliaInsere(&raiz, "opa", 2, NULL, &infoSobe);


    imprimirArv(raiz);
}