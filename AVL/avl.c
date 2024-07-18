#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
struct no
{
    int chave;
    int fb;
    struct no *Fesq;
    struct no *Fdir;
    struct no *pai;
};
struct avl
{
    struct no *sentinela;
    int numElementos;
};
// função auxiliar para criação do nó
no *criaNo(int valor)
{
    no *novo = (no *)malloc(sizeof(no));
    novo->chave = valor;
    novo->fb = 0;
    novo->Fesq = NULL;
    novo->Fdir = NULL;
    novo->pai = NULL;
    return novo;
}
// Função que cria e retorna uma estrutura do tipo árvore
avl *criaArvore()
{
    avl *nova = (avl *)malloc(sizeof(avl));
    nova->sentinela = criaNo(-1000);
    nova->numElementos = 0;
    return nova;
}
// função para inserção do nó na árvore binaria
int insereNo(avl *arv, int valor)
{
    no *novo = criaNo(valor);
    no *anterior = arv->sentinela;
    no *atual = arv->sentinela->Fdir;
    if (novo == NULL)
        return 0;
    if (arv == NULL || arv->sentinela == NULL)
    {
        // arvore vazia
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
    if (anterior == arv->sentinela)
        arv->sentinela->Fdir = novo;
    else if (valor < anterior->chave)
        anterior->Fesq = novo;
    else
        anterior->Fdir = novo;
    novo->pai = anterior;
    arv->numElementos++;
    if (novo->pai == arv->sentinela)
        return 0;
    // atualização do fb após inserção
    atualizaFB_insercao(arv, novo);
    return 1;
}
// função que trata os casos e remove um valor da avl
int removeNo(avl *arv, int valor)
{
    if (arv->sentinela->Fdir == NULL)
        // arvore vazia
        return 0;
    no *atual = arv->sentinela->Fdir;
    no *pai_atual = arv->sentinela;
    no *filho = NULL;
    // percorre ate encontrar o valor
    while (atual != NULL && atual->chave != valor)
    {
        pai_atual = atual;
        if (valor < atual->chave)
            atual = atual->Fesq;
        else
            atual = atual->Fdir;
    }
    if (atual == NULL)
        return 0;
    // verifica se o nó a ser removido tem pelo menos um filho
    if (atual->Fesq == NULL || atual->Fdir == NULL)
    {
        if (atual->Fesq != NULL)
            filho = atual->Fesq;
        else
            filho = atual->Fdir;
        if (filho == NULL)
        {
            if (atual == arv->sentinela->Fdir)
                // remove a raiz da arvore vazia
                arv->sentinela->Fdir = NULL;
            else
            {
                // remove o nó folha
                if (pai_atual->Fesq == atual)
                    pai_atual->Fesq = NULL;
                else
                    pai_atual->Fdir = NULL;
                atual->pai = NULL;
            }
        }
        else
        {
            // caso em que o nó a ser removido tem um filho
            if (atual == arv->sentinela->Fdir)
            {
                arv->sentinela->Fdir = filho;
                filho->pai = arv->sentinela;
            }
            else
            {
                // remove um nó interno
                if (pai_atual->Fesq == atual)
                    pai_atual->Fesq = filho;
                else
                    pai_atual->Fdir = filho;
                filho->pai = pai_atual;
            }
        }
    }
    else
    {
        // caso em que o nó a ser removido tem dois filhos
        no *sucessor = atual->Fdir;
        while (sucessor->Fesq != NULL)
        {
            sucessor = sucessor->Fesq;
        }
        atual->chave = sucessor->chave;
        atual = sucessor;
        if (atual->pai == arv->sentinela)
            arv->sentinela->Fdir = atual->Fdir;
        else
        {
            if (atual == atual->pai->Fesq)
                atual->pai->Fesq = atual->Fdir;
            else
                atual->pai->Fdir = atual->Fdir;
        }

        if (atual->Fdir != NULL)
            atual->Fdir->pai = atual->pai;
    }
    // atualiza-se o fb após a remoção e libera a memória
    if (filho != NULL && filho != arv->sentinela)
        atualizaFB_remocao(arv, filho, atual->chave);
    free(atual);
    arv->numElementos--;
    return 1;
}
void imprimeOrdem(no *raiz)
{
    if (raiz != NULL)
    {
        imprimeOrdem(raiz->Fesq);
        if (raiz->pai == NULL)
            printf("%d - %d - %d\n", raiz->chave, -1, raiz->fb);
        else
            printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        imprimeOrdem(raiz->Fdir);
    }
}
void imprimePreOrdem(no *raiz)
{
    if (raiz != NULL)
    {
        if (raiz->pai == NULL)
            printf("%d - %d - %d\n", raiz->chave, -1, raiz->fb);
        else
            printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        imprimePreOrdem(raiz->Fesq);
        imprimePreOrdem(raiz->Fdir);
    }
}
// retorna a raiz da avl
no *getRaiz(avl *arv)
{
    if (arv == NULL || arv->sentinela == NULL)
        return NULL;
    return arv->sentinela->Fdir;
}
// retorna o numero de elementos da avl
int getNumElementos(avl *arv)
{
    if (arv == NULL || arv->sentinela == NULL)
        return 0;
    return arv->numElementos;
}
// função para ler o arquivo
int processaCarga(avl *arv, char *nomeArquivo, int tipo)
{
    FILE *arquivo;
    int valor;
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
        return -2;
    while (fscanf(arquivo, "%d", &valor) != EOF)
    {
        if (tipo == 1)
            insereNo(arv, valor);
        else if (tipo == 2)
            removeNo(arv, valor);
    }
    return 1;
    fclose(arquivo);
}
void atualizaFB_insercao(avl *arv, no *novoNo)
{
    no *aux = novoNo;
    do
    {
        if (aux->chave < aux->pai->chave)
            (aux->pai->fb)--;
        else
            (aux->pai->fb)++;
        aux = aux->pai;
    } while (aux->fb != 0 && aux->fb != -2 && aux->fb != 2 && aux->pai != arv->sentinela && aux->pai->chave != -1000);
    if (aux->fb == -2)
        balanceamento(arv, aux);
    else if (aux->fb == 2)
        balanceamento(arv, aux);
}
void atualizaFB_remocao(avl *arv, no *pai, int chave)
{
    no *aux = pai;
    if (aux == NULL || aux->fb == 1 || aux->fb == -1)
        return;
    if (aux->fb == 2 || aux->fb == -2)
    {
        balanceamento(arv, pai);
        if (aux->pai != NULL && aux->pai->fb == 0)
            atualizaFB_remocao(arv, aux->pai, chave);
    }
}

void balanceamento(avl *arv, no *noDesbalanceado)
{
    no *filho;
    if (noDesbalanceado->fb == 2)
    {
        filho = noDesbalanceado->Fdir;
        if (filho->fb == -1)
        {
            // rotação dupla
            int fbNeto = filho->Fesq->fb;
            rotacaoDir(filho);
            rotacaoEsq(noDesbalanceado);
            // ajustar fb
            if (fbNeto == -1)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 1;
            }
            else if (fbNeto == 0)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else if (fbNeto == 1)
            {
                noDesbalanceado->fb = -1;
                filho->fb = 0;
            }
        }
        else
        {
            int fbFilho = filho->fb;
            rotacaoEsq(noDesbalanceado);
            // só na remoção
            if (fbFilho == 0)
            {
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            }
            else if (fbFilho == 1)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
        }
    }
    else if (noDesbalanceado->fb == -2)
    {
        filho = noDesbalanceado->Fesq;
        if (filho->fb == 1)
        {
            int fbNeto = filho->Fdir->fb;
            rotacaoEsq(filho);
            rotacaoDir(noDesbalanceado);
            if (fbNeto == -1)
            {
                noDesbalanceado->fb = 1;
                filho->fb = 0;
            }
            else if (fbNeto == 0)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else if (fbNeto == 1)
            {
                noDesbalanceado->fb = 0;
                filho->fb = -1;
            }
        }
        else
        {
            int fbFilho = filho->fb;
            rotacaoDir(noDesbalanceado);
            if (fbFilho == 0)
            {
                noDesbalanceado->fb = -1;
                filho->fb = 1;
            }
            else if (fbFilho == -1)
            {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
        }
    }
}
void rotacaoEsq(no *noDesbalanceado)
{
    no *filho = noDesbalanceado->Fdir;
    noDesbalanceado->Fdir = filho->Fesq;
    if (filho->Fesq != NULL)
        filho->Fesq->pai = noDesbalanceado;
    filho->pai = noDesbalanceado->pai;
    if (noDesbalanceado->pai->chave == -1000)
        noDesbalanceado->pai->Fdir = filho;
    else if (noDesbalanceado == noDesbalanceado->pai->Fesq)
        noDesbalanceado->pai->Fesq = filho;
    else
        noDesbalanceado->pai->Fdir = filho;
    filho->Fesq = noDesbalanceado;
    noDesbalanceado->pai = filho;
    noDesbalanceado->fb = 0;
    filho->fb = 0;
}
void rotacaoDir(no *noDesbalanceado)
{
    no *filho = noDesbalanceado->Fesq;
    noDesbalanceado->Fesq = filho->Fdir;
    if (filho->Fdir != NULL)
        filho->Fdir->pai = noDesbalanceado;
    filho->pai = noDesbalanceado->pai;
    if (noDesbalanceado->pai->chave == -1000)
        noDesbalanceado->pai->Fdir = filho;
    else if (noDesbalanceado == noDesbalanceado->pai->Fdir)
        noDesbalanceado->pai->Fdir = filho;
    else
        noDesbalanceado->pai->Fesq = filho;
    filho->Fdir = noDesbalanceado;
    noDesbalanceado->pai = filho;
    noDesbalanceado->fb = 0;
    filho->fb = 0;
}