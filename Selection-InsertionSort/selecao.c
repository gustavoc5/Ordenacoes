#include <stdio.h>
#include <stdlib.h>
#include "selecao.h"

// função responsável por 
int geraAleatorios(char *nomeArquivo, int qtd, int semente)
{
    if (qtd <= 0)
    {
        return 1;
    }
    // abertura do arquivo para escrita (write)
    FILE *arq = fopen(nomeArquivo, "w");
    if (arq == NULL)
    {
        return 1;
    }
    // inicialização da semente
    srand(semente);
    // preenchimento do arquivo com os números aleatórios
    for (int i = 0; i < qtd; i++)
    {
        fprintf(arq, "%d\n", rand() % 1000);
    }
    fclose(arq);
    return 0;
}
// função que lê o arquivo
int *leArquivo(char *nomeArquivo, int qtd)
{
    // abertura do arquivo em modo de leitura (read)
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL)
    {
        return NULL;
    }
    // alocação dinâmica do vetor de inteiros
    int *vet = (int *)malloc(qtd * sizeof(int));
    if (vet == NULL)
    {
        fclose(arq);
        return NULL;
    }
    // leitura dos valores presentes no arquivo com destino ao vetor previamente alocado
    for (int i = 0; i < qtd; i++)
    {
        if (fscanf(arq, "%d", &vet[i]) != 1)
        {
            fclose(arq);
            return NULL;
        }
    }
    fclose(arq);
    return vet;
}

// função responsável por ordenar o vetor por meio do método seleção
void selecao(int *vet, int tam)
{
    int marcador = 0;
    int menor;
    int aux;
    int pos;
    // ordenação acaba quando o marcador chega na última posição do vetor
    while (marcador < tam - 1)
    {
        // atribui o menor valor a posição do marcador e salva a posição atual
        menor = vet[marcador];
        pos = marcador;
        // percorre o vetor
        for (int i = marcador + 1; i < tam; i++)
        {
            // compara se o elemento atual é menor que o anteriormente definido
            if (vet[i] < menor)
            {
                // em caso positivo, atualiza-se as variáveis
                menor = vet[i];
                pos = i;
            }
        }
        // se a posição do menor elemento for diferente do marcador, é realizada a troca entre eles
        if (pos != marcador)
        {
            aux = vet[marcador];
            vet[marcador] = vet[pos];
            vet[pos] = aux;
        }
        // acrescenta-se o marcador com o intuito de chegar ao fim do vetor
        marcador++;
    }
}
// função responsável por ordenar o vetor por meio do método inserção
void insercao(int *vet, int tam)
{
    int marcador = 0;
    int aux;
    int pos;
    // marcador é iniciado na posição 1 para comparar 
    for (marcador = 1; marcador < tam; marcador++)
    {
        pos = marcador - 1; // posição onde o valor temporário deve ser inserido posteriormente
        aux = vet[marcador]; // valor temporário
        // percorre o vetor enquanto a posição onde aux deve ser inserido for maior que 0 e o valor temporário é menor que o valor da posição atual
        while (aux < vet[pos] && pos >= 0)
        {
            // move o valor temporário uma posição a frente e decrementa a posição
            vet[pos + 1] = vet[pos];
            pos--;
        }
        // por fim o valor é inserido na posição correta
        vet[pos + 1] = aux;
    }
}
// função para busca de um valor em um vetor ordenado
void buscaBinaria(int *vet, int inicio, int fim, int valor, int *res)
{
    int meio;
    // a cada chamada o número de chamadas armazenado em res[1] é incrementado
    res[1]++;
    // caso de parada
    if (inicio > fim)
    {
        return;
    }
    // define o meio do vetor para realização da busca binária
    meio = (inicio + fim) / 2;
    // ocorre quando o valor é encontrado no vetor
    if (vet[meio] == valor)
    {
        res[0] = 1;
        return;
    }
    // caso o elemento do meio do vetor seja menor que o valor procurado, chama a função novamente direcionando a procura para o seu lado direito
    else if (vet[meio] < valor)
    {
        buscaBinaria(vet, meio + 1, fim, valor, res);
    }
    // por fim restou o caso em que o valor do meio do vetor é maior que o valor procurado, portanto direciona a procura para o lado direito do vetor
    else
    {
        buscaBinaria(vet, inicio, meio - 1, valor, res);
    }
}
// função que imprime o vetor ordenado da forma anteriormente definida
void imprimeVet(int *vet, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}