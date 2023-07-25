#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arv23.h"

void lerArquivo(char *path, Arv23 **raiz, int inseriu[]){
    FILE *arquivo;
    arquivo = fopen(path, "r");
    Info *aux;
    aux = NULL;

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.");
    }

    char frase[5000], *palavra;

    int linha = 1;

    while(fgets(frase, sizeof(frase), arquivo) != NULL){
        palavra = strtok(frase, " ");

        while (palavra != NULL){
            palavra[strcspn(palavra, "\n")] = '\0'; // strcspn(palavra, "\n") encontra a primeira posição de \n. e substtui por \0
            palavra[strcspn(palavra, ".")] = '\0';
            // Arv23 *inserePalavra(Arv23 **raiz, char *palavra, int linha, Arv23 *pai, Info **infoSobe)
            // printf("%s\n",palavra);
            auxiliaInsere(raiz, palavra, linha, NULL, &aux);
            // printf("Vez %d\n", linha);
            // imprimirArv(*raiz);
            palavra = strtok(NULL, " ");
        }
        printf("%d\n", linha);
        linha += 1;
    }

}

// cria nó deve receber a palavra, ponteiro para lista, se esse ponteiro for nulo, deve-se criar a lista, pelo parametro linha, caso o ponteiro 
// não seja nulo é setado o na info
Info *criaInfo(char *palavra, Linhas *lista, int linha){
    /*
    A função criaInfo aloca memória para uma estrutura Info, preenche os campos palavra
    e ListaNum com os valores fornecidos e retorna a estrutura Info criada.   
    
    Parâmetros:
        palavra: A palavra a ser armazenada na estrutura.
        lista: A lista de linhas a ser armazenada na estrutura.
        linha: A linha da palavra a ser armazenada na estrutura.
    
    Retorno: 
        Um ponteiro para a estrutura `Info` criada.
    */

    Info *info;
    info = (Info*) malloc(sizeof(Info)); // Aloca memória para a estrutura `Info`.

    info->palavra = (char*) malloc((strlen(palavra) + 1) * sizeof(char)); // Aloca memória para a string `palavra`.
    strcpy(info->palavra, palavra);

    if(lista == NULL){
        info->ListaNum = NULL;
        inserirLinha(&(info->ListaNum), linha);
    }else{
        info->ListaNum = lista;
    }
    return info;
}

// verificar se lista que vem de fora é NULL se for cria se não adiciona


Arv23 *criaNo(Info *info, Arv23 *noEsq, Arv23 *noCentro) {
    /*  
    
    A função criaNO aloca memória para um novo nó da árvore 2-3 e preenche seus campos
    com os valores fornecidos. O número de informações contidas no nó é inicializado como 1,
    e os ponteiros para os nós filho são definidos conforme especificado.

    Parâmetros:
        info: A informação a ser armazenada no nó.
        noEsq: O nó da subárvore esquerda.
        noCentro: O nó da subárvore central.

    Retorno: 
        Um ponteiro para o nó criado.
    */

   // Aloca memória para o nó.
    Arv23 *no = (Arv23*) malloc(sizeof(Arv23)); 

    // Armazena a informação no nó.
    no->info1 = info; 
    
    // Define o número de informações como 1.
    no->numInfo = 1;

    // Define os ponteiros para os nós das subárvores.
    no->esq = noEsq;
    no->centro = noCentro;
    no->dir = NULL;

    // Retorna o nó criado.
    return no;
}

void adicionaNo(Arv23 **raiz, Info *info, Arv23 *filho) {
    /*  
    A função adicionaNo adiciona um novo nó à árvore 2-3. O parâmetro raiz é um ponteiro
    para o ponteiro da raiz da árvore. O parâmetro info é um ponteiro para a estrutura Info
    a ser adicionada ao nó. O parâmetro Novo é um ponteiro para o novo nó que será adicionado.
 
    Se a palavra em info for maior que a palavra no primeiro nó da raiz, o campo info2 e dir da
    raiz são atualizados com os valores fornecidos. Caso contrário, o campo info2 é atualizado
    com o valor do campo info1 da raiz, e o campo info1 da raiz é atualizado com o valor de info.
    Os campos dir e centro da raiz são atualizados com os valores de Novo e do campo centro da raiz,
    respectivamente.

    Parâmetros:
        raiz: Um ponteiro para a raiz da árvore.
        info: A informação a ser adicionada à árvore.
        Novo: O novo nó a ser adicionado à árvore.
    
    Retorno: 
        Não possui retorno, mas o ponteiro de informações na raiz da árvore é alterada/adicionado.
    */

    if(strcmp(info->palavra, (*raiz)->info1->palavra) > 0){
        (*raiz)->info2 = info;
        (*raiz)->dir = filho;
    }else{
        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->info1 = info; 

        (*raiz)->dir = (*raiz)->centro;
        (*raiz)->centro = filho;
    }
    (*raiz)->numInfo = 2;
}

