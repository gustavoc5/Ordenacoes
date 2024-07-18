#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main() {
    avl *arv;
    char nomeArquivo[30];
    int res;
    scanf("%s", nomeArquivo);
    arv = criaArvore();
    res = processaCarga(arv, nomeArquivo, 1);
    if(res == -2)
    {
        printf("Erro ao abrir o arquivo de insercao");
        return 0;
    }
    if(res == 0)
    {
        printf("Erro na insercao");
        return 0;
    }
    imprimePreOrdem(getRaiz(arv));
    printf("%d\n", getNumElementos(arv));
    scanf("%s", nomeArquivo);
    res = processaCarga(arv, nomeArquivo, 2);
    if(res == -2)
    {
        printf("Erro ao abrir o arquivo de remocao");
        return 0;
    }
    if(res == 0)
    {
      printf("Erro na remocao");
      return 0;
    }
    imprimePreOrdem(getRaiz(arv));
    printf("%d", getNumElementos(arv));
    free(arv);
    return 1;
}
