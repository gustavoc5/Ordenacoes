#include <stdio.h>
#include <stdlib.h>
#include "selecao.h"

int main() {
    char nomeArquivo[30];
    int *vet; //guarda o vetor que será ordenado
    int res[2]; //guarda o resultado da busca binária. Possui 2 posições.
    int tam; // tamanho do vetor
    int semente; // semente para geração dos aleatórios
    int elemento; // número que será buscado no vetor por busca binária

    scanf("%s", nomeArquivo);
    scanf("%d", &tam);
    scanf("%d", &semente);
    geraAleatorios(nomeArquivo, tam, semente);
    vet = leArquivo(nomeArquivo, tam);
    selecao(vet, tam);
    imprimeVet(vet, tam);
    vet = leArquivo(nomeArquivo, tam);
    insercao(vet, tam);
    imprimeVet(vet, tam);

    //****busca binária****/////
    scanf("%d", &elemento);
    res[0] = -1;
    res[1] = 0;
    buscaBinaria(vet, 0, tam-1, elemento, res);
    if (res[0] == 1)
        printf("\nElemento %d encontrado no vetor\n", elemento);
    else
        printf("\nElemento %d NAO encontrado no vetor\n", elemento);
    printf("\nA busca binaria foi chamada %d vezes\n", res[1]);
    free(vet);

    return 0;
}
