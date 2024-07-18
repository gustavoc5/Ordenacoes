// bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include "arvorebinaria.h"

struct no
{
    int chave;
    struct no *Fesq;
    struct no *Fdir;
    struct no *pai;
};

struct arvore
{
    struct no *sentinela;
    int numElementos;
};

// função auxiliar para criação do nó
no *criaNo(int valor)
{
    no *novo = (no *)malloc(sizeof(no));
    novo->chave = valor;
    novo->Fesq = NULL;
    novo->Fdir = NULL;
    novo->pai = NULL;
    return novo;
}

// Função que cria e retorna uma estrutura do tipo árvore
arvore *criaArvore()
{
    arvore *nova = (arvore *)malloc(sizeof(arvore));
    nova->sentinela = criaNo(-1000); // seta para o sentinela o valor de -1000
    nova->numElementos = 0;
    return nova;
}
// função para inserção do nó na árvore binaria
int insereNo(arvore *arv, int valor)
{
    // alocação do no
    no *novo = criaNo(valor);
    no *anterior = arv->sentinela;
    no *atual = arv->sentinela->Fdir;
    // possíveis erros
    if (novo == NULL)
    {
        return 0;
    }
    if (arv == NULL || arv->sentinela == NULL)
    {
        free(novo);
        return 0;
    }
    // percorre a arvore
    while (atual != NULL)
    {
        anterior = atual;
        if (valor < atual->chave)
            atual = atual->Fesq;
        else
            atual = atual->Fdir;
    }
    // chega a raiz da arvore
    if (anterior == arv->sentinela)
        arv->sentinela->Fdir = novo;
    else if (valor < anterior->chave)
        anterior->Fesq = novo;
    else
        anterior->Fdir = novo;

    novo->pai = anterior;
    arv->numElementos++;
    return 1;
}
// função para remoção do nó da arvore
int removeNo(arvore *arv, int valor)
{
    if (arv->sentinela->Fdir == NULL)
    {
        // a árvore está vazia
        return 0;
    }
    no *atual = arv->sentinela->Fdir;
    no *pai_atual = arv->sentinela;
    // percorre ate encontrar o valor
    while (atual != NULL && atual->chave != valor)
    {
        pai_atual = atual;
        if (valor < atual->chave)
        {
            atual = atual->Fesq;
        }
        else
        {
            atual = atual->Fdir;
        }
    }
    if (atual == NULL)
    {
        // o elemento não está presente na árvore

        return -1;
    }
    // verifica se o nó a ser removido tem pelo menos um filho
    if (atual->Fesq == NULL || atual->Fdir == NULL)
    {
        no *filho = NULL;
        if (atual->Fesq != NULL)
        {
            filho = atual->Fesq;
        }
        else
        {
            filho = atual->Fdir;
        }
        if (filho == NULL)
        {
            // caso em que o nó a ser removido não tem filhos
            if (atual == arv->sentinela->Fdir)
            {
                // remove a raiz da árvore vazia
                arv->sentinela->Fdir = NULL;
            }
            else
            {
                // remove o nó folha
                if (pai_atual->Fesq == atual)
                {
                    pai_atual->Fesq = NULL;
                }
                else
                {
                    pai_atual->Fdir = NULL;
                }
                atual->pai = NULL;
            }
            free(atual);
        }
        else
        {
            // caso em que o nó a ser removido tem um filho
            if (atual == arv->sentinela->Fdir)
            {
                // remove a raiz da árvore
                arv->sentinela->Fdir = filho;
                filho->pai = arv->sentinela;
            }
            else
            {
                // remove um nó interno
                if (pai_atual->Fesq == atual)
                {
                    pai_atual->Fesq = filho;
                }
                else
                {
                    pai_atual->Fdir = filho;
                }
                filho->pai = pai_atual;
                atual->pai = NULL;
            }
            free(atual);
        }
    }
    else
    {
        // caso em que o nó a ser removido tem dois filhos
        no *sucessor = atual->Fdir;
        no *pai_sucessor = atual;
        while (sucessor->Fesq != NULL)
        {
            pai_sucessor = sucessor;
            sucessor = sucessor->Fesq;
        }

        atual->chave = sucessor->chave;
        if (pai_sucessor == atual)
        {
            pai_sucessor->Fdir = sucessor->Fdir;
        }
        else
        {
            pai_sucessor->Fesq = sucessor->Fdir;
        }

        if (sucessor->Fdir != NULL)
        {
            sucessor->Fdir->pai = pai_sucessor;
        }
        free(sucessor);
    }
    arv->numElementos--;
    return 1;
}
// função que imprime a arvore binaria em ordem (esq, raiz, dir)
void imprimeOrdem(no *raiz)
{
    if (raiz != NULL)
    {
        imprimeOrdem(raiz->Fesq);
        if (raiz->pai == NULL)
        {
            printf("%d - %d\n", raiz->chave, -1);
        }
        else
        {
            printf("%d - %d\n", raiz->chave, raiz->pai->chave);
        }
        imprimeOrdem(raiz->Fdir);
    }
}
// função que imprime a arvore binaria em pre ordem (raiz, esq, dir)
void imprimePreOrdem(no *raiz)
{
    if (raiz != NULL)
    {
        if (raiz->pai == NULL)
        {
            printf("%d - %d\n", raiz->chave, -1);
        }
        else
        {
            printf("%d - %d\n", raiz->chave, raiz->pai->chave);
        }
        imprimePreOrdem(raiz->Fesq);
        imprimePreOrdem(raiz->Fdir);
    }
}
// retorna a raiz da arvore
no *getRaiz(arvore *arv)
{
    if (arv == NULL || arv->sentinela == NULL)
        return NULL;

    return arv->sentinela->Fdir;
}
// retorna o numero de elementos da arvore
int getNumElementos(arvore *arv)
{
    if (arv == NULL || arv->sentinela == NULL)
        return 0;

    return arv->numElementos;
}
// função para ler o arquivo
void processaCarga(arvore *arv, char *nomeArquivo)
{
    FILE *arquivo;
    int valor;

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    while (fscanf(arquivo, "%d", &valor) != EOF)
    {
        insereNo(arv, valor);
    }

    fclose(arquivo);
}