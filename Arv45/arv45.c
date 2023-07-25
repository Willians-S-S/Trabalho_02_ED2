#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Info Info;
// s  informações  de  cada  calçado  são:  código, tipo,   marca,   tamanho,   quantidade   e   preço.
struct Info{
    int cod, tam, qtd, linha;
    char *tipo, *marca;
    float preco;
};


typedef struct Arv45 Arv45;

struct Arv45{
    Info *info1, *info2, *info3, *info4;
    int qtdInfo;

    Arv45 *esq, *centro_esq, *centro, *centro_dir, *dir;
};

Arv45 *insere45(Arv45 **raiz, Arv45 *pai, Info **sobe, int cod, int tam, int qtd, int linha, char *tipo, char *marca, float preco);

void lerArquivo(Arv45 **raiz, Info **sobe){
    FILE *arquivo;
    int cod, tam, qtd, linha;
    char tipo[100], marca[100];
    float preco;

    // Abrir o arquivo para leitura
    arquivo = fopen("loja.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        // return 1;
    }

    linha = 1;

    // Ler cada linha do arquivo até o final
    while (fscanf(arquivo, "%d %d %d %s %s %f\n", &cod, &tam, &qtd, tipo, marca, &preco) == 6) {
        // Aqui você pode fazer o que desejar com os dados lidos de cada linha
        // Por exemplo, imprimir os valores na tela
        // printf("cod: %d\n", cod);
        // printf("tam: %d\n", tam);
        // printf("qtd: %d\n", qtd);
        // printf("linha: %d\n", linha);
        // printf("tipo: %s\n", tipo);
        // printf("marca: %s\n", marca);
        // printf("preco: %.2f\n", preco);

        insere45(raiz, NULL, sobe, cod, tam, qtd, linha, tipo, marca, preco);

        linha++;
    }

    // Fechar o arquivo
    fclose(arquivo);
}

Info *criaInfo(int cod, int tam, int qtd, int linha, char *tipo, char *marca, float preco){
    Info *info;

    info = (Info*) malloc(sizeof(Info));

    info->cod = cod;
    info->tam = tam;
    info->qtd = qtd;
    info->linha = linha;


    info->tipo = (char *) malloc(sizeof(char) *(strlen(tipo) + 1));
    strcpy(info->tipo, tipo);

    info->marca = (char *) malloc(sizeof(char) *(strlen(marca) + 1));
    strcpy(info->marca, marca);

    info->preco = preco;

    return info;
}

Arv45 *criaNo(Info *info, Arv45 * No_esq, Arv45 * No_centro_esq){
    Arv45 *No;
    No = (Arv45 *) malloc(sizeof(Arv45));

    No->info1 = info;
    No->qtdInfo = 1;
    No->esq = No_esq;
    No->centro_esq = No_centro_esq;
    No->centro = NULL;
    No->centro_dir = NULL;
    No->dir = NULL;

    return No;
}

int folha(Arv45 *No){
    int eh = 0;
    if(No->esq == NULL)
        eh = 1;
    return eh;
}

void adicionaNo(Arv45 **No, Info *info, Arv45 *filho){

    if((*No)->qtdInfo == 1){
        if(info->cod > (*No)->info1->cod){
            (*No)->info2 = info;
            (*No)->centro = filho;

        }else{
            (*No)->info2 = (*No)->info1;
            (*No)->info1 = info;

            (*No)->centro = (*No)->centro_esq;
            (*No)->centro_esq = filho;

        }
        (*No)->qtdInfo = 2;

    }else if((*No)->qtdInfo == 2){

        if(info->cod > (*No)->info2->cod){
            (*No)->info3 = info;
            (*No)->centro_dir = filho;

        }else if(info->cod > (*No)->info1->cod && info->cod < (*No)->info2->cod){
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = info;

            (*No)->centro_dir = (*No)->centro;
            (*No)->centro = filho;

        }else{
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = (*No)->info1;
            (*No)->info1 = info;

            (*No)->centro_dir = (*No)->centro;
            (*No)->centro = (*No)->centro_esq;
            (*No)->centro_esq = filho;

        }
        (*No)->qtdInfo = 3;

    }else{
        if(info->cod > (*No)->info3->cod){
            (*No)->info4 = info;
            (*No)->dir = filho;

        }else if(info->cod > (*No)->info2->cod && info->cod < (*No)->info3->cod){
            (*No)->info4 = (*No)->info3;
            (*No)->info3 = info;

            (*No)->dir = (*No)->centro_dir;
            (*No)->centro_dir = filho;

        }else if (info->cod > (*No)->info1->cod && info->cod < (*No)->info2->cod){
            (*No)->info4 = (*No)->info3;
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = info;

            (*No)->dir = (*No)->centro_dir;
            (*No)->centro_dir = (*No)->centro;
            (*No)->centro = filho;

        }else{
            (*No)->info4 = (*No)->info3;
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = (*No)->info1;
            (*No)->info1 = info;

            (*No)->dir = (*No)->centro_dir;
            (*No)->centro_dir = (*No)->centro;
            (*No)->centro = (*No)->centro_esq;
            (*No)->centro_esq = filho;
        }
        (*No)->qtdInfo = 4;
        
    }
}

