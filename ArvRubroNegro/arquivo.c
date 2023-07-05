// #include <stdio.h>

// int main() {
//     FILE *arquivo = fopen("arquivo.txt", "a+"); // Abrir o arquivo em modo leitura e gravação

//     if (arquivo == NULL) {
//         printf("Erro ao abrir o arquivo.");
//         return 1;
//     }

//     int linhaDesejada = 3; // Definir a linha desejada
//     int tamanhoMaxLinha = 100; // Definir o tamanho máximo de cada linha

//     // Calcular a posição da linha desejada
//     long posicaoLinha = (linhaDesejada - 1) * tamanhoMaxLinha;

//     // Mover o ponteiro do arquivo para a posição da linha desejada
//     fseek(arquivo, posicaoLinha, SEEK_SET);

//     // Escrever o conteúdo na linha especificada
//     fprintf(arquivo, " Texto a ser escrito na linha %d", linhaDesejada);

//     fclose(arquivo); // Fechar o arquivo

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *arquivo = fopen("arquivo.txt", "r"); // Abrir o arquivo em modo leitura

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    char frase[100], linha[100]; // Definir um buffer para armazenar a frase
    // fgets(frase, sizeof(frase), arquivo); // Ler a frase do arquivo

    char *palavraDesejada = "Texto"; // Definir a palavra desejada
    char *palavra;

    // palavra = strtok(frase, " "); // Separar a frase em palavras usando espaço em branco como separador

    int contador = 1;

     while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s\n", linha);
        palavra = strtok(linha, " ");
        printf("%s\n", linha);
        while (palavra != NULL && (strcmp(palavra, palavraDesejada) != 0)) {
            palavra = strtok(NULL, " "); // Ler a próxima palavra
            if(palavra != NULL)
                contador = strcmp(palavra, palavraDesejada);
        }
        printf("%s \n", linha);
    }


    if (palavra != NULL) {
        printf("Palavra lida: %s\n", palavra);
    } else {
        printf("Palavra não encontrada.\n");
    }

    fclose(arquivo); // Fechar o arquivo

    return 0;
}
