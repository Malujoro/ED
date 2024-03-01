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
    int fatorB;
} No;

typedef struct
{
    No *raiz;
} ArvoreBinariaBusca;

void removerBusca(Aluno aluno, No **noAtual, int *diminuiu);

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
    no->fatorB = 0;
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

void rotacaoDireita(No **pai)
{
    No *novoPai = (*pai)->filhoEsquerda;
    (*pai)->filhoEsquerda = novoPai->filhoDireita;
    novoPai->filhoDireita = *pai;
    *pai = novoPai;
}

void rotacaoEsquerda(No **pai)
{
    No *novoPai = (*pai)->filhoDireita;
    (*pai)->filhoDireita = novoPai->filhoEsquerda;
    novoPai->filhoEsquerda = *pai;
    *pai = novoPai;
}

void rotacaoDireitaEsquerda(No **pai)
{
    No *filho = (*pai)->filhoDireita;
    rotacaoDireita(&filho);
    (*pai)->filhoDireita = filho;
    rotacaoEsquerda(pai);
}

void rotacaoEsquerdaDireita(No **pai)
{
    No *filho = (*pai)->filhoEsquerda;
    rotacaoEsquerda(&filho);
    (*pai)->filhoEsquerda = filho;
    rotacaoDireita(pai);
}

void realizarRotacao(No **pai)
{
    No *filho;
    No *neto;

    if((*pai)->fatorB == -2)
    {
        filho = (*pai)->filhoEsquerda;
    
        if(filho->fatorB == -1)
        {
            (*pai)->fatorB = 0;
            filho->fatorB = 0;
            rotacaoDireita(pai);
        }
        else if(filho->fatorB == 0)
        {
            (*pai)->fatorB = -1;
            filho->fatorB = 1;
            rotacaoDireita(pai);
        }
        else if(filho->fatorB == 1)
        {
            neto = filho->filhoDireita;
            if(neto->fatorB == -1)
            {
                (*pai)->fatorB = 1;
                filho->fatorB = 0;
            }
            else if(neto->fatorB == 0)
            {
                (*pai)->fatorB = 0;
                filho->fatorB = 0;
            }
            else if(neto->fatorB == 1)
            {
                (*pai)->fatorB = 0;
                filho->fatorB = -1;
            }
            neto->fatorB = 0;
            rotacaoEsquerdaDireita(pai);
        }
    }
    else if((*pai)->fatorB == 2)
    {
        filho = (*pai)->filhoDireita;
    
        if(filho->fatorB == 1)
        {
            (*pai)->fatorB = 0;
            filho->fatorB = 0;
            rotacaoEsquerda(pai);
        }
        else if(filho->fatorB == 0)
        {
            (*pai)->fatorB = 1;
            filho->fatorB = -1;
            rotacaoEsquerda(pai);
        }
        else if(filho->fatorB == -1)
        {
            neto = filho->filhoEsquerda;
            if(neto->fatorB == -1)
            {
                (*pai)->fatorB = 0;
                filho->fatorB = 1;
            }
            else if(neto->fatorB == 0)
            {
                (*pai)->fatorB = 0;
                filho->fatorB = 0;
            }
            else if(neto->fatorB == 1)
            {
                (*pai)->fatorB = -1;
                filho->fatorB = 0;
            }
            neto->fatorB = 0;
            rotacaoDireitaEsquerda(pai);
        }
    }
}

void inserirRecursivo(No **noAtual, Aluno aluno, int *cresceu)
{
    if(estaCheia())
        printf("\nErro! A árvore está cheia\n");
    else
    {

        if((*noAtual) == NULL)
        {
            No *noNovo = criarNo();
            noNovo->aluno = aluno;
            (*noAtual) = noNovo;
            *cresceu = 1;
            return;   
        }

        if(aluno.ra < (*noAtual)->aluno.ra)
        {
            inserirRecursivo(&(*noAtual)->filhoEsquerda, aluno, cresceu);
            if(*cresceu)
                (*noAtual)->fatorB -= 1;
        }
        else
        {
            inserirRecursivo(&(*noAtual)->filhoDireita, aluno, cresceu);
            if(*cresceu)
                (*noAtual)->fatorB += 1;
        }

        realizarRotacao(noAtual);

        if(*cresceu && (*noAtual)->fatorB == 0)
            *cresceu = 0;
    }
}

void inserir(ArvoreBinariaBusca *arvore, Aluno aluno)
{
    int cresceu;
    inserirRecursivo(&(arvore->raiz), aluno, &cresceu);
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

void deletarNo(No **noAtual, int *diminuiu)
{
    No *aux = *noAtual;

    if((*noAtual)->filhoEsquerda == NULL)
    {
        *noAtual = (*noAtual)->filhoDireita;
        *diminuiu = 1;
        free(aux);
    }
    else if((*noAtual)->filhoDireita == NULL)
    {
        *noAtual = (*noAtual)->filhoEsquerda;
        *diminuiu = 1;
        free(aux);
    }
    else
    {
        Aluno alunoSucessor = obterSucessor(*noAtual);
        (*noAtual)->aluno = alunoSucessor;
        removerBusca(alunoSucessor, &(*noAtual)->filhoDireita, diminuiu);
        if(diminuiu)
            (*noAtual)->fatorB -= 1;
    }

}

void removerBusca(Aluno aluno, No **noAtual, int *diminuiu)
{
    if(aluno.ra < (*noAtual)->aluno.ra)
    {
        removerBusca(aluno, &((*noAtual)->filhoEsquerda), diminuiu);
        if(*diminuiu)
            (*noAtual)->fatorB += 1;
    }
    else if(aluno.ra > (*noAtual)->aluno.ra)
    {
        removerBusca(aluno, &((*noAtual)->filhoDireita), diminuiu);
        if(*diminuiu)
            (*noAtual)->fatorB -= 1;
    }
    else
        deletarNo(noAtual, diminuiu);
    
    if(noAtual != NULL)
    {
        realizarRotacao(noAtual);
        if(*diminuiu && (*noAtual)->fatorB != 0)
            *diminuiu = 0;
    }
}

void remover(ArvoreBinariaBusca *arvore, Aluno aluno)
{
    if(estaVazia(*arvore))
        printf("\nErro! A árvore está vazia\n");
    else
    {
        int diminuiu;
        removerBusca(aluno, &(arvore->raiz), &diminuiu);
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
        printf("\n[2] - Remover aluno");
        printf("\n[3] - Buscar aluno");
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
                leiaRA("\nRA do aluno a ser removido: ", &aluno.ra);
                remover(&arvore, aluno);
                break;
            case 3:
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