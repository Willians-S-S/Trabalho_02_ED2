typedef struct Linhas Linhas;

// Lista encadeada com com os numeros das linhas
struct Linhas{
    int linha;
    Linhas *prox;
};


typedef struct Info Info;

// Infor vai conter a palavra e a lista de números das linha
struct Info{
    char *palavra;
    Linhas *ListaNum;
};

typedef struct Arv23 Arv23;

struct  Arv23 {
    Info *info1, *info2;
    int numInfo;
    Arv23 *esq, *centro, *dir;
};

Arv23 *inserePalavra(Arv23 **raiz, char *palavra, int linha, Arv23 *pai, char *sobe, Linhas **listaSobe);


