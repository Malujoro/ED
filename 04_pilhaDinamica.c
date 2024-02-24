#include <stdio.h>
#include <stdlib.h>

#define TipoPrint "%d"

typedef int TipoItem;

typedef struct PilhaDinamica
{
    TipoItem valor;
    struct PilhaDinamica *proximo;
} PilhaDinamica;

PilhaDinamica *criarPilha()
{
    PilhaDinamica *pilha = malloc(sizeof(PilhaDinamica));
    pilha->proximo = NULL;
    return pilha;
}

void excluirPilha(PilhaDinamica **ultimo)
{
    PilhaDinamica *aux;
    while(*ultimo != NULL)
    {
        aux = *ultimo;
        *ultimo = (*ultimo)->proximo;
        free(aux);
    }
}

int estaVazia(PilhaDinamica *ultimo)
{
    return (ultimo == NULL);
}

int estaCheia()
{
    PilhaDinamica *aux = criarPilha();
    
    if(aux == NULL)
        return 1;
    
    free(aux);
    return 0;
}

void inserir(PilhaDinamica **ultimo, TipoItem dado)
{
    if(estaCheia())
        printf("\nErro! Pilha está cheia\n");
    else
    {
        PilhaDinamica *aux = criarPilha();
        aux->valor = dado;
        aux->proximo = *ultimo;
        *ultimo = aux;
    }
}

int remover(PilhaDinamica **ultimo, TipoItem *dado)
{
    if(estaVazia(*ultimo))
    {
        printf("\nErro! Pilha está vazia\n");
        return 0;
    }

    PilhaDinamica *aux = *ultimo;
    *dado = (*ultimo)->valor;
    *ultimo = (*ultimo)->proximo;
    free(aux);
    return 1;
}

void imprimir(PilhaDinamica *ultimo)
{
    PilhaDinamica *aux = ultimo;

    printf("\nPilha: [ ");
    while(aux != NULL)
    {
        printf(TipoPrint, aux->valor);
        printf(" ");
        aux = aux->proximo;
    }
    printf("]\n");
}

int main()
{
    PilhaDinamica *ultimo;
    TipoItem item;
    int op;

    do
    {
        printf("\nMenu");
        printf("\n[1] - Inserir elemento");
        printf("\n[2] - Remover elemento");
        printf("\n[3] - Exibir Pilha");
        printf("\n[4] - Excluir Pilha");
        printf("\n[0] - Sair");
        printf("\nOpção: ");
        scanf(" %d", &op);

        switch(op)
        {
            case 1:
                printf("\nElemento: ");
                scanf(TipoPrint, &item);
                inserir(&ultimo, item);
                break;

            case 2:
                if(remover(&ultimo, &item))
                {
                    printf("\nElemento removido: ");
                    printf(TipoPrint, item);
                    printf("\n");
                }
                break;

            case 3:
                imprimir(ultimo);
                break;

            case 4:
                printf("\nPilha Excluída\n");
                excluirPilha(&ultimo);
                break;
        }
    }while(op != 0);
    return 0;
}