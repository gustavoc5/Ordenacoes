#include <stdio.h>
#include <stdlib.h>
#include "arvorebinaria.h"

int main() {
    char nomeArquivo[30];
    arvore *arv;
    int elemRem;

    scanf("%s", nomeArquivo);

    arv = criaArvore();
    processaCarga(arv, nomeArquivo);
    imprimePreOrdem(getRaiz(arv));
    printf("\n%d\n", getNumElementos(arv));

    scanf("%d", &elemRem);
    removeNo(arv, elemRem);

    scanf("%d", &elemRem);
    removeNo(arv, elemRem);

    scanf("%d", &elemRem);
    removeNo(arv, elemRem);

    scanf("%d", &elemRem);
    removeNo(arv, elemRem);

    imprimePreOrdem(getRaiz(arv));
    printf("\n%d\n", getNumElementos(arv));

    scanf("%d", &elemRem);
    if (removeNo(arv, elemRem) == -1)
        printf("Elemento não esta na arvore");

    free(arv);

}