Arv45 *quebraNo(Arv45 **raiz, Info *info, Info **sobe, Arv45 *filho){
    Arv45 *maiorNo;

    if(info->cod > (*raiz)->info4->cod){
        *sobe = (*raiz)->info3;

        maiorNo = criaNo((*raiz)->info4, (*raiz)->centro_dir, (*raiz)->dir);
        
        maiorNo->info2 = info;

        maiorNo->centro = filho;

        maiorNo->qtdInfo = 2;

    } else if(info->cod > (*raiz)->info3->cod){
        *sobe = (*raiz)->info3;

        maiorNo = criaNo(info, (*raiz)->centro_dir, filho);
        
        maiorNo->info2 = (*raiz)->info4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

    }else if(info->cod > (*raiz)->info2->cod){
        *sobe = info;
        
        maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->centro_dir);
        
        maiorNo->info2 = (*raiz)->info4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

    }else if(info->cod > (*raiz)->info1->cod){
        *sobe = (*raiz)->info2;

        maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->centro_dir);
        
        maiorNo->info2 = (*raiz)->info4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

        (*raiz)->info2 = info;
        (*raiz)->centro = filho;

    }else{
        *sobe = (*raiz)->info2;

        maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->centro_dir);
        
        maiorNo->info2 = (*raiz)->info4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->centro = (*raiz)->centro_esq;
        
        (*raiz)->info1 = info;
        (*raiz)->centro_esq = filho;

    }

    (*raiz)->qtdInfo = 2;
    (*raiz)->centro_dir = NULL;
    (*raiz)->dir = NULL;

    return maiorNo;
    
}

Arv45 *insere45(Arv45 **raiz, Arv45 *pai, Info **sobe, int cod, int tam, int qtd, int linha, char *tipo, char *marca, float preco){
    Arv45 *maiorNO;

    if(*raiz == NULL){
        *raiz = criaNo(criaInfo(cod, tam, qtd, linha, tipo, marca, preco), NULL, NULL);
    }else{
        if(folha(*raiz)){
            if((*raiz)->qtdInfo < 4){
                adicionaNo(raiz, criaInfo(cod, tam, qtd, linha, tipo, marca, preco), NULL);
                maiorNO = NULL;
            }else{
                maiorNO = quebraNo(raiz, criaInfo(cod, tam, qtd, linha, tipo, marca, preco), sobe, NULL);

                if(pai == NULL){
                    *raiz = criaNo(*sobe, *raiz, maiorNO);
                    maiorNO = NULL;
                }
            }
        }else{
            if(cod < (*raiz)->info1->cod)
                maiorNO = insere45(&((*raiz)->esq), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco);

            else if((*raiz)->qtdInfo == 1 || ((*raiz)->qtdInfo <= 4 && cod < (*raiz)->info2->cod))
                maiorNO = insere45(&((*raiz)->centro_esq), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco);

            else if(((*raiz)->qtdInfo == 2)  || ((*raiz)->qtdInfo <= 4 && cod < (*raiz)->info3->cod))
                maiorNO = insere45(&((*raiz)->centro), *raiz,  sobe, cod, tam, qtd, linha, tipo, marca, preco);

            else if(((*raiz)->qtdInfo == 3) || ((*raiz)->qtdInfo == 4 && cod < (*raiz)->info4->cod))
                maiorNO = insere45(&((*raiz)->centro_dir), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco);

            else 
                maiorNO = insere45(&((*raiz)->dir), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco);

            if(maiorNO){
                if((*raiz)->qtdInfo < 4){
                    adicionaNo(raiz, *sobe, maiorNO);
                    maiorNO = NULL;
                }else{
                    maiorNO = quebraNo(raiz, criaInfo(cod, tam, qtd, linha, tipo, marca, preco), sobe, maiorNO);

                    if(pai == NULL){
                        *raiz = criaNo(*sobe, *raiz, maiorNO);
                        maiorNO = NULL;
                    }
                }
            }
        }
    }
    return maiorNO;
}

// void mostrar(Arv45 *Raiz) {
//     if (Raiz != NULL) {
//         printf("%d ", Raiz->info1);
//         if(Raiz->qtdInfo == 2 || Raiz->qtdInfo > 2)
//             printf("%d ", Raiz->info2);
//         if(Raiz->qtdInfo == 3 || Raiz->qtdInfo > 3)
//             printf("%d ", Raiz->info3);
//         if(Raiz->qtdInfo == 4)
//             printf("%d ", Raiz->info4);
//         printf("Quantidade de Info: %d\n", Raiz->qtdInfo);

//         mostrar(Raiz->esq);
//         mostrar(Raiz->centro_esq);
//         mostrar(Raiz->centro);
//         mostrar(Raiz->centro_dir);
//         mostrar(Raiz->dir);
//     }
// }

void exibirInfo(Info *info){
    printf("cod: %d, tam: %d, qtd: %d, linha: %d, tipo: %s, marca: %s, preco: %.2f\n", info->cod, info->tam, info->qtd, info->linha, info->tipo, info->marca, info->preco);
}

