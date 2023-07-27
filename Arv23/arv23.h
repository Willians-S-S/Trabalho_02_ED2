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

Arv23 *criaNo(Info *info, Arv23 *noEsq, Arv23 *noCentro);

void lerArquivo(char *path, Arv23 **raiz, char *resultado);

Info *criaInfo(char *palavra, Linhas *lista, int linha);


void adicionaNo(Arv23 **raiz, Info *info, Arv23 *filho);

void inserirLinha(Linhas **no, int linha);

Arv23 *quebraNo(Arv23 **Raiz, Arv23 *filho, Info *info, Info **infoSobe);

Arv23 *inserePalavra(Arv23 **raiz, char *palavra, int linha, Arv23 *pai, Info **infoSobe, int *flag);

void auxiliaInsere(Arv23 **raiz, char *palavra, int linha, Arv23 *pai, Info **infoSobe, char *resultado);

// imprimir
void imprimirLista(Linhas *no);

void imprimirInfo(Info *info);

void imprimirArv(Arv23 *raiz);

//busca
Info *buscaPalavra(Arv23 *raiz, char *palavra, Info **aux);

// Remover
Linhas removeLinha(Linhas **no, int linha, int *flag);
void auxRemover(Arv23 **raiz, char *palavra, int linha, char *resultado);
void MaiorInfoRemoveEsq(Arv23 **raiz, Arv23** PaiMaior, Arv23** MaiorInfoRemove, int LocalInfo);
void Redistribui(Arv23 **raiz, Arv23 **pai);
void remover23(Arv23 **pai, Arv23 **raiz, char *palavra);