//
// Created by Vanessa on 20/03/2023.
//

#ifndef BOLHA_H
#define BOLHA_H

typedef struct tReturn tReturn;
//declara o tipo de dados tReturn

tReturn* alocatReturn();
//Essa função aloca memória para uma variável do tipo tReturn

int *getVet(tReturn *rep);
//Essa função retorna o vetor contido na estrutura tReturn;

int getTam(tReturn *rep);
//Essa função retorna o tamanho vetor contido na estrutura tReturn;

int getErro(tReturn *rep);
//Essa função retorna o valor da variável error contido na estrutura tReturn;

void trataErro(int erro);
//Essa função trata os erros relativos à função leArquivo
//erro 1 : abertura do arquivo -- printf("Erro ao abrir o arquivo\n");
//erro 2: leitura do arquivo -- printf("Erro ao ler do arquivo\n");
//erro 3 : alocação de memória -- printf("Erro ao alocar memória\n");

tReturn* leArquivo(char nomeArquivo[]);
//Essa função lê um arquivo com números inteiros (um número por linha) e preenche um vetor
//A primeira linha do arquivo contém o tamanho do vetor
//A função retorna o tipo TReturn formado por um ponteiro para inteiros, um inteiro que guarda o tamanho do vetor e um inteiro que codifica erros

int bolha (int *vet, int tam);
//Essa função ordena o vetor usando o método bolha e retorna a quantidade de comparações realizadas

int bolhaInteligente (int *vet, int tam);
//Essa função ordena o vetor usando o método bolha inteligente e retorna a quantidade de comparações realizadas

void imprimeVet(int *vet, int tam);
//Essa função imprime os dados de um vetor (um número por linha) - printf("%d\n", vet[i])


#endif //BOLHA_H

