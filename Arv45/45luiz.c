#include <stdio.h>
#include <stdlib.h>

typedef struct arvore45 Arv45;
struct arvore45 {
    int info1, info2, info3, info4, NInfos;
    Arv45 *esq, *centroesq, *centro, *centrodir, *dir;
};

int EhFolha(Arv45 *no);
Arv45* InsereArv45(Arv45 **raiz, int info, Arv45 *pai, int *sobe);
Arv45* CriaNo(int info, Arv45* esq, Arv45* centroesq, Arv45* centro, Arv45* centrodir, Arv45* dir);
Arv45* quebraNo(Arv45 **no, int info, int *sobe, Arv45* filho);
void adicionaNo(Arv45** node, int info, Arv45* filho);
void ImprimirArvore(Arv45* Raiz, int nivel);

int main() {
    Arv45* RaizArv; RaizArv = NULL;

    int cont = 0;
    // Inserir valores na árvore
    int valores[] = {100, 200, 250, 300, 500, 600, 700, 750, 800, 850, 900, 890,
    950, 1000};
    int numValores = sizeof(valores) / sizeof(valores[0]);
    int i;
	int sobe;
    // for (i = 0; i < 56; i++) {
    //     InsereArv45(&RaizArv, i, NULL, &sobe);
    // }
    InsereArv45(&RaizArv, 721, NULL, &sobe);
    InsereArv45(&RaizArv, 670, NULL, &sobe);
    InsereArv45(&RaizArv, 570, NULL, &sobe);
    InsereArv45(&RaizArv, 922, NULL, &sobe);
    InsereArv45(&RaizArv, 130, NULL, &sobe);
    InsereArv45(&RaizArv, 345, NULL, &sobe);
    InsereArv45(&RaizArv, 797, NULL, &sobe);
    InsereArv45(&RaizArv, 385, NULL, &sobe);
    InsereArv45(&RaizArv, 874, NULL, &sobe);
    InsereArv45(&RaizArv, 405, NULL, &sobe);
    InsereArv45(&RaizArv, 652, NULL, &sobe);
    InsereArv45(&RaizArv, 491, NULL, &sobe);
    InsereArv45(&RaizArv, 830, NULL, &sobe);
    InsereArv45(&RaizArv, 443, NULL, &sobe);
    InsereArv45(&RaizArv, 105, NULL, &sobe);
    InsereArv45(&RaizArv, 285, NULL, &sobe);
    InsereArv45(&RaizArv, 126, NULL, &sobe);
    InsereArv45(&RaizArv, 556, NULL, &sobe);
    InsereArv45(&RaizArv, 795, NULL, &sobe);
    InsereArv45(&RaizArv, 899, NULL, &sobe);
    
    InsereArv45(&RaizArv, 502, NULL, &sobe);
    InsereArv45(&RaizArv, 866, NULL, &sobe);
    InsereArv45(&RaizArv, 725, NULL, &sobe);
    InsereArv45(&RaizArv, 581, NULL, &sobe);
    InsereArv45(&RaizArv, 408, NULL, &sobe);
    InsereArv45(&RaizArv, 348, NULL, &sobe);
    InsereArv45(&RaizArv, 575, NULL, &sobe);
    InsereArv45(&RaizArv, 719, NULL, &sobe);
    InsereArv45(&RaizArv, 983, NULL, &sobe);
    InsereArv45(&RaizArv, 63, NULL, &sobe);

    ImprimirArvore(RaizArv, 0);

    return 0;
}

int EhFolha(Arv45 *no) {
    int EhFolha; EhFolha = 0;
    if (no->esq == NULL && no->centroesq == NULL && no->centro == NULL) {
        EhFolha = 1;
    }

    return (EhFolha);
}

