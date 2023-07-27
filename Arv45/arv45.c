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

Arv45 *insere45(Arv45 **raiz, Arv45 *pai, Info **sobe, int cod, int tam, int qtd, int linha, char *tipo, char *marca, float preco, int *flag);

void lerArquivo(Arv45 **raiz, Info **sobe){
    FILE *arquivo;
    int cod, tam, qtd, linha, flag = 0;
    char tipo[100], marca[100];
    float preco;

    // Abrir o arquivo para leitura
    arquivo = fopen("loja.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }else{

        linha = 1;

        // Ler cada linha do arquivo até o final
        while (fscanf(arquivo, "%d %d %d %s %s %f\n", &cod, &tam, &qtd, tipo, marca, &preco) == 6) {
            insere45(raiz, NULL, sobe, cod, tam, qtd, linha, tipo, marca, preco, &flag);

            if(flag == 0) 
                printf("Esse codigo nao foi inserido: %d\n", cod);
            flag = 0;
            linha++;
        }

        fclose(arquivo);

    }
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

    (*raiz)->info3 = NULL;
    (*raiz)->info4 = NULL;

    return maiorNo;
    
}

Arv45 *insere45(Arv45 **raiz, Arv45 *pai, Info **sobe, int cod, int tam, int qtd, int linha, char *tipo, char *marca, float preco, int *flag){
    Arv45 *maiorNO;
    maiorNO = NULL;

    if(*raiz == NULL){
        *raiz = criaNo(criaInfo(cod, tam, qtd, linha, tipo, marca, preco), NULL, NULL);
        *flag = 1; // informa que a foi inserido
    }else{
        if(folha(*raiz)){
            *flag = 1; // informa que a foi inserido
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
                maiorNO = insere45(&((*raiz)->esq), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);

            else if((*raiz)->qtdInfo == 1 || ((*raiz)->qtdInfo <= 4 && cod < (*raiz)->info2->cod))
                maiorNO = insere45(&((*raiz)->centro_esq), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);

            else if(((*raiz)->qtdInfo == 2)  || ((*raiz)->qtdInfo <= 4 && cod < (*raiz)->info3->cod))
                maiorNO = insere45(&((*raiz)->centro), *raiz,  sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);

            else if(((*raiz)->qtdInfo == 3) || ((*raiz)->qtdInfo == 4 && cod < (*raiz)->info4->cod))
                maiorNO = insere45(&((*raiz)->centro_dir), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);

            else 
                maiorNO = insere45(&((*raiz)->dir), *raiz, sobe, cod, tam, qtd, linha, tipo, marca, preco, flag);

            if(maiorNO){
                if((*raiz)->qtdInfo < 4){
                    adicionaNo(raiz, *sobe, maiorNO);
                    maiorNO = NULL;
                }else{
                    // maiorNO = quebraNo(raiz, criaInfo(cod, tam, qtd, linha, tipo, marca, preco), sobe, maiorNO);
                    maiorNO = quebraNo(raiz, *sobe, sobe, maiorNO);

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

void exibirInfo(Info *info){
        printf("cod: %d, tam: %d, qtd: %d, linha: %d, tipo: %s, marca: %s, preco: %.2f\n", info->cod, info->tam, info->qtd, info->linha, info->tipo, info->marca, info->preco);
}

void mostrar(Arv45* raiz, int nivel) {
    if (raiz != NULL) {

        for (int i = 0; i < nivel; i++)
            printf("   ");

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
        mostrar(raiz->centro_dir, nivel + 1); 
        mostrar(raiz->dir, nivel + 1);
    }
}

// void mostrar(Arv45* Raiz, int nivel) {
//     if (Raiz != NULL) {
//         // Imprimir os valores do nível atual
//         for (int i = 0; i < nivel; i++) {
//             printf("\t");
//         }

//         printf("Nivel %d: ", nivel);
        
//         // Imprimir os valores de acordo com o número de informações presentes no nó
//         printf("%d ", Raiz->info1->cod);
//         if (Raiz->qtdInfo == 2) {
//             printf("%d ", Raiz->info2->cod);
//         }
//         if (Raiz->qtdInfo == 3) {
//             printf("%d ", Raiz->info2->cod);
//             printf("%d ", Raiz->info3->cod);
//         }
//         if (Raiz->qtdInfo == 4) {
//             printf("%d ", Raiz->info2->cod);
//             printf("%d ", Raiz->info3->cod);
//             printf("%d ", Raiz->info4->cod);
//         }

//         printf("qtdInfo %d\n", Raiz->qtdInfo);

//         // Recursivamente imprimir os filhos
//         mostrar(Raiz->esq, nivel + 1);
//         mostrar(Raiz->centro_esq, nivel + 1);
//         mostrar(Raiz->centro, nivel + 1);
//         mostrar(Raiz->centro_dir, nivel + 1);
//         mostrar(Raiz->dir, nivel + 1);
//     }
// }

Info *buscarProduto(Arv45 *raiz, int cod){
    Info *achou = NULL;

    if(raiz){
        if(cod == raiz->info1->cod)
            achou = raiz->info1;

        else if(raiz->qtdInfo == 2){
            if(cod == raiz->info2->cod)
                achou = raiz->info2;

        }else if(raiz->qtdInfo == 3){
            if(cod == raiz->info3->cod)
                achou = raiz->info3;

        }else if(raiz->qtdInfo == 4){
            if(cod == raiz->info4->cod)
                achou = raiz->info4;

        }else{
            if(cod < raiz->info1->cod)
                achou = buscarProduto(raiz->esq, cod);

            else if(raiz->qtdInfo == 1 || (raiz->qtdInfo <= 4 && cod < raiz->info2->cod))
                achou = buscarProduto(raiz->centro_esq, cod);

            else if((raiz->qtdInfo == 2)  || (raiz->qtdInfo <= 4 && cod < raiz->info3->cod))
                achou = buscarProduto(raiz->centro, cod);

            else if((raiz->qtdInfo == 3) || (raiz->qtdInfo == 4 && cod < raiz->info4->cod))
                achou = buscarProduto(raiz->centro_dir, cod);

            else 
                achou = buscarProduto(raiz->dir, cod);
        }
    }
    return achou;
}

void atualizarArquivo(Info *no){
    char nomeArquivo[] = "loja.txt";
    FILE *arquivo;
    int linhaAtual = 1;
    char linha[100];

    arquivo = fopen(nomeArquivo, "r+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }else{
        int flag = 1;
        // Percorre o arquivo até a linha desejada
        while (linhaAtual < no->linha) {
            if (fgets(linha, sizeof(linha), arquivo) == NULL) {
                printf("Linha alvo fora do alcance do arquivo.\n");
                fclose(arquivo);
                flag = 0;
            }
            linhaAtual++;
        }
     
        if(flag){
            fseek(arquivo, -1, SEEK_CUR); // Volta 1 caractere para sobrescrever a quebra de linha
            // codigo, tamanho, quantidade, tipo, marca, preco.
            fprintf(arquivo, "\n%d %d %d %s %s %.2f", no->cod, no->tam, no->qtd, no->tipo, no->marca, no->preco);

            fclose(arquivo);
        }
    }
}

void vender(Arv45 *raiz){
    mostrar(raiz, 0);
    int cod, qtd, opcompra;
    Info *aux;

    printf("Escolha o produto pelo código: ");
    scanf("%d", &cod);
    // digitou o codigo certo?

    aux = buscarProduto(raiz, cod);

    if(aux != NULL){
        printf("Deseja comprar quantos calcados: ");
        scanf("%d", &qtd);

        if(qtd > aux->qtd && aux->qtd != 0){
            printf("Estao disponiveis somente %d calcados. Deseja compra-los? 1 - sim / 2 - nao:  ", aux->qtd);
            scanf("%d", &opcompra);
            
            if(opcompra == 1){
                printf("Segundo if\n");
                printf("O valor total eh: %.2f,  Deseja continua? 1 - sim / 2 - nao: ", aux->preco * aux->qtd);
                scanf("%d", &opcompra);
                
                if(opcompra == 1){
                    aux->qtd = 0;
                    atualizarArquivo(aux);
                    printf("Compra realizada com sucesso.\n");
                }else if(opcompra == 2)
                    printf("Compra nao efetuada.\n");
                else
                    printf("Codigo nao reconhecido refaca as operacoes.\n");

            }else if(opcompra == 2)
                printf("Compra nao efetuada.\n");
            else
                printf("Codigo nao reconhecido refaca as operacoes.\n");
        
        }
        else if(qtd != 0 && aux->qtd != 0){

            printf("O valor total eh: %.2f,  Deseja continua? 1 - sim / 2 - nao: ", aux->preco * qtd);
            scanf("%d", &opcompra);
            
            if(opcompra == 1){
                aux->qtd -= qtd;
                atualizarArquivo(aux);
                printf("Compra realizada com sucesso.\n");
            }
            else if(opcompra == 2)
                printf("Compra nao efetuada.\n");
            else
                printf("Codigo nao reconhecido refaca as operacoes.\n");
        }
        else{
            if(qtd == 0)
                printf("vc digitou 0, ou seja, nao eh possivel comprar\n");
            else
                printf("Nao eh possivel comprar pois o produto nao estar disponivel\n");
        }

    }else
        printf("Produto nao encontrado.\n");
}

void reporProduto(Arv45 *raiz){
    mostrar(raiz, 0);
    int cod, qtd, opcompra;
    Info *aux;

    printf("Escolha o produto pelo código: ");
    scanf("%d", &cod);
    // digitou o codigo certo?

    aux = buscarProduto(raiz, cod);

    if(aux != NULL){
        printf("Qual a quantidade de produto: ");
        scanf("%d", &qtd);

        if(qtd > 0){
           aux->qtd += qtd;
            atualizarArquivo(aux);
        }else
            printf("Quantidade de produto inferior ou igual a zero.\n");
        
    }else
        printf("Produto nao encontrado.\n");
}

int quantidadeLinhas(){
    FILE *arquivo;

    arquivo = fopen("loja.txt", "r");
    
    char tipo[100], marca[100], linha[250];
    int qtdLinha = 1;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            ++qtdLinha;
    }
    return qtdLinha;
}

void adicionarCalcados(Arv45 **raiz, Info **sobe){
    FILE *arquivo;

    arquivo = fopen("loja.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }else{
        int cod, tam, qtd, flag = 0, qtdLinha = 1;
        char tipo[100], marca[100], linha[250];
        float preco;

        printf("Digite o codigo do produto: ");
        scanf("%d", &cod);
        printf("Digite o tamanho do produto: ");
        scanf("%d", &tam);
        printf("Digite a quantida do produto: ");
        scanf("%d", &qtd);
        printf("Digite o tipo do produto: ");
        scanf("%s", tipo);
        printf("Digite o a marca do produto: ");
        scanf("%s", marca);
        printf("Digite o preco do produto: ");
        scanf("%f", &preco);

        
        qtdLinha = quantidadeLinhas();


        insere45(raiz, NULL, sobe, cod, tam, qtd, qtdLinha, tipo, marca, preco, &flag);

        if(flag == 1)
            fprintf(arquivo, "\n%d %d %d %s %s %.2f", cod, tam, qtd, tipo, marca, preco);
        
        fclose(arquivo);
    }

}

int main(){
    Arv45 *raiz = NULL;
    Info *sobe; 

    lerArquivo(&raiz, &sobe);
    mostrar(raiz, 0);
    // atualizarArquivo();
    // vender(raiz);
    // reporProduto(raiz);
    // adicionarCalcados(&raiz, &sobe);

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

    // mostrar(raiz, 0);

    return 0;    
}