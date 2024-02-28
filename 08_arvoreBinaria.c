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

}

void remover(ArvoreBinariaBusca *arvore, Aluno aluno)
{
    
}

int buscar(ArvoreBinariaBusca *arvore, Aluno *aluno)
{

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
    ArvoreBinariaBusca arvore;

    return 0;
}