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
        removerBusca(alunoSucessor, (*noAtual)->filhoDireita);
    }

}

int removerBusca(Aluno aluno, No **noAtual)
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
    return 0;
}

void remover(ArvoreBinariaBusca *arvore, Aluno aluno)
{
    if(estaVazia(*arvore))
        printf("\nErro! A árvore está vazia\n");
    else
    {
        No *raiz = arvore->raiz;
        if(removerBusca(aluno, &raiz))
            deletarNo(&raiz);
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