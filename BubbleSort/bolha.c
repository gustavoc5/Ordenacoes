#include <stdio.h>
#include <stdlib.h>
#include "bolha.h"
// struct definida
struct tReturn
{
    int *vet;
    int tam;
    int erro;
};

typedef struct tReturn tReturn;

// alocação da struct
tReturn *alocatReturn()
{
    // atribuição de valores padrão para os campos da struct
    tReturn *rep = (tReturn *)malloc(sizeof(tReturn));
    rep->vet = NULL;
    rep->tam = 0;
    rep->erro = 0;
    return rep;
}

// retorna o vetor
int *getVet(tReturn *rep)
{
    int *vetor = rep->vet;
    return vetor;
}
// retorna o tamanho do vetor
int getTam(tReturn *rep)
{
    int tamanho = rep->tam;
    return tamanho;
}
// retorna o tipo de erro
int getErro(tReturn *rep)
{
    int error = rep->erro;
    return error;
}

// verificação de qual erro ocorreu
void trataErro(int erro)
{
    switch (erro)
    {
    case 1:
        printf("Erro ao abrir o arquivo\n");
        break;

    case 2:
        printf("Erro ao ler do arquivo\n");
        break;

    case 3:
        printf("Erro ao alocar memória\n");
        break;

    default:
        printf("Outro erro\n");
        break;
    }
}
// função para leitura do arquivo e atribuição dos campos da struct
tReturn *leArquivo(char nomeArquivo[])
{
    // cria e aloca uma struct tReturn
    tReturn *ret = alocatReturn();
    // tenta abrir o arquivo
    FILE *arq = fopen(nomeArquivo, "r");
    // caso o arquivo seja nulo, houve erro ao abrir o arquivo
    if (arq == NULL)
    {
        ret->erro = 1;
        return ret;
    }
    // lê o primeiro valor do arquivo e armazena no campo de tamanho
    fscanf(arq, "%d", &ret->tam);
    // caso o tamanho seja nulo, houve erro na leitura do arquivo
    if (&(ret->tam) == NULL)
    {
        fclose(arq);
        ret->erro = 2;
        return ret;
    }
    // aloca memória suficiente para o vetor
    ret->vet = (int *)malloc(sizeof(int) * (size_t)ret->tam);
    // caso o vetor seja nulo, houve erro na alocação de memória
    if (ret->vet == NULL)
    {
        fclose(arq);
        ret->erro = 3;
        return ret;
    }
    // varre o arquivo e armazena os valores no vetor
    for (int i = 0; i < ret->tam; i++)
    {
        // a função fscanf retorna o número de valores lidos corretamente, portanto com um teste podemos saber se houve erro ou não na leitura do arquivo
        int num = fscanf(arq, "%d", &ret->vet[i]);
        if (num != 1)
        {
            fclose(arq);
            ret->erro = 2;
            return ret;
        }
    }
    // por fim fecha o arquivo e retorna a struct
    fclose(arq);
    return ret;
}
// algoritmo de ordenação bolha
int bolha(int *vet, int tam)
{
    // inicializa comparações em 0
    int comp = 0;
    int aux;
    // percorre o vetor inteiro
    for (int i = 0; i < tam; i++)
    {
        // a cada posição, compara-se a posição atual com a anterior
        for (int j = 1; j < tam; j++)
        {
            comp++;
            // caso a atual seja maior que a anterior, faz-se a troca dos elementos
            if (vet[j] < vet[j - 1])
            {
                aux = vet[j - 1];
                vet[j - 1] = vet[j];
                vet[j] = aux;
            }
        }
    }
    return comp;
}

int bolhaInteligente(int *vet, int tam)
{
    int comp = 0;
    int aux;
    int troca = 1;
    // enquanto houver trocas, o bolha inteligente continua percorrendo o vetor
    while (troca != 0)
    {
        troca = 0;
        for (int i = 1; i < tam; i++)
        {
            comp++;
            // compara-se o elemento atual com o anterior
            if (vet[i] < vet[i - 1])
            {
                aux = vet[i - 1];
                vet[i - 1] = vet[i];
                vet[i] = aux;
                // atualiza o valor de troca para 1, sinalizando para continuar a ordenação
                troca = 1;
            }
        }
        // a cada iteração o tamanho diminui pois é garantia que a posição [tam-i] foi ordenada
        tam--;
    }
    return comp;
}
// impressão do vetor ordenado um elemento por linha
void imprimeVet(int *vet, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%d\n", vet[i]);
    }
}