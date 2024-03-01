#include <stdio.h>
#include <stdlib.h>

#define VAZIO -1

typedef struct
{
    char nome[100];
    int ra;
} Aluno;

typedef struct No
{
    Aluno aluno;
    struct No *filhoEsquerda;
    struct No *filhoDireita;
} No;

typedef struct
{
    No *raiz;
} ArvoreBinariaBusca;

int removerBusca(Aluno aluno, No **noAtual);

Aluno criarAluno()
{
    Aluno aluno;
    aluno.nome[0] = ' ';
    aluno.ra = VAZIO;
    return aluno;
}

No *criarNo()
{
    No *no = malloc(sizeof(No));
    no->aluno = criarAluno();
    no->filhoEsquerda = NULL;
    no->filhoDireita = NULL;
    return no;
}

ArvoreBinariaBusca criarArvore()
{
    ArvoreBinariaBusca arvore;
    arvore.raiz = NULL;
    return arvore;
} 

void deletarArvore(No *noAtual)
{
    if(noAtual != NULL)
    {
        deletarArvore(noAtual->filhoEsquerda);
        deletarArvore(noAtual->filhoDireita);
        
        free(noAtual);
    }
}

int estaVazia(ArvoreBinariaBusca arvore)
{
    return (arvore.raiz == NULL);
}

int estaCheia()
{
    No *no = criarNo();
    
    if(no == NULL)
        return 1;
    
    free(no);
    return 0;
}

void inserir(ArvoreBinariaBusca *arvore, Aluno aluno)
{
    if(estaCheia())
        printf("\nErro! A árvore está cheia\n");
    else
    {
        No *noNovo = criarNo();
        noNovo->aluno = aluno;

        if(arvore->raiz == NULL)
            arvore->raiz = noNovo;
        else
        {
            No *aux = arvore->raiz;
            while(aux != NULL)
            {
                if(aluno.ra < aux->aluno.ra)
                {
                    if(aux->filhoEsquerda == NULL)
                    {
                        aux->filhoEsquerda = noNovo;
                        return;
                    }
                    else
                        aux = aux->filhoEsquerda;
                }
                else if(aluno.ra > aux->aluno.ra)
                {
                    if(aux->filhoDireita == NULL)
                    {
                        aux->filhoDireita = noNovo;
                        return;
                    }
                    else
                        aux = aux->filhoDireita;
                }
            }
        }
    }
}

Aluno obterSucessor(No *aux)
{
    Aluno alunoSucessor;

    aux = aux->filhoDireita;

    while(aux->filhoEsquerda != NULL)
        aux = aux->filhoEsquerda;

    alunoSucessor = aux->aluno;
    return alunoSucessor;
}

void deletarNo(No **noAtual)
{
    No *aux = *noAtual;

    if((*noAtual)->filhoEsquerda == NULL)
    {
        *noAtual = (*noAtual)->filhoDireita;
        free(aux);
    }
    else if((*noAtual)->filhoDireita == NULL)
    {
        *noAtual = (*noAtual)->filhoEsquerda;
        free(aux);
    }
    else
    {
        Aluno alunoSucessor = obterSucessor(*noAtual);
        (*noAtual)->aluno = alunoSucessor;
        removerBusca(alunoSucessor, &(*noAtual)->filhoDireita);
    }

}

int removerBusca(Aluno aluno, No **noAtual)
{
    if(*noAtual != NULL)
    {
        if(aluno.ra < (*noAtual)->aluno.ra)
            removerBusca(aluno, &((*noAtual)->filhoEsquerda));
        else if(aluno.ra > (*noAtual)->aluno.ra)
            removerBusca(aluno, &((*noAtual)->filhoDireita));
        else
        {
            deletarNo(noAtual);
            return 1;
        }
    }
    return 0;
}

void remover(ArvoreBinariaBusca *arvore, Aluno aluno)
{
    if(estaVazia(*arvore))
        printf("\nErro! A árvore está vazia\n");
    else
    {
        if(removerBusca(aluno, &(arvore->raiz)))
            printf("\nElemento removido!\n");
        else
            printf("\nElemento não encontrado\n");
    }
}

int buscar(ArvoreBinariaBusca *arvore, Aluno *aluno)
{
    No *aux = arvore->raiz;
    
    while(aux != NULL)
    {
        
        if(aluno->ra < aux->aluno.ra)
            aux = aux->filhoEsquerda;
        else if(aluno->ra > aux->aluno.ra)
            aux = aux->filhoDireita;
        else
        {
            *aluno = aux->aluno;
            return 1;
        }
    }
    return 0;
}

void imprimirPreOrdem(No *noAtual)
{
    if(noAtual != NULL)
    {
        printf("\n%s : %d\n", noAtual->aluno.nome, noAtual->aluno.ra);

        imprimirPreOrdem(noAtual->filhoEsquerda);
        imprimirPreOrdem(noAtual->filhoDireita);
    }
}

void imprimirEmOrdem(No *noAtual)
{
    if(noAtual != NULL)
    {
        imprimirEmOrdem(noAtual->filhoEsquerda);

        printf("\n%s : %d\n", noAtual->aluno.nome, noAtual->aluno.ra);

        imprimirEmOrdem(noAtual->filhoDireita);
    }
}

void imprimirPosOrdem(No *noAtual)
{
    if(noAtual != NULL)
    {
        imprimirPosOrdem(noAtual->filhoEsquerda);
        imprimirPosOrdem(noAtual->filhoDireita);
        
        printf("\n%s : %d\n", noAtual->aluno.nome, noAtual->aluno.ra);
    }
}

void leiaRA(char *texto, int *dado)
{
    printf("%s", texto);
    scanf(" %d", dado);
}

int main()
{
    ArvoreBinariaBusca arvore = criarArvore();
    Aluno aluno;
    int op;

    do
    {
        printf("\nMenu");
        printf("\n[1] - Inserir aluno");
        printf("\n[2] - Buscar aluno");
        printf("\n[3] - Remover aluno");
        printf("\n[4] - Imprimir alunos em pré ordem");
        printf("\n[5] - Imprimir alunos em ordem");
        printf("\n[6] - Imprimir alunos em pós ordem");
        printf("\n[7] - Recriar árvore");
        printf("\n[0] - Sair");
        printf("\nOpção: ");
        scanf(" %d", &op);

        switch(op)
        {
            case 1:
                leiaRA("\nRA: ", &aluno.ra);
                printf("\nNome: ");
                scanf(" %[^\n]s", aluno.nome);
                inserir(&arvore, aluno);
                break;
            case 2:
                leiaRA("\nRA do aluno a ser buscado: ", &aluno.ra);
                if(buscar(&arvore, &aluno))
                {
                    printf("\nAluno encontrado: ");
                    printf("\nRA: %d", aluno.ra);
                    printf("\nNome: %s\n", aluno.nome);
                }
                else
                    printf("\nAluno NÃO encontrado\n");
                break;
            case 3:
                leiaRA("\nRA do aluno a ser removido: ", &aluno.ra);
                remover(&arvore, aluno);
                break;
            case 4:
                imprimirPreOrdem(arvore.raiz);
                break;
            case 5:
                imprimirEmOrdem(arvore.raiz);
                break;
            case 6:
                imprimirPosOrdem(arvore.raiz);
                break;
            case 7:
                deletarArvore(arvore.raiz);
                arvore = criarArvore();
                break;
        }
    }while(op != 0);

    return 0;
}