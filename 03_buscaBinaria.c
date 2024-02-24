#include <stdio.h>

int main()
{
    int vetor[] = {1, 2, 4, 7, 9, 10, 13, 18, 19, 27, 30};
    int tamanho = 11;
    int chave, encontrou = 1, pos;
    int inicio = 0, fim = tamanho-1, meio;

    printf("Valor buscado: ");
    scanf(" %d", &chave);

    if(chave == vetor[inicio])
        pos = inicio;
    else if(chave == vetor[fim])
        pos = fim;
    else
    {
        encontrou = 0;
        do
        {
            meio = (inicio + fim)/2;

            if(chave == vetor[meio])
            {
                pos = meio;
                encontrou = 1;
            }
            else if(chave < vetor[meio])
                fim = meio;
            else if(chave > vetor[meio])
                inicio = meio;
        }while(fim - inicio != 1 && !encontrou);
    }

    if(encontrou)
        printf("\n%d Encontrado! vetor[%d]\n", vetor[pos], pos);
    else
        printf("\nValor %d não encontrado\n", chave);
    return 0;
}