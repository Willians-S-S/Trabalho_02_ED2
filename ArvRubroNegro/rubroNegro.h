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

typedef struct Rubro Rubro;

// Rubro vai ser a arvore
struct Rubro{
    Info *info;
    int cor; 
    Rubro *esq, *dir;
};

Rubro *buscarPalavra1(Rubro *raiz, char *palavra, int achou[]);

void lerArquivo(char *nomeArquivo, Rubro **raiz, int inseriu[]);

Rubro *buscarPalavra(Rubro *raiz, char *palavra, int linha, int achou[]);

int buscaLinha(Linhas *no, int linha, int achou[]);

void balancear(Rubro **raiz);

void mover2EsqRed(Rubro **raiz);

void mover2DirRed(Rubro **raiz);

void removeMenor(Rubro **raiz);

int removePalavra(Rubro **raiz, char *palavra);

int removeLinha(Linhas **no, int linha, int achou[]);

int auxRemover(Rubro **raiz, char *palavra, int linha, int achou[]);

int cor(Rubro *raiz);

void inserirLinha(Linhas **no, int linha, int inseriu[]);

Rubro *criaNo(char *palavra, int linha, int inseriu[]);

void inserirPalavra(Rubro **raiz, char *palavra, int linha, int *inseriu);

// void excluirPalavra();

void inserirRubro(Rubro **raiz, char *palavra, int linha, int inseriu[]);

void trocaCor(Rubro *raiz);

void rotacaoEsq(Rubro **raiz);

void rotacaoDir(Rubro **raiz);
