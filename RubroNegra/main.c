#include <stdio.h>
#include "rubroNegra.h"

int main() {
    rb *arv;
    char nomeArquivo[30];

    arv = criaArvore();
    scanf("%s", nomeArquivo);
    processaCarga(arv, nomeArquivo, 1);
    imprimePreOrdem(arv, getRaiz(arv));
    printf("%d\n", getNumElementos(arv));
    scanf("%s", nomeArquivo);
    processaCarga(arv, nomeArquivo, 2);
    imprimePreOrdem(arv, getRaiz(arv));
    printf("%d", getNumElementos(arv));
    return 0;
}
