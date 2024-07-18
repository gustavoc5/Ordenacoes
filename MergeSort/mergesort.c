#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

struct tVet
{
    int *vet;
    int tam;
};
// definição da struct

void mergesort(int *v, int inicio, int fim)
{
    int meio;
    if (inicio < fim)
    // algoritmo do mergesort
    {
        meio = (inicio + fim) / 2;
        mergesort(v, inicio, meio);
        mergesort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}
// Função recursiva que executa a fase de divisão do algoritmo mergesort

void merge(int *v, int inicio, int meio, int fim)
{
    int marca1 = inicio;            // controla as posições do vetor logico 1
    int marca2 = meio + 1;          // controla as posições do vetor logico 2
    int vetAux[(fim - inicio) + 1]; // vetor auxiliar
    int i = 0;                      // contador do vetor auxiliar
    int k;                          // contador para cópia final

    while (marca1 <= meio && marca2 <= fim)
    {
        if (v[marca1] < v[marca2])
        {
            vetAux[i] = v[marca1];
            marca1++;
        }
        else
        {
            vetAux[i] = v[marca2];
            marca2++;
        }
        // incremento da posição do marcador
        i++;
    }
    // copia o resto do vetor 1 para o vetor auxiliar
    while (marca1 <= meio)
    {
        vetAux[i] = v[marca1];
        marca1++;
        i++;
    }
    // copia o resto do vetor 2 para o auxiliar
    while (marca2 <= fim)
    {
        vetAux[i] = v[marca2];
        marca2++;
        i++;
    }
    // copia o vetor auxiliar para o vetor original
    for (k = 0; k < i; k++)
    {
        v[inicio + k] = vetAux[k];
    }
}
// Função que faz a fusão de dois vetores pré-ordenados e os copia para o vetor original

void imprimeVet(int *v, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%d ", v[i]);
    }
}
// Função que imprime um vetor

tVet *leArquivo(char *nomeArquivo)
{
    // alocação do vetor e atribuições
    tVet *v = (tVet *)malloc(sizeof(tVet));
    v->vet = NULL;
    v->tam = 0;
    // abertura do arquivo em modo de leitura
    FILE *arq = fopen(nomeArquivo, "r");
    // atribuição do tamanho correto
    fscanf(arq, "%d", &v->tam);
    // alocação do vetor com base no tamanho
    v->vet = (int *)malloc(sizeof(int) * (size_t)v->tam);
    // preenchimento do vetor
    for (int i = 0; i < v->tam; i++)
    {
        // a função fscanf retorna o número de valores lidos corretamente, portanto com um teste podemos saber se houve erro ou não na leitura do arquivo
        int num = fscanf(arq, "%d", &v->vet[i]);
        if (num != 1)
        {
            fclose(arq);
            return v;
        }
    }
    // por fim fecha o arquivo e retorna a struct
    fclose(arq);
    return v;
}
// Função que lê os dados de um arquivo e carrega em um vetor de inteiros
int getVetTam(tVet *res)
{
    return res->tam;
}
// Função que retorna o tamanho do vetor

int *getVet(tVet *res)
{
    return res->vet;
}
// Função que retorna o vetor