void inserirLinha(Linhas **no, int linha){
    if(*no == NULL){
        *no = (Linhas*) malloc(sizeof(Linhas));

        if(*no != NULL){
            (*no)->linha = linha;
            (*no)->prox = NULL;
        }
    }else
        inserirLinha(&((*no)->prox), linha);
}

Arv23 *quebraNo(Arv23 **raiz, Arv23 *filho, Info *info, Info **infoSobe) {
    Arv23 *maiorNo;
    maiorNo = NULL;

    if (strcmp(info->palavra, (*raiz)->info2->palavra) > 0) {
        *infoSobe = (*raiz)->info2;
        maiorNo = criaNo(info, (*raiz)->dir, filho);
    } 
    
    else if (strcmp(info->palavra, (*raiz)->info1->palavra) < 0) {
        *infoSobe = (*raiz)->info1;
        maiorNo = criaNo((*raiz)->info2, (*raiz)->centro, (*raiz)->dir);
        
        (*raiz)->info1 = info;
        (*raiz)->centro = filho;
    }

    else {
        *infoSobe = info;
        maiorNo = criaNo((*raiz)->info2, filho, (*raiz)->dir);  
    }

    (*raiz)->numInfo = 1;
    (*raiz)->info2 = NULL;
    // strcpy((*raiz)->info2->palavra, "Chega");
    (*raiz)->dir = NULL; 

    return maiorNo;
}

int folha(Arv23 *raiz){
    int flag = 0;

    if(raiz->esq == NULL)
        flag = 1;
    
    return flag;
}

