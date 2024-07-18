#include <stdio.h>
#include <stdlib.h>
#include "bolha.h"

int main() {
    char nomeArquivo[30];
    tReturn *rep;
    int cont;

    scanf("%s", nomeArquivo);
    printf("BOLHA\n");
    rep = leArquivo(nomeArquivo);
    if(getErro(rep) == 0)
    {
        cont = bolha(getVet(rep), getTam(rep));
        imprimeVet(getVet(rep), getTam(rep));
        printf("BOLHA realizou %d comparacoes.\n\n", cont);
    }
    else
        trataErro(getErro(rep));

    printf("BOLHA INTELIGENTE\n");
    rep = leArquivo(nomeArquivo);
    if(getErro(rep) == 0)
    {
        cont = bolhaInteligente(getVet(rep), getTam(rep));
        imprimeVet(getVet(rep), getTam(rep));
        printf("BOLHA INTELIGENTE realizou %d comparacoes.\n", cont);
    }
    else
        trataErro(getErro(rep));

    free(rep);

    return 0;
}
