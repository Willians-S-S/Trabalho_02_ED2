#include <stdio.h>
#include <stdlib.h>

typedef struct Arv23 Arv23;

struct Arv23{
    int info_1, info_2, info_3, info_4, qtdInfo;

    Arv23 *esq, *centro_esq, *centro, *centro_dir, *dir;
};

Arv23 *criaNo(int info, Arv23 * No_esq, Arv23 * No_centro_esq){
    Arv23 *No;
    No = (Arv23 *) malloc(sizeof(Arv23));

    No->info_1 = info;
    No->qtdInfo = 1;
    No->esq = No_esq;
    No->centro_esq = No_centro_esq;
    No->centro = NULL;
    No->centro_dir = NULL;
    No->dir = NULL;

    return No;
}

int folha(Arv23 *No){
    int eh = 0;
    if(No->esq == NULL)
        eh = 1;
    return eh;
}

void adicionaNo(Arv23 **No, int info, Arv23 *filho){

    if((*No)->qtdInfo == 1){
        if(info > (*No)->info_1){
            (*No)->info_2 = info;
            (*No)->centro = filho;

        }else{
            (*No)->info_2 = (*No)->info_1;
            (*No)->info_1 = info;

            (*No)->centro = (*No)->centro_esq;
            (*No)->centro_esq = filho;

        }
        (*No)->qtdInfo = 2;

    }else if((*No)->qtdInfo == 2){

        if(info > (*No)->info_2){
            (*No)->info_3 = info;
            (*No)->centro_dir = filho;

        }else if(info > (*No)->info_1 && info < (*No)->info_2){
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = info;

            (*No)->centro_dir = (*No)->centro;
            (*No)->centro = filho;

        }else{
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = (*No)->info_1;
            (*No)->info_1 = info;

            (*No)->centro_dir = (*No)->centro;
            (*No)->centro = (*No)->centro_esq;
            (*No)->centro_esq = filho;

        }
        (*No)->qtdInfo = 3;

    }else{
        if(info > (*No)->info_3){
            (*No)->info_4 = info;
            (*No)->dir = filho;

        }else if(info > (*No)->info_2 && info < (*No)->info_3){
            (*No)->info_4 = (*No)->info_3;
            (*No)->info_3 = info;

            (*No)->dir = (*No)->centro_dir;
            (*No)->centro_dir = filho;

        }else if (info > (*No)->info_1 && info < (*No)->info_2){
            (*No)->info_4 = (*No)->info_3;
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = info;

            (*No)->dir = (*No)->centro_dir;
            (*No)->centro_dir = (*No)->centro;
            (*No)->centro = filho;

        }else{
            (*No)->info_4 = (*No)->info_3;
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = (*No)->info_1;
            (*No)->info_1 = info;

            (*No)->dir = (*No)->centro_dir;
            (*No)->centro_dir = (*No)->centro;
            (*No)->centro = (*No)->centro_esq;
            (*No)->centro_esq = filho;
        }
        (*No)->qtdInfo = 4;
        
    }
}

Arv23 *quebraNo(Arv23 **raiz, int info, int *sobe, Arv23 *filho){
    Arv23 *maiorNo;

    if(info > (*raiz)->info_4){
        *sobe = (*raiz)->info_3;

        maiorNo = criaNo((*raiz)->info_4, (*raiz)->centro_dir, (*raiz)->dir);
        
        maiorNo->info_2 = info;

        maiorNo->centro = filho;

        maiorNo->qtdInfo = 2;

    } else if(info > (*raiz)->info_3){
        *sobe = (*raiz)->info_3;

        maiorNo = criaNo(info, (*raiz)->centro_dir, filho);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

    }else if(info > (*raiz)->info_2){
        *sobe = info;

        maiorNo = criaNo((*raiz)->info_3, (*raiz)->centro, (*raiz)->centro_dir);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

    }else if(info > (*raiz)->info_1){
        *sobe = (*raiz)->info_2;

        maiorNo = criaNo((*raiz)->info_3, (*raiz)->centro, (*raiz)->centro_dir);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

        (*raiz)->info_2 = info;
        (*raiz)->centro = filho;

    }else{
        *sobe = (*raiz)->info_2;

        maiorNo = criaNo((*raiz)->info_3, (*raiz)->centro, (*raiz)->centro_dir);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->qtdInfo = 2;

        (*raiz)->info_2 = (*raiz)->info_1;
        (*raiz)->centro = (*raiz)->centro_esq;
        
        (*raiz)->info_1 = info;
        (*raiz)->centro_esq = filho;

    }

    (*raiz)->qtdInfo = 2;
    // (*raiz)->centro = NULL;

    return maiorNo;
    
}