Arv45* InsereArv45(Arv45 **raiz, int info, Arv45 *pai, int *sobe) {
    Arv45 *MaiorNo; MaiorNo = NULL;

    if (*raiz == NULL) {
        *raiz = CriaNo(info, NULL, NULL, NULL, NULL, NULL);
    }
    else {
        if(EhFolha(*raiz) == 1) {
            if((*raiz)->NInfos == 1 || (*raiz)->NInfos == 2 || (*raiz)->NInfos == 3) {
                adicionaNo(raiz, info, NULL);
            }
            else {
                MaiorNo = quebraNo(raiz, info, sobe, NULL);
                if (pai == NULL) {
                    *raiz = CriaNo(*sobe, *raiz, MaiorNo, NULL, NULL, NULL);
                    MaiorNo = NULL;
                }
            }
        }
        else {
            if (info < (*raiz)->info1) {
                MaiorNo = InsereArv45(&((*raiz)->esq), info, *raiz, sobe);
            } else if ((*raiz)->NInfos == 1 || info < (*raiz)->info2) {
                MaiorNo = InsereArv45(&((*raiz)->centroesq), info, *raiz, sobe);
            } else if ((*raiz)->NInfos == 2 || info < (*raiz)->info3) {
                MaiorNo = InsereArv45(&((*raiz)->centro), info, *raiz, sobe);    
            } else if ((*raiz)->NInfos == 3 || info < (*raiz)->info4) {
                MaiorNo = InsereArv45(&((*raiz)->centrodir), info, *raiz, sobe);   
            } else {
                MaiorNo = InsereArv45(&((*raiz)->dir), info, *raiz, sobe);
            }

            if (MaiorNo != NULL) {
                if ((*raiz)->NInfos == 1 || (*raiz)->NInfos == 2 || (*raiz)->NInfos == 3) {
                    adicionaNo(raiz, *sobe, MaiorNo);
                    MaiorNo = NULL;
                }
                else {
                    MaiorNo = quebraNo(raiz, *sobe, sobe, MaiorNo);

                    if (pai == NULL) {
                        *raiz = CriaNo(*sobe, *raiz, MaiorNo, NULL, NULL, NULL);
                        MaiorNo = NULL;
                    }          
                }
            }
        }
    }
    return (MaiorNo);
}

Arv45* quebraNo(Arv45 **no, int info, int *sobe, Arv45* filho) {
    Arv45* MaiorNO;

    if (info > (*no)->info4) {
        *sobe = (*no)->info3;
        MaiorNO = CriaNo(info, (*no)->centrodir, filho, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, (*no)->info4, (*no)->dir);
    }
    else if (info > (*no)->info3 && info < (*no)->info4) {
        *sobe = (*no)->info3;
        MaiorNO = CriaNo((*no)->info4, (*no)->centrodir, (*no)->dir, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, info, filho);
    }
    else if (info > (*no)->info2 && info < (*no)->info3) {
        *sobe = info;
        MaiorNO = CriaNo((*no)->info4, filho, (*no)->dir, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, (*no)->info3, (*no)->centrodir);
    }
    else if (info > (*no)->info1 && info < (*no)->info2) {
        *sobe = (*no)->info2;
        (*no)->info2 = info;
        MaiorNO = CriaNo((*no)->info4, (*no)->centro, (*no)->dir, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, (*no)->info3, (*no)->centrodir);
        (*no)->centro = filho;
    }
    else {
        *sobe = (*no)->info2;
        (*no)->info2 = (*no)->info1;
        MaiorNO = CriaNo((*no)->info4, (*no)->centro, (*no)->dir, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, (*no)->info3, (*no)->centrodir);
        (*no)->centro = (*no)->centroesq;
        (*no)->info1 = info;
        (*no)->centroesq = filho;
    }


    (*no)->centrodir = NULL;
    (*no)->dir = NULL;
    (*no)->NInfos = 2;
    return (MaiorNO);
}

