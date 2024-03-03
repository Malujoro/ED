// Grafo Simples Direcionado Ponderado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRO -1
#define TRUE 1
#define FALSE 0
#define TipoPrint "%s"

typedef char *TipoItem;

typedef struct No
{
    TipoItem valor;
    struct No *proximo;
} No;

typedef struct
{
    No *primeiro;
    No *ultimo;
} Fila;

typedef struct
{
    int arestaNula;
    int maxVertices;
    int numVertices;
    TipoItem *vertices;
    int **matrizAdjacencias;
    int *marcador;
} Grafo;

////////////////////////////////////////////////////////

No *criarFila()
{
    No *fila = (No *)malloc(sizeof(No));
    return fila;
}

void excluirFila(Fila *fila)
{
    No *aux;

    while(fila->primeiro != NULL)
    {
        aux = fila->primeiro;
        fila->primeiro = fila->primeiro->proximo;
        free(aux);
    }
    fila->ultimo = NULL;
}

int estaCheiaFila()
{
    No *aux = criarFila();
    if(aux == NULL)
        return 1;
    
    free(aux);
    return 0;
}

int estaVaziaFila(Fila *fila)
{
    return (fila->primeiro == NULL);
}

void inserirFila(Fila *fila, TipoItem dado)
{
    if(estaCheiaFila())
        printf("\nErro! Fila está cheia\n");
    else
    {
        No *aux = criarFila();
        aux->valor = dado;
        aux->proximo = NULL;

        if(fila->primeiro == NULL)
            fila->primeiro = aux;
        else
            fila->ultimo->proximo = aux;
        
        fila->ultimo = aux;
    }
}

int removerFila(Fila *fila, TipoItem *dado)
{
    if(estaVaziaFila(fila))
    {
        printf("\nErro! Fila está vazia\n");
        return 0;
    }

    No *aux = fila->primeiro;
    *dado = aux->valor;
    fila->primeiro = fila->primeiro->proximo;
    free(aux);

    if(fila->primeiro == NULL)
        fila->ultimo = NULL;

    return 1;
}

void imprimirFila(Fila fila)
{
    No *aux = fila.primeiro;

    printf("\nFila: [");
    while(aux != NULL)
    {
        printf(" ");
        printf(TipoPrint, aux->valor);
        aux = aux->proximo;
    }
    printf(" ]\n");
}

////////////////////////////////////////////////////////

No *criarPilha()
{
    No *pilha = (No *) malloc(sizeof(No));
    pilha->proximo = NULL;
    return pilha;
}

void excluirPilha(No **ultimo)
{
    No *aux;
    while(*ultimo != NULL)
    {
        aux = *ultimo;
        *ultimo = (*ultimo)->proximo;
        free(aux);
    }
}

int estaVaziaPilha(No *ultimo)
{
    return (ultimo == NULL);
}

int estaCheiaPilha()
{
    No *aux = criarPilha();
    
    if(aux == NULL)
        return 1;
    
    free(aux);
    return 0;
}

void inserirPilha(No **ultimo, TipoItem dado)
{
    if(estaCheiaPilha())
        printf("\nErro! Pilha está cheia\n");
    else
    {
        No *aux = criarPilha();
        aux->valor = dado;
        aux->proximo = *ultimo;
        *ultimo = aux;
    }
}

int removerPilha(No **ultimo, TipoItem *dado)
{
    if(estaVaziaPilha(*ultimo))
    {
        printf("\nErro! Pilha está vazia\n");
        return 0;
    }

    No *aux = *ultimo;
    *dado = (*ultimo)->valor;
    *ultimo = (*ultimo)->proximo;
    free(aux);
    return 1;
}

void imprimirPilha(No *ultimo)
{
    No *aux = ultimo;

    printf("\nPilha: [ ");
    while(aux != NULL)
    {
        printf(TipoPrint, aux->valor);
        printf(" ");
        aux = aux->proximo;
    }
    printf("]\n");
}

////////////////////////////////////////////////////////

void limparMarcador(Grafo *grafo)
{
    for(int i = 0; i < grafo->maxVertices; i++)
        grafo->marcador[i] = FALSE;
}

Grafo criarGrafo(int maxVertices, int arestaNula)
{
    Grafo grafo;
    grafo.arestaNula = arestaNula;
    grafo.maxVertices = maxVertices;
    grafo.numVertices = 0;

    grafo.vertices = (TipoItem *) malloc(maxVertices * sizeof(TipoItem));
    for(int i = 0; i < maxVertices; i++)
        grafo.vertices[i] = (TipoItem) malloc(maxVertices * sizeof(char));

    grafo.marcador = (int *) malloc(maxVertices * sizeof(int));
    limparMarcador(&grafo);

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

    free(grafo->marcador);

    for(int i = 0; i < grafo->maxVertices; i++)
        free(grafo->matrizAdjacencias[i]);
    free(grafo->matrizAdjacencias);
        
    grafo->maxVertices = 0;
    grafo->numVertices = 0;
}

int obterIndice(Grafo grafo, TipoItem item)
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

void inserirVertice(Grafo *grafo, TipoItem item)
{
    if(estaCheio(*grafo))
        printf("\nErro! Máximo de vértices atingido\n");
    else
    {
        strcpy(grafo->vertices[grafo->numVertices], item);
        (grafo->numVertices)++;
    }
}