void mostrar(Arv45* raiz, int nivel) {
    if (raiz != NULL) {
        // mostrar(raiz->centro_dir, nivel + 1);

        for (int i = 0; i < nivel; i++)
            printf("   ");

        // printf("%d ", raiz->info1->cod);
        exibirInfo(raiz->info1);
        if (raiz->qtdInfo == 2 || raiz->qtdInfo > 2)
            exibirInfo(raiz->info2);
        if (raiz->qtdInfo == 3 || raiz->qtdInfo > 3)
            exibirInfo(raiz->info3);
        if (raiz->qtdInfo == 4)
            exibirInfo(raiz->info4);
        printf("Quantidade de Info: %d\n", raiz->qtdInfo);

        mostrar(raiz->esq, nivel + 1);
        mostrar(raiz->centro_esq, nivel + 1);
        mostrar(raiz->centro, nivel + 1);
        mostrar(raiz->centro_dir, nivel + 1); // Impresso acima para melhor visualização
        mostrar(raiz->dir, nivel + 1);
    }
}

int main(){
    Arv45 *raiz = NULL;
    Info *sobe; 
    lerArquivo(&raiz, &sobe);
    // insere23(&Raiz, 400, NULL, &sobe);
    // insere23(&Raiz, 721, NULL, &sobe);
    // insere23(&Raiz, 670, NULL, &sobe);
    // insere23(&Raiz, 570, NULL, &sobe);
    // insere23(&Raiz, 922, NULL, &sobe);
    // insere23(&Raiz, 130, NULL, &sobe);
    // insere23(&Raiz, 345, NULL, &sobe);
    // insere23(&Raiz, 797, NULL, &sobe);
    // insere23(&Raiz, 385, NULL, &sobe);
    // insere23(&Raiz, 874, NULL, &sobe);
    // insere23(&Raiz, 405, NULL, &sobe);
    // insere23(&Raiz, 652, NULL, &sobe);
    // insere23(&Raiz, 491, NULL, &sobe);
    // insere23(&Raiz, 830, NULL, &sobe);
    // insere23(&Raiz, 443, NULL, &sobe);
    // insere23(&Raiz, 105, NULL, &sobe);
    // insere23(&Raiz, 285, NULL, &sobe);
    // insere23(&Raiz, 126, NULL, &sobe);
    // insere23(&Raiz, 556, NULL, &sobe);
    // insere23(&Raiz, 795, NULL, &sobe);
    // insere23(&Raiz, 899, NULL, &sobe);
    
    // insere23(&Raiz, 502, NULL, &sobe);
    // insere23(&Raiz, 866, NULL, &sobe);
    // insere23(&Raiz, 725, NULL, &sobe);
    // insere23(&Raiz, 581, NULL, &sobe);
    // insere23(&Raiz, 408, NULL, &sobe);
    // insere23(&Raiz, 348, NULL, &sobe);
    // insere23(&Raiz, 575, NULL, &sobe);
    // insere23(&Raiz, 719, NULL, &sobe);
    // insere23(&Raiz, 983, NULL, &sobe);
    // insere23(&Raiz, 63, NULL, &sobe);

    // insere23(&Raiz, 10, NULL, &sobe);
    // insere23(&Raiz, 11, NULL, &sobe);
    // insere23(&Raiz, 1, NULL, &sobe);
    // insere23(&Raiz, 2, NULL, &sobe);
    // insere23(&Raiz, 3, NULL, &sobe);
    // insere23(&Raiz, 4, NULL, &sobe);
    // insere23(&Raiz, 5, NULL, &sobe);
    // insere23(&Raiz, 6, NULL, &sobe);
    // insere23(&Raiz, 7, NULL, &sobe);
    // insere23(&Raiz, 8, NULL, &sobe);
    // insere23(&Raiz, 9, NULL, &sobe);
    // insere23(&Raiz, 10, NULL, &sobe);
    // insere23(&Raiz, 11, NULL, &sobe);
    // insere23(&Raiz, 900, NULL, &sobe);
    // insere23(&Raiz, 1000,NULL, &sobe);
    // insere23(&Raiz, 600, NULL, &sobe);
    // insere23(&Raiz, 1300,NULL, &sobe);
    // insere23(&Raiz, 1500,NULL, &sobe);
    // insere23(&Raiz, 1200,NULL, &sobe);
    // insere23(&Raiz, 800, NULL, &sobe);
    // insere23(&Raiz, 1100,NULL, &sobe);
    // insere23(&Raiz, 1700,NULL, &sobe);
    // insere23(&Raiz, 350, NULL, &sobe);
    // insere23(&Raiz, 450, NULL, &sobe);
    // insere23(&Raiz, 150, NULL, &sobe);
    // insere23(&Raiz, 50, NULL,  &sobe);
    // insere23(&Raiz, 470, NULL, &sobe);
    // insere23(&Raiz, 490, NULL, &sobe);

    mostrar(raiz, 0);

    return 0;    
}