#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arv23.h"

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

    info->palavra = (char*) malloc(sizeof(char) * (strlen(palavra) + 1)); // Aloca memória para a string `palavra`.
    strcmp(info->palavra, palavra);

    if(lista == NULL){
        info->ListaNum = NULL;
        inserirLinha(info->ListaNum, linha);
    }else{
        info->ListaNum = lista;
    }
    return info;
}

// verificar se lista que vem de fora é NULL se for cria se não adiciona

Arv23 *criaNO(Info *info, Arv23 *noEsq, Arv23 *noCentro) {
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

void adicionaNo(Arv23 **raiz, Info *info, Arv23 *Novo) {
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
        (*raiz)->dir = Novo;
    }else{
        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->info1 = info; 

        (*raiz)->dir = (*raiz)->centro;
        (*raiz)->centro = Novo;
    }
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



Arv23 *inserePalavra(Arv23 **raiz, char *palavra, int linha, Arv23 *pai, char *sobe, Linhas **listaSobe, Info **infoSobe){
    Arv23 *maiorNo;
    Linhas *auxLista;
    auxLista = NULL;

    if(*raiz == NULL){ 
        *raiz = criaNo(criaInfo(palavra, NULL, linha), NULL, NULL);
    }else{
        if(folha(*raiz)){
            if((*raiz)->numInfo == 1){
                adicionaNo(raiz, criaInfo(palavra, NULL, linha), NULL);
                maiorNo = NULL;
            }else{
                maiorNo = quebraNo(raiz, palavra, sobe, listaSobe, NULL);

                if(pai == NULL){
                    *raiz = criaNo(sobe, *raiz, maiorNo);
                    inserirLinha(&((*raiz)->info1->ListaNum), linha);
                    maiorNo = NULL;
                }
            }
        }else{
            // if(strcmp(palavra, (*raiz)->info1->palavra) == 0)
            //     adicionarLinha();
            
            // else if(strcmp(palavra, (*raiz)->info1->palavra) < 0)   
            //     maiorNo = inserePalavra(&((*raiz)->esq), palavra, linha, *raiz, *sobe, listaSobe);
            
            // else if(((*raiz)->numInfo == 1) || ((*raiz)->numInfo == 2 && strcmp(palavra, (*raiz)->info2->palavra) < 0))
            //     maiorNo = inserePalavra(&((*raiz)->centro), palavra, linha, *raiz, *sobe, listaSobe);
           
            // else if(strcmp(palavra, (*raiz)->info2->palavra) == 0)
            //     adicionarLinha();
            
            // else
            //     maiorNo = inserePalavra(&((*raiz)->dir), palavra, linha, *raiz, *sobe, listaSobe);   

            if(maiorNo != NULL){
                if((*raiz)->numInfo == 1){
                    // adicionaNo();
                    maiorNo = NULL;
                }else{
                    maiorNo = quebraNo();
                    
                    if(pai == NULL){
                        criaNo(sobe, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}