void inserirAresta(Grafo *grafo, TipoItem noSaida, TipoItem noEntrada, int peso)
{
    int i = obterIndice(*grafo, noSaida);
    int j = obterIndice(*grafo, noEntrada);

    if(i != ERRO && j != ERRO)
        grafo->matrizAdjacencias[i][j] = peso;
    else
        printf("\nErro! Vértice inválido\n");
}

int obterPeso(Grafo grafo, TipoItem noSaida, TipoItem noEntrada)
{
    int i = obterIndice(grafo, noSaida);
    int j = obterIndice(grafo, noEntrada);
    
    if(i != ERRO && j != ERRO)
        return grafo.matrizAdjacencias[i][j];

    printf("\nErro! Vértice inválido\n");
    return ERRO;
}

int obterGrau(Grafo grafo, TipoItem item)
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

void buscaLargura(Grafo *grafo, TipoItem origem, TipoItem destino)
{
    // Cria as variáveis que vão conter as posições dos itens de Origem, Destino e Removido
    int posOrigem = obterIndice(*grafo, origem);
    int posDestino = obterIndice(*grafo, destino);
    int posItem;

    // Inicia limpando os marcadores
    limparMarcador(grafo);

    // Se os índices forem válidos, fará a busca
    if(posOrigem != ERRO && posDestino != ERRO)
    {
        // Cria a variável para Fila
        Fila fila;
        fila.primeiro = NULL;
        fila.ultimo = NULL;
        // Cria a variável para conter o item analisado
        TipoItem item;

        // Insere o primeiro item na fila [Origem]
        inserirFila(&fila, origem);
        // Define o marcador para esse item como TRUE
        grafo->marcador[posOrigem] = TRUE;
        do
        {
            // Remove um item da Fila
            removerFila(&fila, &item);
            // Verifica se o item removido é o buscado
            if(strcmp(destino, item) == 0)
            {
                printf("\nVisitando: %s\n", item);
                printf("\nCaminho encontrado\n");
                return;
            }

            // Verifica se o item atual tem "vértices" a serem seguidos
            posItem = obterIndice(*grafo, item);
            printf("\nVisitando: %s\n", item);
            for(int i = 0; i < grafo->numVertices; i++)
            {
                // Caso tenham vértices disponíveis (que ainda não foram percorridos), adiciona na Fila
                if(grafo->marcador[i] == FALSE && grafo->matrizAdjacencias[posItem][i] != grafo->arestaNula)
                {
                    printf("\nEnfileirando: %s\n", grafo->vertices[i]);
                    inserirFila(&fila, grafo->vertices[i]);
                    grafo->marcador[i] = TRUE;
                }
            }
            // Caso a fila esteja vazia, significa que percorreu todos os caminhos e não encontrou um válido
            if(estaVaziaFila(&fila))
            {
                printf("\nCaminho indisponível\n");
                return;
            }
        }while(strcmp(destino, item) != 0);
    }
    printf("\nErro! Índices inválidos\n");
}

void buscaProfundidade(Grafo *grafo, TipoItem origem, TipoItem destino)
{
    int posOrigem = obterIndice(*grafo, origem);
    int posDestino = obterIndice(*grafo, destino);
    int posItem;

    if(posOrigem != ERRO && posDestino != ERRO)
    {
        No *pilha = NULL;
        TipoItem item;
        limparMarcador(grafo);

        inserirPilha(&pilha, origem);
        grafo->marcador[posOrigem] = TRUE;

        do
        {
            removerPilha(&pilha, &item);
            if(strcmp(destino, item) == 0)
            {
                printf("\nVisitando: %s\n", item);
                printf("\nCaminho encontrado\n");
                return;
            }

            posItem = obterIndice(*grafo, item);
            printf("\nVisitando: %s\n", item);
            for(int i = 0; i < grafo->numVertices; i++)
            {
                if(grafo->marcador[i] == FALSE && grafo->matrizAdjacencias[posItem][i] != grafo->arestaNula)
                {
                    printf("\nEmpilhando: %s\n", grafo->vertices[i]);
                    inserirPilha(&pilha, grafo->vertices[i]);
                    grafo->marcador[i] = TRUE;
                }
            }

            if(estaVaziaPilha(pilha))
            {
                printf("\nCaminho não encontrado\n");
                return;
            }
        }while(strcmp(destino, item) != 0);
    }
    printf("\nErro! Índices inválidos\n");
}

////////////////////////////////////////////////////////

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
    char vertice[100];
    char vertice2[100];
    
    do
    {
        printf("\nMenu");
        printf("\n[1] - Inserir Vértice");
        printf("\n[2] - Inserir Aresta");
        printf("\n[3] - Grau de um Vértice");
        printf("\n[4] - Peso de uma Aresta");
        printf("\n[5] - Matriz de Adjacências");
        printf("\n[6] - Lista de Vértices");
        printf("\n[7] - Busca por Largura");
        printf("\n[8] - Busca por Profundidade");
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
            case 7:
                printf("\nVértice Saída: ");
                scanf(" %[^\n]s", vertice);
                printf("\nVértice Entrada: ");
                scanf(" %[^\n]s", vertice2);
                buscaLargura(&grafo, vertice, vertice2);
                break;
            case 8:
                printf("\nVértice Saída: ");
                scanf(" %[^\n]s", vertice);
                printf("\nVértice Entrada: ");
                scanf(" %[^\n]s", vertice2);
                buscaProfundidade(&grafo, vertice, vertice2);
                break;
        }
    }while(op != 0);

    return 0;
}