Arv45* CriaNo(int info, Arv45* esq, Arv45* centroesq, Arv45* centro, Arv45* centrodir, Arv45* dir) {
    Arv45* NovoNo = (Arv45*)malloc(sizeof(Arv45));
    
    NovoNo->info1 = info;
    NovoNo->NInfos = 1;
    NovoNo->esq = esq;
    NovoNo->centroesq = centroesq;
    NovoNo->centro = centro;
    NovoNo->centrodir = centrodir;
    NovoNo->dir = dir;

    return NovoNo;
}

void adicionaNo(Arv45** node, int info, Arv45* filho) {
    if ((*node)->NInfos == 1) {
        if (info < (*node)->info1) {
            (*node)->info2 = (*node)->info1;
            (*node)->centro = (*node)->centroesq;
            (*node)->centroesq = filho;
            (*node)->info1 = info;
        }
        else {
            (*node)->info2 = info;
            (*node)->centro = filho;
        }
        (*node)->NInfos = 2;
    }
    else if ((*node)->NInfos == 2) {
        if (info > (*node)->info2) {
            (*node)->info3 = info;
            (*node)->centrodir = filho;
        }
        else if (info < (*node)->info1) {
            (*node)->info3 = (*node)->info2;
            (*node)->centrodir = (*node)->centro;
            (*node)->info2 = (*node)->info1;
            (*node)->centro = (*node)->centroesq;
            (*node)->info1 = info;
            (*node)->centroesq = filho;
        }
        else {
            (*node)->info3 = (*node)->info2;
            (*node)->centrodir = (*node)->centro;
            (*node)->info2 = info;
            (*node)->centro = filho;
        }
        (*node)->NInfos = 3;
    }
    else if ((*node)->NInfos == 3) {
        if (info > (*node)->info3) {
            (*node)->info4 = info;
            (*node)->dir = filho;
        }
        else if (info > (*node)->info2) {
            (*node)->info4 = (*node)->info3;
            (*node)->dir = (*node)->centrodir;
            (*node)->info3 = info;
            (*node)->centrodir = filho;
        }
        else if (info > (*node)->info1) {
            (*node)->info4 = (*node)->info3;
            (*node)->dir = (*node)->centrodir;
            (*node)->info3 = (*node)->info2;
            (*node)->centrodir = (*node)->centro;
            (*node)->info2 = info;
            (*node)->centro = filho;
        }
        else {
            (*node)->info4 = (*node)->info3;
            (*node)->dir = (*node)->centrodir;
            (*node)->info3 = (*node)->info2;
            (*node)->centrodir = (*node)->centro;
            (*node)->info2 = (*node)->info1;
            (*node)->centro = (*node)->centroesq;
            (*node)->info1 = info;
            (*node)->centroesq = filho;
        }
        (*node)->NInfos = 4;
    }
}

void ImprimirArvore(Arv45* Raiz, int nivel) {
    if (Raiz != NULL) {
        // Imprimir os valores do nível atual
        for (int i = 0; i < nivel; i++) {
            printf("\t");
        }

        printf("Nivel %d: ", nivel);
        
        // Imprimir os valores de acordo com o número de informações presentes no nó
        printf("%d ", Raiz->info1);
        if (Raiz->NInfos == 2) {
            printf("%d ", Raiz->info2);
        }
        if (Raiz->NInfos == 3) {
            printf("%d ", Raiz->info2);
            printf("%d ", Raiz->info3);
        }
        if (Raiz->NInfos == 4) {
            printf("%d ", Raiz->info2);
            printf("%d ", Raiz->info3);
            printf("%d ", Raiz->info4);
        }

        printf("NInfos %d\n", Raiz->NInfos);

        // Recursivamente imprimir os filhos
        ImprimirArvore(Raiz->esq, nivel + 1);
        ImprimirArvore(Raiz->centroesq, nivel + 1);
        ImprimirArvore(Raiz->centro, nivel + 1);
        ImprimirArvore(Raiz->centrodir, nivel + 1);
        ImprimirArvore(Raiz->dir, nivel + 1);
    }
}