Arv23 *insere23(Arv23 **raiz, int info, Arv23 *pai, int *sobe){
    Arv23 *maiorNO;
    // maiorNO = NULL;

    if(*raiz == NULL){
        *raiz = criaNo(info, NULL, NULL);
    }else{
        if(folha(*raiz)){
            if((*raiz)->qtdInfo < 4){
                adicionaNo(raiz, info, NULL);
                maiorNO = NULL;
            }else{
                maiorNO = quebraNo(raiz, info, sobe, NULL);

                if(pai == NULL){
                    *raiz = criaNo(*sobe, *raiz, maiorNO);
                    maiorNO = NULL;
                }
            }
        }else{
            if(info < (*raiz)->info_1)
                maiorNO = insere23(&((*raiz)->esq), info, *raiz, sobe);

            else if((*raiz)->qtdInfo == 1 || ((*raiz)->qtdInfo == 2 && info < (*raiz)->info_2))
                maiorNO = insere23(&((*raiz)->centro_esq), info, *raiz, sobe);

            // else if((info > (*raiz)->info_2 && (*raiz)->qtdInfo == 2)  || ((*raiz)->qtdInfo == 3 && info < (*raiz)->info_3))
            else if(((*raiz)->qtdInfo == 2)  || ((*raiz)->qtdInfo == 3 && info < (*raiz)->info_3))
                maiorNO = insere23(&((*raiz)->centro), info, *raiz, sobe);

            // else if((*raiz)->qtdInfo == 2 || ((*raiz)->qtdInfo == 3 && info < (*raiz)->info_3))
            //     maiorNO = insere23(&((*raiz)->centro), info, *raiz, sobe);

            // else if((info > (*raiz)->info_3 && (*raiz)->qtdInfo == 3) || ((*raiz)->qtdInfo == 4 && info < (*raiz)->info_4))
            else if(((*raiz)->qtdInfo == 3) || ((*raiz)->qtdInfo == 4 && info < (*raiz)->info_4))
                maiorNO = insere23(&((*raiz)->centro_dir), info, *raiz, sobe);

            // else if(((*raiz)->qtdInfo == 4 && info < (*raiz)->info_2))
            //     maiorNO = insere23(&((*raiz)->centro_esq), info, *raiz, sobe);

            else 
                maiorNO =insere23(&((*raiz)->dir), info, *raiz, sobe);

            if(maiorNO){
                if((*raiz)->qtdInfo < 4){
                    adicionaNo(raiz, *sobe, maiorNO);
                    maiorNO = NULL;
                }else{
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

void mostrar(Arv23 *Raiz) {
    if (Raiz != NULL) {
        printf("%d ", Raiz->info_1);
        if(Raiz->qtdInfo == 2 || Raiz->qtdInfo > 2)
            printf("%d ", Raiz->info_2);
        if(Raiz->qtdInfo == 3 || Raiz->qtdInfo > 3)
            printf("%d ", Raiz->info_3);
        if(Raiz->qtdInfo == 4)
            printf("%d ", Raiz->info_4);
        printf("Quantidade de Info: %d\n", Raiz->qtdInfo);

        mostrar(Raiz->esq);
        mostrar(Raiz->centro_esq);
        mostrar(Raiz->centro);
        mostrar(Raiz->centro_dir);
        mostrar(Raiz->dir);
    }
}

int main(){
    Arv23 *Raiz = NULL;
    int sobe; 

    // insere23(&Raiz, 400, NULL, &sobe);
    insere23(&Raiz, 1, NULL, &sobe);
    insere23(&Raiz, 2, NULL, &sobe);
    insere23(&Raiz, 3, NULL, &sobe);
    insere23(&Raiz, 4, NULL, &sobe);
    insere23(&Raiz, 5, NULL, &sobe);
    insere23(&Raiz, 6, NULL, &sobe);
    insere23(&Raiz, 7, NULL, &sobe);
    insere23(&Raiz, 8, NULL, &sobe);
    insere23(&Raiz, 9, NULL, &sobe);
    insere23(&Raiz, 10, NULL, &sobe);
    insere23(&Raiz, 11, NULL, &sobe);
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

    mostrar(Raiz);

    return 0;    
}