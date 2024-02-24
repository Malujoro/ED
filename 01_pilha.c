#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define TipoPrint "%d"

typedef int TipoItem;

typedef struct
{
    int tamanho;
    TipoItem *estrutura;
} Pilha;

Pilha criarPilha()
{
    Pilha pilha;

    pilha.estrutura = malloc(MAX * sizeof(TipoItem));
    pilha.tamanho = 0;
    
    return pilha;
}

void excluirPilha(Pilha *pilha)
{
    free(pilha->estrutura);
    // *pilha = criarPilha();
    pilha->tamanho = 0;
}

int estaCheia(Pilha pilha)
{
    return(pilha.tamanho == MAX);
}

int estaVazia(Pilha pilha)
{
    return(pilha.tamanho == 0);
}

void inserir(Pilha *pilha, TipoItem item)
{
    if(estaCheia(*pilha))
        printf("\nErro! Pilha está Cheia\n");
    else
    {
        pilha->estrutura[pilha->tamanho] = item;
        pilha->tamanho++;
    }
}

int remover(Pilha *pilha, TipoItem *item)
{
    if(estaVazia(*pilha))
    {
        printf("\nErro! Pilha está vazia\n");
        return 0;
    }

    pilha->tamanho--;
    *item = pilha->estrutura[pilha->tamanho];
    return 1;
}

void imprimir(Pilha pilha)
{
    printf("\nPilha [");
    for(int i = 0; i < pilha.tamanho; i++)
    {
        printf(" ");
        printf(TipoPrint, pilha.estrutura[i]);
    }
    printf(" ]\n");
}

int main()
{
    Pilha pilha1 = criarPilha();
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
                inserir(&pilha1, item);
                break;

            case 2:
                if(remover(&pilha1, &item))
                {
                    printf("\nElemento removido: ");
                    printf(TipoPrint, item);
                    printf("\n");
                }
                break;

            case 3:
                imprimir(pilha1);
                break;     
                  
            case 4:
                printf("\nPilha Excluída\n");
                excluirPilha(&pilha1);
                break;
        }
    }while(op != 0);
    return 0;
}