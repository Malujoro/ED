#include <stdio.h>
#include <stdlib.h>

#define TipoPrint  "%d"

typedef int TipoItem;

typedef struct FilaDinamica
{
    TipoItem valor;
    struct FilaDinamica *proximo;
} FilaDinamica;

typedef struct
{
    FilaDinamica *primeiro;
    FilaDinamica *ultimo;
} Fila;

FilaDinamica *criarFila()
{
    FilaDinamica *fila = malloc(sizeof(FilaDinamica));
    return fila;
}

void excluirFila(Fila *fila)
{
    FilaDinamica *aux;

    while(fila->primeiro != NULL)
    {
        aux = fila->primeiro;
        fila->primeiro = fila->primeiro->proximo;
        free(aux);
    }
    fila->ultimo = NULL;
}

int estaCheia()
{
    FilaDinamica *aux = criarFila();
    if(aux == NULL)
        return 1;
    
    free(aux);
    return 0;
}

int estaVazia(Fila *fila)
{
    return (fila->primeiro == NULL);
}

void inserir(Fila *fila, TipoItem dado)
{
    if(estaCheia())
        printf("\nErro! Fila está cheia\n");
    else
    {
        FilaDinamica *aux = criarFila();
        aux->valor = dado;
        aux->proximo = NULL;

        if(fila->primeiro == NULL)
            fila->primeiro = aux;
        else
            fila->ultimo->proximo = aux;
        
        fila->ultimo = aux;
    }
}

int remover(Fila *fila, TipoItem *dado)
{
    if(estaVazia(fila))
    {
        printf("\nErro! Fila está vazia\n");
        return 0;
    }

    FilaDinamica *aux = fila->primeiro;
    *dado = aux->valor;
    fila->primeiro = fila->primeiro->proximo;
    free(aux);

    if(fila->primeiro == NULL)
        fila->ultimo = NULL;

    return 1;
}

void imprimir(Fila fila)
{
    FilaDinamica *aux = fila.primeiro;

    printf("\nFila: [");
    while(aux != NULL)
    {
        printf(" ");
        printf(TipoPrint, aux->valor);
        aux = aux->proximo;
    }
    printf(" ]\n");
}

int main()
{
    Fila fila;
    fila.primeiro = NULL;
    fila.ultimo = NULL;
    TipoItem dado;
    int op;

    do
    {
        printf("\nMenu");
        printf("\n[1] - Inserir Elemento");
        printf("\n[2] - Remover Elemento");
        printf("\n[3] - Exibir Fila");
        printf("\n[4] - Excluir Fila");
        printf("\n[0] - Sair");
        printf("\nOpção: ");
        scanf(" %d", &op);

        switch(op)
        {
            case 1:
                printf("\nElemento: ");
                scanf(TipoPrint, &dado);
                inserir(&fila, dado);
                break;

            case 2:
                if(remover(&fila, &dado))
                {
                    printf("\nElemento removido: ");
                    printf(TipoPrint, dado);
                    printf("\n");
                }
                break;
                
            case 3:
                imprimir(fila);
                break;
                
            case 4:
                excluirFila(&fila);
                break;
        }
    }while(op != 0);

    return 0;
}