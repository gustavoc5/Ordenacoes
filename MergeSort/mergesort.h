//
// Created by Vanessa on 13/04/2023.
//

#ifndef LISTA4_MERGE_MERGESORT_H
#define LISTA4_MERGE_MERGESORT_H

typedef struct tVet tVet;

void mergesort(int *v, int inicio, int fim);
//Função recursiva que executa a fase de divisão do algoritmo mergesort

void merge(int *v, int inicio, int meio, int fim);
//Função que faz a fusão de dois vetores pré-ordenados e os copia para o vetor original

void imprimeVet(int *v, int tam);
//Função que imprime um vetor
//printf("%d ", vet[i])

tVet * leArquivo(char *nomeArquivo);
//Função que lê os dados de um arquivo e carrega em um vetor de inteiros
//Retorna o tipo tVet, composto por um vetor de inteiros e o tamanho do vetor
//A primeira linha do arquivo possui o tamanho do vetor

int getVetTam(tVet *res);
//Função que retorna o tamanho do vetor

int *getVet(tVet *res);
//Função que retorna o vetor


#endif //LISTA4_MERGE_MERGESORT_H
