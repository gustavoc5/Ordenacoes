// GUSTAVO RAFAEL PAULINO
// 2022006185

// bibliotecas necessárias
#include "rubroNegra.h"
#include <stdio.h>
#include <stdlib.h>

struct no
{
    int chave;
    char cor;
    struct no *Fesq;
    struct no *Fdir;
    struct no *pai;
};

struct rb
{
    struct no *sentinelaRaiz;
    int numElementos;
    struct no *sentinelaFolha;
};

// função auxiliar para criação do nó
no *criaNo(int valor)
{
    no *novo = (no *)malloc(sizeof(no));
    novo->chave = valor;
    novo->cor = 'V';
    novo->Fesq = NULL;
    novo->Fdir = NULL;
    novo->pai = NULL;
    return novo;
}

// Função que cria e retorna uma estrutura do tipo árvore
rb *criaArvore()
{
    rb *nova = (rb *)malloc(sizeof(rb));
    nova->sentinelaRaiz = criaNo(-1000); // seta para o sentinela o valor de -1000
    nova->sentinelaRaiz->cor = 'P';
    nova->numElementos = 0;
    nova->sentinelaFolha = criaNo(-2000);
    nova->sentinelaFolha->cor = 'P';
    nova->sentinelaRaiz->Fdir = nova->sentinelaFolha;
    nova->sentinelaRaiz->Fesq = nova->sentinelaFolha;
    return nova;
}

int insereNo(rb *arv, int valor)
{
    // alocação do no
    no *novo = criaNo(valor);
    no *anterior = arv->sentinelaRaiz;    // y
    no *atual = arv->sentinelaRaiz->Fdir; // x
    // possíveis erros
    if (novo == NULL)
    {
        return 0;
    }
    if (arv == NULL || arv->sentinelaRaiz == NULL)
    {
        free(novo);
        return 0;
    }
    // percorre a rb
    while (atual != arv->sentinelaFolha)
    {
        anterior = atual;
        if (novo->chave < atual->chave)
        {
            atual = atual->Fesq;
        }
        else
            atual = atual->Fdir;
    }
    novo->pai = anterior;
    if (anterior == arv->sentinelaRaiz)
    {
        arv->sentinelaRaiz->Fdir = novo;
    }

    else if (novo->chave < anterior->chave)
    {
        anterior->Fesq = novo;
    }
    else
        anterior->Fdir = novo;
    arv->numElementos++;
    novo->Fdir = arv->sentinelaFolha;
    novo->Fesq = arv->sentinelaFolha;
    balanceamentoInsercao(arv, novo);
    return 1;
}

