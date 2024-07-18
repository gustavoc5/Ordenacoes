#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

int main() {
    //DECLARAÇÃO DE VARIÁVEIS
    tVet *res;
    char nomeArquivo[80];

    scanf("%s", nomeArquivo);

    res = leArquivo(nomeArquivo);
    imprimeVet(getVet(res), getVetTam(res));
    printf("\n");
    mergesort(getVet(res),0, getVetTam(res)-1);
    imprimeVet(getVet(res), getVetTam(res));
    free(res);
    return 0;
}
