//
// Created by Vanessa on 22/03/2023.
//

#ifndef LISTA3_SELECAO_H
#define LISTA3_SELECAO_H

int geraAleatorios(char *nomeArquivo, int qtd, int semente);
//Esta função gera 'qtd' números aleatórios e os escreve no arquivo 'nomeArquivo'
//Os numeros devem variar entre 0 e 1000 e devem ser inicializados com a semente
//A função retorna 0 se funcionou corretamente. Retorna 1 se houve algum erro no processo.
//Pesquisem pelas funções rand() e srand().

int* leArquivo(char *nomeArquivo, int qtd);
//Esta função lê 'qtd' dados do arquivo 'nomeArquivo' e os insere em um vetor de inteiros
//A função retorna NULL caso haja algum erro no processo.

void selecao(int *vet, int tam);
//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena (ordem crescente) utilizando o método seleção

void insercao(int *vet, int tam);
//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena utilizando o método insercao

void buscaBinaria(int *vet, int inicio, int fim, int valor, int *res);
//Esta função implementa a busca binária e sua saída é salva no vetor res
//res[0] recebe 1 se encontrou o elemento buscado e 0 caso contrário
//res[1] informa quantas vezes a função buscaBinaria foi chamada, uma vez que ela é recursiva
    //ou seja, sempre que a função é chamada res[1] é incrementado

void imprimeVet(int *vet, int tam);
//Esta função recebe um vetor e o imprime na tela
//A impressão é em linha -> printf("%d ", ...);
//Antes de encerrar, a função imprime uma linha em branco

#endif //LISTA3_SELECAO_H
