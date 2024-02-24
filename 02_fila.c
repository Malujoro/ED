#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define TipoPrint "%d"

typedef int TipoItem;

typedef struct
{
    int primeiro, ultimo;
    TipoItem *estrutura;
} Fila;

Fila criarFila()
{
    Fila fila;
    
    fila.estrutura = malloc(MAX * sizeof(TipoItem));
    fila.primeiro = 0;
    fila.ultimo = 0;

    return fila;
}

void excluirFila(Fila *fila)
{
    free(fila->estrutura);
    fila->primeiro = -1;
    fila->ultimo = -1;
}

int estaCheia(Fila fila)
{
    return (fila.ultimo - fila.primeiro == MAX);
}

int estaVazia(Fila fila)
{
    return (fila.primeiro == fila.ultimo);
}

void inserir(Fila *fila, TipoItem dado)
{
    if(estaCheia(*fila))
        printf("\nErro! A fila está cheia\n");
    else
    {
        fila->estrutura[(fila->ultimo) % MAX] = dado;
        fila->ultimo++;
    }
}

int remover(Fila *fila, TipoItem *item)
{
    if(estaVazia(*fila))
    {
        printf("\nErro! A fila está vazia\n");
        return 0;
    }

    *item = fila->estrutura[(fila->primeiro) % MAX];
    fila->primeiro++;
    
    return 1;
}

void imprimir(Fila fila)
{
    printf("\nFila: [ ");
    for(int i = fila.primeiro; i < fila.ultimo; i++)
    {
        printf(TipoPrint, fila.estrutura[i % MAX]);
        printf(" ");
    }
    printf("]\n");
}


int main()
{
    Fila fila1 = criarFila();
    TipoItem dado;
    int op;

    do
    {
        printf("\nMenu");
        printf("\n[1] - Inserir elemento");
        printf("\n[2] - Remover elemento");
        printf("\n[3] - Exibir Fila");
        printf("\n[0] - Sair");
        printf("\nOpção: ");
        scanf(" %d", &op);

        switch(op)
        {
            case 1:
                printf("\nElemento: ");
                scanf(TipoPrint, &dado);
                inserir(&fila1, dado);
                break;

            case 2:
                if(remover(&fila1, &dado))
                {
                    printf("\nElemento removido: ");
                    printf(TipoPrint, dado);
                    printf("\n");
                }
                break;

            case 3:
                imprimir(fila1);
                break;
        }
    }while(op != 0);
    return 0;
}