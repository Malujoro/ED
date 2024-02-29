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
    arvore.raiz = criarNo();
    return arvore;
}

void deletarArvore(No *noAtual)
{

}

int estaVazia(ArvoreBinariaBusca arvore)
{
    return (arvore.raiz == VAZIO);
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
                else if(aluno.ra >= aux->aluno.ra)
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

void remover(ArvoreBinariaBusca *arvore, Aluno aluno)
{
    if(estaVazia(*arvore))
        printf("\nErro! A árvore está vazia\n");
    else
    {
        No *aux = arvore->raiz;

        while(aux->aluno.ra != VAZIO && aux->aluno.ra != aluno.ra)
        {
            if(aluno.ra < aux->aluno.ra)
                aux = aux->filhoEsquerda;
            else if(aluno.ra >= aux->aluno.ra)
                aux = aux->filhoDireita;
        }
        if(aux->aluno.ra == VAZIO)
            printf("\nErro! Elemento não encontrado\n");
        else
        {

        }
    }
}

int buscar(ArvoreBinariaBusca *arvore, Aluno *aluno)
{
    No *aux = arvore->raiz;
    
    while(aux->aluno.ra != aluno->ra)
    {
        
        if(aluno->ra < aux->aluno.ra)
        {
            if(aux->filhoEsquerda == NULL)
                return 0;
            else
                aux = aux->filhoEsquerda;
        }
        else if(aluno->ra >= aux->aluno.ra)
        {
            if(aux->filhoDireita == NULL)
                return 0;
            else
                aux = aux->filhoDireita;
        }
    }

    *aluno = aux->aluno;
    return 1;
}

void imprimirPreOrdem(No *noAtual)
{

}

void imprimirEmOrdem(No *noAtual)
{

}

void imprimirPosOrdem(No *noAtual)
{

}

int main()
{
    ArvoreBinariaBusca arvore = criarArvore();

    return 0;
}