// função auxiliar que faz a busca na rb
no *busca(rb *arv, no *raiz, int valor)
{
    if (raiz == NULL || raiz == arv->sentinelaFolha || raiz->chave == valor)
    {
        return raiz;
    }

    if (valor < raiz->chave)
    {
        return busca(arv, raiz->Fesq, valor);
    }
    else
    {
        return busca(arv, raiz->Fdir, valor);
    }
}
// função auxiliar que encontra o sucessor do nó a ser removido
no *sucessor(rb *arv, no *noAtual)
{
    if (noAtual->Fdir != arv->sentinelaFolha)
    {
        noAtual = noAtual->Fdir;
        while (noAtual->Fesq != arv->sentinelaFolha)
        {
            noAtual = noAtual->Fesq;
        }
        return noAtual;
    }

    no *noPai = noAtual->pai;
    while (noPai != NULL && noAtual == noPai->Fdir)
    {
        noAtual = noPai;
        noPai = noPai->pai;
    }

    return noPai;
}
// função que remove um nó da rb
int removeNo(rb *arv, int valor)
{
    no *noRemover = busca(arv, getRaiz(arv), valor);
    // se árvore estiver vazia, retorna 0
    if (arv == NULL || arv->sentinelaRaiz == NULL)
    {
        free(noRemover);
        return 0;
    }

    if (noRemover == NULL)
    {
        printf("Valor não encontrado na árvore.\n");
        return -1;
    }

    no *noFilho, *noPai;
    if (noRemover->Fesq == arv->sentinelaFolha || noRemover->Fdir == arv->sentinelaFolha)
    {
        noPai = noRemover;
    }
    else
    {
        noPai = sucessor(arv, noRemover);
    }

    if (noPai->Fesq != arv->sentinelaFolha)
    {
        noFilho = noPai->Fesq;
    }
    else
    {
        noFilho = noPai->Fdir;
    }

    noFilho->pai = noPai->pai;

    if (noPai->pai == NULL)
    {
        arv->sentinelaRaiz->Fdir = noFilho;
    }

    else
    {
        if (noPai == noPai->pai->Fesq)
        {
            noPai->pai->Fesq = noFilho;
        }
        else
        {
            noPai->pai->Fdir = noFilho;
        }
    }

    if (noPai != noRemover)
    {
        noRemover->chave = noPai->chave;
    }

    if (noPai->cor == 'P')
    {
        balanceamentoRemocao(arv, noFilho, noPai->pai, valor);
    }

    arv->numElementos--;
    return 1;
}
// função que faz o balanceamento da rb após a remoção de um nó
void balanceamentoRemocao(rb *arv, no *noDesbal, no *pai, int chave)
{
    no *irmao;

    while (noDesbal != arv->sentinelaRaiz->Fdir && noDesbal->cor == 'P')
    {
        if (noDesbal == pai->Fesq)
        {
            irmao = pai->Fdir;
            if (irmao->cor == 'V')
            { // Caso 1
                irmao->cor = 'P';
                pai->cor = 'V';
                rotacaoEsq(arv, pai);
                irmao = pai->Fdir;
            }

            if (irmao->Fesq->cor == 'P' && irmao->Fdir->cor == 'P')
            { // Caso 2
                irmao->cor = 'V';
                noDesbal = pai;
                pai = noDesbal->pai;
            }
            else
            {
                if (irmao->Fdir->cor == 'P')
                { // Caso 3
                    irmao->Fesq->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoDir(arv, irmao);
                    irmao = pai->Fdir;
                }

                irmao->cor = pai->cor;
                pai->cor = 'P';
                irmao->Fdir->cor = 'P';
                rotacaoEsq(arv, pai);
                noDesbal = arv->sentinelaRaiz->Fdir;
            }
        }
        else
        {
            irmao = pai->Fesq;
            if (irmao->cor == 'V')
            { // Caso 1
                irmao->cor = 'P';
                pai->cor = 'V';
                rotacaoDir(arv, pai);
                irmao = pai->Fesq;
            }

            if (irmao->Fesq->cor == 'P' && irmao->Fdir->cor == 'P')
            { // Caso 2
                irmao->cor = 'V';
                noDesbal = pai;
                pai = noDesbal->pai;
            }
            else
            {
                if (irmao->Fesq->cor == 'P')
                { // Caso 3
                    irmao->Fdir->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoEsq(arv, irmao);
                    irmao = pai->Fesq;
                }

                irmao->cor = pai->cor;
                pai->cor = 'P';
                irmao->Fesq->cor = 'P';
                rotacaoDir(arv, pai);
                noDesbal = arv->sentinelaRaiz->Fdir;
            }
        }

        pai = noDesbal->pai;
    }

    noDesbal->cor = 'P';
    if (noDesbal == arv->sentinelaRaiz->Fdir && noDesbal->Fesq == arv->sentinelaFolha && noDesbal->Fdir == arv->sentinelaFolha)
    {
        if (noDesbal == arv->sentinelaRaiz->Fdir)
        {
            noDesbal->Fdir = arv->sentinelaFolha;
        }
        else if (noDesbal == pai->Fesq)
        {
            pai->Fesq = arv->sentinelaFolha;
        }
        else
        {
            pai->Fdir = arv->sentinelaFolha;
        }
    }
}

// função que imprime a rb binaria em ordem (esq, raiz, dir)
void imprimeOrdem(no *raiz)
{
    if (raiz != NULL)
    {
        imprimeOrdem(raiz->Fesq);
        if (raiz->pai == NULL)
        {
            // printf("%d - %c - %d\n", raiz->chave, raiz->cor, -1);
        }
        else
        {
            printf("%d: %c -- %d\n", raiz->chave, raiz->cor, raiz->pai->chave);
        }
        imprimeOrdem(raiz->Fdir);
    }
}
// função que imprime a rb binaria em pre ordem (raiz, esq, dir)
void imprimePreOrdem(rb *arv, no *raiz)
{
    if (raiz != arv->sentinelaFolha)
    {
        if (raiz != arv->sentinelaRaiz)
        {
            printf("%d: %c -- %d\n", raiz->chave, raiz->cor, raiz->pai->chave);
        }
        imprimePreOrdem(arv, raiz->Fesq);
        imprimePreOrdem(arv, raiz->Fdir);
    }
}

