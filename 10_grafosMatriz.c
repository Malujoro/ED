// Grafo Simples Não-Direcionado Ponderado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TipoPrint "%s"
#define ERRO -1

typedef char TipoItem;

typedef struct
{
    int arestaNula;
    int maxVertices;
    int numVertices;
    TipoItem **vertices;
    int **matrizAdjacencias;
} Grafo;

Grafo criarGrafo(int maxVertices, int arestaNula)
{
    Grafo grafo;
    grafo.arestaNula = arestaNula;
    grafo.maxVertices = maxVertices;
    grafo.numVertices = 0;

    grafo.vertices = malloc(maxVertices * sizeof(TipoItem *));
    for(int i = 0; i < maxVertices; i++)
        grafo.vertices[i] = (TipoItem *) malloc(maxVertices * sizeof(TipoItem));

    grafo.matrizAdjacencias = (int **) malloc(maxVertices * sizeof(int *));
    for(int i = 0; i < maxVertices; i++)
        grafo.matrizAdjacencias[i] = (int *) malloc(maxVertices * sizeof(int));

    for(int i = 0; i < maxVertices; i++)
    {
        for(int j = 0; j < maxVertices; j++)
            grafo.matrizAdjacencias[i][j] = arestaNula;
    }

    return grafo;
}

void excluirGrafo(Grafo *grafo)
{
    for(int i = 0; i < grafo->numVertices; i++)
        free(grafo->vertices[i]);
    free(grafo->vertices);

    for(int i = 0; i < grafo->maxVertices; i++)
        free(grafo->matrizAdjacencias[i]);
    free(grafo->matrizAdjacencias);
        
    grafo->maxVertices = 0;
    grafo->numVertices = 0;
}

int obterIndice(Grafo grafo, TipoItem *item)
{
    for(int i = 0; i < grafo.numVertices; i++)
    {
        if(strcmp(grafo.vertices[i], item) == 0)
            return i;
    }
    return ERRO;
}

int estaCheio(Grafo grafo)
{
    return (grafo.numVertices == grafo.maxVertices);
}

void inserirVertice(Grafo *grafo, TipoItem *item)
{
    if(estaCheio(*grafo))
        printf("\nErro! Máximo de vértices atingido\n");
    else
    {
        strcpy(grafo->vertices[grafo->numVertices], item);
        (grafo->numVertices)++;
    }
}

void inserirAresta(Grafo *grafo, TipoItem *noSaida, TipoItem *noEntrada, int peso)
{
    int i = obterIndice(*grafo, noSaida);
    int j = obterIndice(*grafo, noEntrada);

    if(i != ERRO && j != ERRO)
    {
        grafo->matrizAdjacencias[i][j] = peso;
        grafo->matrizAdjacencias[j][i] = peso;
    }
    else
        printf("\nErro! Vértice inválido\n");
}

int obterPeso(Grafo grafo, TipoItem *noSaida, TipoItem *noEntrada)
{
    int i = obterIndice(grafo, noSaida);
    int j = obterIndice(grafo, noEntrada);
    
    if(i != ERRO && j != ERRO)
        return grafo.matrizAdjacencias[i][j];

    printf("\nErro! Vértice inválido\n");
    return ERRO;
}

int obterGrau(Grafo grafo, TipoItem *item)
{
    int pos = obterIndice(grafo, item);
    
    if(pos != ERRO)
    {
        int quant = 0;
        for(int i = 0; i < grafo.numVertices; i++)
        {
            if(grafo.matrizAdjacencias[pos][i] != grafo.arestaNula)
                quant++;
        }
        return quant;
    }
    printf("\nErro! Vértice inválido\n");
    return ERRO;
}

void imprimirMatriz(Grafo grafo)
{
    printf("\nMatriz de adjacências\n");
    for(int i = 0; i < grafo.numVertices; i++)
    {
        for(int j = 0; j < grafo.numVertices; j++)
            printf("%d \t ", grafo.matrizAdjacencias[i][j]);

        printf("\n");
    }
}

void imprimirVertices(Grafo grafo)
{
    printf("\nLista de vértices\n");
    for(int i = 0; i < grafo.numVertices; i++)
    {
        printf("%d: ", i);
        printf(TipoPrint, grafo.vertices[i]);
        printf("\n");
    }
}

int main()
{
    int max, nulo;

    printf("\nMáximo de Vértices: ");
    scanf(" %d", &max);

    do
    {
        printf("\nValor Nulo (Diferente de -1): ");
        scanf(" %d", &nulo);
    }while(nulo == -1);

    Grafo grafo = criarGrafo(max, nulo);
    int op, num;
    TipoItem vertice[100];
    TipoItem vertice2[100];
    
    do
    {
        printf("\nMenu");
        printf("\n[1] - Inserir Vértice");
        printf("\n[2] - Inserir Aresta");
        printf("\n[3] - Grau de um Vértice");
        printf("\n[4] - Peso de uma Aresta");
        printf("\n[5] - Matriz de Adjacências");
        printf("\n[6] - Lista de Vértices");
        printf("\n[0] - Sair");
        printf("\nOpção: ");
        scanf(" %d", &op);

        switch(op)
        {
            case 1:
                printf("\nVértice a ser inserido: ");
                scanf(" %[^\n]s", vertice);
                inserirVertice(&grafo, vertice);
                break;
            case 2:
                printf("\nVértice Saída: ");
                scanf(" %[^\n]s", vertice);
                printf("\nVértice Entrada: ");
                scanf(" %[^\n]s", vertice2);
                printf("\nPeso: ");
                scanf(" %d", &num);
                inserirAresta(&grafo, vertice, vertice2, num);
                break;
            case 3:
                printf("\nVértice para calcular o grau: ");
                scanf(" %[^\n]s", vertice);
                num = obterGrau(grafo, vertice);
                if(num != ERRO && num != grafo.arestaNula)
                    printf("\nGrau: %d\n", num);
                break;
            case 4:
                printf("\nVértice Saída: ");
                scanf(" %[^\n]s", vertice);
                printf("\nVértice Entrada: ");
                scanf(" %[^\n]s", vertice2);
                num = obterPeso(grafo, vertice, vertice2);
                if(num != ERRO)
                    printf("\nPeso: %d\n", num);
                break;
            case 5:
                imprimirMatriz(grafo);
                break;
            case 6:
                imprimirVertices(grafo);
                break;
        }
    }while(op != 0);

    return 0;
}