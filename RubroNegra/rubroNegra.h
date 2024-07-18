//
// Created by Vanessa on 25/05/2023.
//

#ifndef LISTA8_RUBRONEGRA_H
#define LISTA8_RUBRONEGRA_H

typedef struct no no;
typedef struct rb rb;


//Função que cria e retorna uma estrutura do tipo árvore balanceada utilizando o algoritmo AVL
rb *criaArvore();

//Função que insere um elemento na árvore
//Retorna 1 se a inserção foi realizada com sucesso
//Retorna 0 se não foi possível realizar a inserção
int insereNo(rb *arv, int valor);

//Função que remove um elemento da árvore implementando a remoção por cópia usando o sucessor
//Retorna 1 se o elemento foi removido
//Retorna 0 se a árvore estiver vazia
//Retorna -1 caso o elemento a ser removido não esteja na árvore
int removeNo(rb *arv, int valor);

//Função que imprime a árvore em ordem
//printf("%d: %c -- %d\n", raiz->chave, raiz->cor, raiz->pai->chave);
void imprimeOrdem(no *raiz);

//Função que imprime a árvore em pré-ordem
//printf("%d: %c -- %d\n", raiz->chave, raiz->cor, raiz->pai->chave);
void imprimePreOrdem(rb *arv, no *raiz);

//Função que retorna a raiz da árvore
no *getRaiz(rb *arv);

//Função que retorna a quantidade de elementos da árvore
int getNumElementos(rb *arv);

//Função que lê um arquivo com números inteiros e um tipo
//Se o tipo for 1, a função deve chamar insereNo
//Se o tipo for 2, a função deve chamar removeNo
//Retorna -2 se o arquivo não puder ter sido lido
//Se o tipo for 1, insere os elementos na árvore e retorna os valores obtidos com o processamento da inserção
//  Retorna 1 se a inserção foi realizada com sucesso
//  Retorna 0 se não foi possível realizar a inserção
//Se o tipo for 2, remove os elementos da árvore e retorna os valores obtidos com o processamento da remoção
//  Retorna 1 se o elemento foi removido
//  Retorna 0 se a árvore estiver vazia
//Os valores retornados são tratados na main
int processaCarga(rb *arv, char *nomeArquivo, int tipo);

/***********FUNÇÕES DA Rubro Negra**************/

//Função que corrige o balanceamento após a inserção
void balanceamentoInsercao(rb *arv, no *noDesbal);

//Função que corrige o balanceamento após a remoção
void balanceamentoRemocao(rb *arv, no *noDesbal, no *pai, int valor);

//Função que implementa a rotação à direita
void rotacaoDir(rb * arv, no *noDesbal);

//Função que implementa a rotação à esquerda
void rotacaoEsq(rb * arv, no *noDesbal);

#endif //LISTA8_RUBRONEGRA_H