Arv23 *inserePalavra(Arv23 **raiz, char *palavra, int linha, Arv23 *pai, Info **infoSobe){
    Arv23 *maiorNo;

    if(*raiz == NULL){ 
        *raiz = criaNo(criaInfo(palavra, NULL, linha), NULL, NULL);
    }else{

        if(folha(*raiz)){
            if((*raiz)->numInfo == 1){
                adicionaNo(raiz, criaInfo(palavra, NULL, linha), NULL);
                maiorNo = NULL;
            }else{
                maiorNo = quebraNo(raiz, NULL, criaInfo(palavra, NULL, linha), infoSobe);

                if(pai == NULL){
                    *raiz = criaNo(*infoSobe, *raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        }else{
            
            if(strcmp(palavra, (*raiz)->info1->palavra) < 0)   
                maiorNo = inserePalavra(&((*raiz)->esq), palavra, linha, *raiz, infoSobe);
            
            else if(((*raiz)->numInfo == 1) || ((*raiz)->numInfo == 2 && strcmp(palavra, (*raiz)->info2->palavra) < 0))
                maiorNo = inserePalavra(&((*raiz)->centro), palavra, linha, *raiz, infoSobe);
            
            else
                maiorNo = inserePalavra(&((*raiz)->dir), palavra, linha, *raiz, infoSobe);   

            if(maiorNo != NULL){
                if((*raiz)->numInfo == 1){
                    adicionaNo(raiz, *infoSobe, maiorNo);
                    maiorNo = NULL;
                }else{
                    maiorNo = quebraNo(raiz, maiorNo, *infoSobe, infoSobe);
                    if(pai == NULL){
                        *raiz = criaNo(*infoSobe, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}

void auxiliaInsere(Arv23 **raiz, char *palavra, int linha, Arv23 *pai, Info **infoSobe){
    Info *aux;
    aux = NULL;
    buscaPalavra(*raiz, palavra, &aux);

    if(aux == NULL){
        inserePalavra(raiz, palavra, linha, NULL, infoSobe);
    }else{
        inserirLinha(&(aux->ListaNum), linha);
    }
}

// imprimir
void imprimirLista(Linhas *no){
    if(no != NULL){
        printf("%d ", no->linha);
        imprimirLista(no->prox);
    }
}

void imprimirInfo(Info *info){
    if(info != NULL){
        printf("%s, linhas: ", info->palavra);
        imprimirLista(info->ListaNum);
        printf("\n");
    }
}

void imprimirArv(Arv23 *raiz){
    if(raiz != NULL){
        printf("\nInfo 1:\n");
        imprimirInfo(raiz->info1);
        if(raiz->numInfo == 2){
            printf("Info 2:\n");
            imprimirInfo(raiz->info2);
        }
        imprimirArv(raiz->esq);
        imprimirArv(raiz->centro);
        imprimirArv(raiz->dir);
    }
}

// busca

Info *buscaPalavra(Arv23 *raiz, char *palavra, Info **aux){
    // Info *aux;
    // aux = NULL;

    if(raiz != NULL){
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
    // if(raiz != NULL){
    //     if(strcmp(palavra, raiz->info1->palavra) == 0)
    //         return raiz->info1;
    //     if(raiz->numInfo == 2){
    //         if(strcmp(palavra, raiz->info2->palavra) == 0)
    //             return raiz->info2;
    //     }
    //     imprimirArv(raiz->esq);
    //     imprimirArv(raiz->centro);
    //     imprimirArv(raiz->dir);
    // }
    // return aux;
}

// Remover

void MaiorInfoRemoveEsq(Arv23 **raiz, Arv23** PaiMaior, Arv23** MaiorInfoRemove, int LocalInfo) {
    if (MaiorInfoRemove != NULL) {
        if ((*MaiorInfoRemove)->esq == NULL) {
            char *aux;
            // aux = NULL;
            aux = (char *) malloc(sizeof(char) * 50);
            strcpy(aux, "NOT FOUND");

            if (LocalInfo == 1) {
                strcpy(aux, (*raiz)->info1->palavra);

                if ((*MaiorInfoRemove)->numInfo == 2) {
                    strcpy((*raiz)->info1->palavra, (*MaiorInfoRemove)->info2->palavra);
                    strcpy((*MaiorInfoRemove)->info2->palavra, aux);
                }
                else {
                    strcpy((*raiz)->info1->palavra, (*MaiorInfoRemove)->info1->palavra);
                    strcpy((*MaiorInfoRemove)->info1->palavra, aux);
                }

            }
            else if (LocalInfo == 2) {
                strcpy(aux, (*raiz)->info2->palavra);

                if ((*MaiorInfoRemove)->numInfo == 2) {
                    strcpy((*raiz)->info2->palavra, (*MaiorInfoRemove)->info2->palavra);
                    strcpy((*MaiorInfoRemove)->info2->palavra, aux);
                }
                else {
                    strcpy((*raiz)->info2->palavra, (*MaiorInfoRemove)->info1->palavra);
                    strcpy((*MaiorInfoRemove)->info1->palavra, aux);
                }

            }

            remover23(PaiMaior, MaiorInfoRemove, aux);
        }
        else {
            if ((*MaiorInfoRemove)->numInfo == 2) {
                MaiorInfoRemoveEsq(raiz, MaiorInfoRemove, &((*MaiorInfoRemove)->dir), LocalInfo);
            }
            else if ((*MaiorInfoRemove)->numInfo == 1) {
                MaiorInfoRemoveEsq(raiz, MaiorInfoRemove, &((*MaiorInfoRemove)->centro), LocalInfo);
            }
        } 
    }
    Redistribui(MaiorInfoRemove, PaiMaior);
}

void Redistribui(Arv23 **raiz, Arv23 **pai) {
    if (*raiz != NULL)
        if ((*raiz)->numInfo == 0) {
            if (pai != NULL) {
                if ((*raiz) == ((*pai)->dir)) {
                    if ((*pai)->centro->numInfo == 2) {
                        (*raiz)->info1 = (*pai)->info2;
                        (*raiz)->numInfo = 1;
                        (*pai)->info2 = (*pai)->centro->info2;
                        (*pai)->centro->numInfo = 1;
                        (*raiz)->esq = (*pai)->centro->dir;
                        (*pai)->centro->dir = NULL;
                    }
                    else if ((*pai)->centro->numInfo == 1) {
                        (*raiz)->info2 = (*pai)->info2;
                        (*raiz)->dir = (*raiz)->centro;
                        (*raiz)->info1 = (*pai)->centro->info1;
                        (*raiz)->numInfo = 2;
                        (*pai)->numInfo = 1;
                        (*raiz)->centro = (*pai)->centro->centro;
                        (*raiz)->esq = (*pai)->centro->esq;
                        free((*pai)->centro);
                        (*pai)->centro = (*raiz);
                        (*pai)->dir = NULL;
                    }
                }
                else if ((*raiz) == (*pai)->centro) {
                    if ((*pai)->esq->numInfo == 2) {
                        (*raiz)->info1 = (*pai)->info1;
                        (*raiz)->numInfo = 1;
                        (*pai)->info1 = (*pai)->esq->info2;
                        (*pai)->esq->numInfo = 1;
                        (*raiz)->esq = (*pai)->esq->dir;
                        (*pai)->esq->dir = NULL;
                    }
                    else if ((*pai)->esq->numInfo == 1) {
                        if ((*pai)->numInfo == 2) {
                            (*raiz)->info2 = (*pai)->info1;
                            (*raiz)->info1 = (*pai)->esq->info1;
                            (*raiz)->numInfo = 2;
                            (*raiz)->dir = (*raiz)->centro;
                            (*raiz)->centro = (*pai)->esq->centro;
                            (*raiz)->esq = (*pai)->esq->esq;
                            free((*pai)->esq);
                            (*pai)->esq = (*raiz);
                            (*pai)->info1 = (*pai)->info2;
                            (*pai)->numInfo = 1;
                            (*pai)->centro = (*pai)->dir;
                            (*pai)->dir = NULL;
                        }
                        else if ((*pai)->numInfo == 1) {
                            (*raiz)->info2 = (*pai)->info1;
                            (*raiz)->info1 = (*pai)->esq->info1;
                            (*raiz)->numInfo = 2;
                            (*pai)->numInfo = 0;
                            (*raiz)->dir = (*raiz)->centro;
                            (*raiz)->centro = (*pai)->esq->centro;
                            (*raiz)->esq = (*pai)->esq->esq;
                            free((*pai)->esq);
                            (*pai)->esq = NULL;
                        }
                    }
                }
                else if ((*raiz) == (*pai)->esq) {
                    if ((*pai)->centro->numInfo == 2) {
                        (*raiz)->info1 = (*pai)->info1;
                        (*raiz)->numInfo = 1;
                        (*pai)->info1 = (*pai)->centro->info1;
                        (*pai)->centro->numInfo = 1;
                        (*pai)->centro->info1 = (*pai)->centro->info2;
                        (*raiz)->esq = (*raiz)->centro;
                        (*raiz)->centro = (*pai)->centro->esq;
                        (*pai)->centro->esq = (*pai)->centro->centro;
                        (*pai)->centro->centro = (*pai)->centro->dir;
                        (*pai)->centro->dir = NULL;
                    }
                    else if ((*pai)->centro->numInfo == 1) {
                        if ((*pai)->numInfo == 2) {
                            (*raiz)->info1 = (*pai)->info1;
                            (*raiz)->info2 = (*pai)->centro->info1;
                            (*raiz)->numInfo = 2;
                            (*raiz)->esq = (*raiz)->centro;
                            (*raiz)->centro = (*pai)->centro->esq;
                            (*raiz)->dir = (*pai)->centro->centro;
                            (*pai)->info1 = (*pai)->info2;
                            (*pai)->numInfo = 1;
                            free((*pai)->centro);
                            (*pai)->centro = (*pai)->dir;
                            (*pai)->dir = NULL;
                        }
                        else if ((*pai)->numInfo == 1) {
                            (*raiz)->info1 = (*pai)->info1;
                            (*raiz)->esq = (*raiz)->centro;
                            (*raiz)->info2 = (*pai)->centro->info1;
                            (*raiz)->centro = (*pai)->centro->esq;
                            (*raiz)->dir = (*pai)->centro->centro;
                            (*pai)->numInfo = 0;
                            (*raiz)->numInfo = 2;
                            free((*pai)->centro);
                            (*pai)->centro = (*raiz);
                            (*pai)->esq = NULL;
                        }
                    }
                }
            }
            else if (pai == NULL) {
                (*raiz) = (*raiz)->centro;
            }
            // else if (folha(*raiz) == 0 && pai == NULL){
            //     free(*raiz);
            //     *raiz = NULL;
            // }    
        }
}

void remover23(Arv23 **pai, Arv23 **raiz, char *palavra){
	if (*raiz != NULL) {
        if(strcmp(palavra, (*raiz)->info1->palavra) == 0){
            if(folha(*raiz)) {
                if((*raiz)->numInfo == 2) {
                    (*raiz)->info1 = (*raiz)->info2;
                    (*raiz)->numInfo = 1;

                    // free((*raiz)->info2->palavra);
                }
                else if((*raiz)->numInfo == 1){
                    (*raiz)->numInfo = 0;
                }
            }
            else {
                Arv23 **MaiorInfoRemove = &((*raiz)->esq);
                Arv23 **PaiMaior = raiz;
                MaiorInfoRemoveEsq(raiz, PaiMaior, MaiorInfoRemove, 1);
            }
        }
        else if ((*raiz)->numInfo == 2 && strcmp(palavra, (*raiz)->info2->palavra) == 0) {
            if (folha(*raiz)) {
                (*raiz)->numInfo = 1;
            }
            else {
                Arv23 **MaiorInfoRemove = &((*raiz)->centro);
                Arv23 **PaiMaior = raiz;
                MaiorInfoRemoveEsq(raiz, PaiMaior, MaiorInfoRemove, 2);
            }
        }
        
		else if (strcmp(palavra, (*raiz)->info1->palavra) < 0) {
            remover23(raiz, &((*raiz)->esq), palavra);
        }
        else if ((*raiz)->numInfo == 1 || (*raiz)->numInfo == 2 && strcmp(palavra, (*raiz)->info2->palavra) < 0) {
            remover23(raiz, &((*raiz)->centro), palavra);
        }
        else {
            remover23(raiz, &((*raiz)->dir), palavra);
        }
    }
    Redistribui(raiz, pai);
}