// retorna a raiz da rb
no *getRaiz(rb *arv)
{
    if (arv == NULL || arv->sentinelaRaiz == NULL)
        return NULL;
    return arv->sentinelaRaiz->Fdir;
}
// retorna o numero de elementos da rb
int getNumElementos(rb *arv)
{
    if (arv == NULL || arv->sentinelaRaiz == NULL)
        return 0;

    return arv->numElementos;
}
// função para ler o arquivo
int processaCarga(rb *arv, char *nomeArquivo, int tipo)
{
    FILE *arquivo;
    int valor;
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return -2;
    }

    while (fscanf(arquivo, "%d", &valor) != EOF)
    {
        if (tipo == 1)
            insereNo(arv, valor);
        else if (tipo == 2)
        {
            removeNo(arv, valor);
        }
    }
    return 1;
    fclose(arquivo);
}

void balanceamentoInsercao(rb *arv, no *noDesbalanceado)
{
    no *pai = noDesbalanceado->pai;
    no *avo = pai->pai; //
    no *tio;            // y
    while (pai->cor == 'V')
    {
        if (pai == avo->Fesq)
        {
            tio = avo->Fdir;
            if (tio->cor == 'V')
            {
                pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                noDesbalanceado = avo;
            }
            // caso 2
            else
            {
                if (noDesbalanceado == pai->Fdir)
                {
                    noDesbalanceado = pai;
                    rotacaoEsq(arv, noDesbalanceado);
                }
                // caso 3
                pai = noDesbalanceado->pai;
                avo = pai->pai;
                pai->cor = 'P';
                avo->cor = 'V';
                rotacaoDir(arv, avo);
            }
        }
        else
        {
            tio = avo->Fesq;
            if (tio->cor == 'V')
            {
                pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                noDesbalanceado = avo;
            }
            // caso 2
            else
            {
                if (noDesbalanceado == pai->Fesq)
                {
                    noDesbalanceado = pai;
                    rotacaoDir(arv, noDesbalanceado);
                }
                // caso 3

                pai = noDesbalanceado->pai;
                avo = pai->pai;
                pai->cor = 'P';
                avo->cor = 'V';
                rotacaoEsq(arv, avo);
            }
        }
        if (avo != arv->sentinelaRaiz)
            balanceamentoInsercao(arv, avo);
    }
    arv->sentinelaRaiz->Fdir->cor = 'P';
}
// função que faz a rotação a esquerda
void rotacaoEsq(rb *arv, no *noDesbalanceado)
{
    no *filho = noDesbalanceado->Fdir;
    noDesbalanceado->Fdir = filho->Fesq;
    if (filho->Fesq != arv->sentinelaFolha)
    {
        filho->Fesq->pai = noDesbalanceado;
    }
    filho->pai = noDesbalanceado->pai;
    if (noDesbalanceado->pai == arv->sentinelaRaiz)
    {
        noDesbalanceado->pai->Fdir = filho;
    }
    else if (noDesbalanceado == noDesbalanceado->pai->Fesq)
    {
        noDesbalanceado->pai->Fesq = filho;
    }
    else
    {
        noDesbalanceado->pai->Fdir = filho;
    }
    filho->Fesq = noDesbalanceado;
    noDesbalanceado->pai = filho;
}
// função que faz a rotação a direita
void rotacaoDir(rb *arv, no *noDesbalanceado)
{
    no *filho = noDesbalanceado->Fesq;
    noDesbalanceado->Fesq = filho->Fdir;
    if (filho->Fdir != arv->sentinelaFolha)
    {
        filho->Fdir->pai = noDesbalanceado;
    }
    filho->pai = noDesbalanceado->pai;
    if (noDesbalanceado->pai == arv->sentinelaRaiz)
    {
        noDesbalanceado->pai->Fdir = filho;
    }
    else if (noDesbalanceado == noDesbalanceado->pai->Fdir)
    {
        noDesbalanceado->pai->Fdir = filho;
    }
    else
    {
        noDesbalanceado->pai->Fesq = filho;
    }
    filho->Fdir = noDesbalanceado;
    noDesbalanceado->pai = filho;
}
