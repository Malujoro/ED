#include <stdio.h>
#include <stdlib.h>

#define VAZIO -1
#define DISPONIVEL -2

typedef struct
{
    int ra;
    char nome[100];
} Aluno;

typedef struct
{
    int quantItens;
    int maxItens;
    int maxPosicoes;
    Aluno *estrutura;
} Hash;

Aluno criarAluno()
{
    Aluno aluno;

    aluno.ra = VAZIO;
    aluno.nome[0] = ' ';
    aluno.nome[1] = '\0';
    
    return aluno;
}

Aluno *criarListaAlunos(int tamVetor)
{
    Aluno *aluno = malloc(tamVetor * sizeof(Aluno));

    for(int i = 0; i < tamVetor; i++)
        aluno[i] = criarAluno();
    
    return aluno;
}

Hash criarHash(int tamVetor, int maxItens)
{
    Hash hash;

    hash.estrutura = criarListaAlunos(tamVetor);
    hash.quantItens = 0;
    hash.maxItens = maxItens;
    hash.maxPosicoes = tamVetor;

    return hash;
}

void excluirHash(Hash *hash)
{
    free(hash->estrutura);
    hash->quantItens = 0;
}

int estaCheia(Hash hash)
{
    return(hash.quantItens == hash.maxItens);
}

int funcaoHash(Hash hash, Aluno aluno)
{
    return (aluno.ra % hash.maxPosicoes);
}

void inserir(Hash *hash, Aluno aluno)
{
    if(estaCheia(*hash))
        printf("\nErro! O vetor está cheio\n");
    else
    {
        int posicao = funcaoHash(*hash, aluno);
        hash->estrutura[posicao] = aluno;
        hash->quantItens++;
    }
}

void deletar(Hash *hash, Aluno aluno)
{
    int posicao = funcaoHash(*hash, aluno);
    if(hash->estrutura[posicao].ra != VAZIO)
    {
        hash->estrutura[posicao] = criarAluno();
        hash->quantItens--;
    }
}

int buscar(Hash hash, Aluno *aluno)
{
    int posicao = funcaoHash(hash, *aluno);

    if(hash.estrutura[posicao].ra == aluno->ra)
    {
        *aluno = hash.estrutura[posicao];
        return 1;
    }

    return 0;
}

void imprimir(Hash hash)
{
    printf("\nTabela Hash: \n");
    for(int i = 0; i < hash.maxPosicoes; i++)
    {
        if(hash.estrutura[i].ra != VAZIO)
        {
            printf("\n-----%dº-----", i);
            printf("\nRA: %d", hash.estrutura[i].ra);
            printf("\nAluno: %s\n", hash.estrutura[i].nome);
        }
    }
}

int leiaRA(char *texto)
{
    int ra;
    printf("%s", texto);
    scanf(" %d", &ra);
    return ra;
}

int main()
{
    Aluno dado;
    int op, tamVetor, maxItens;

    do
    {
        printf("\nTamanho da hash: ");
        scanf(" %d", &tamVetor);
        printf("Máximo de itens: ");
        scanf(" %d", &maxItens);

        printf("\nO fator de carga é: %.2f\n", (float) maxItens / (float) tamVetor);
    }while(tamVetor <= maxItens);

    Hash hash = criarHash(tamVetor, maxItens);

    do
    {
        printf("\nMenu");
        printf("\n[1] - Inserir Elemento");
        printf("\n[2] - Remover Elemento");
        printf("\n[3] - Buscar Elemento");
        printf("\n[4] - Exibir Hash");
        printf("\n[5] - Recriar Hash");
        printf("\n[0] - Sair");
        printf("\nOpção: ");
        scanf(" %d", &op);

        switch(op)
        {
            case 1:
                dado.ra = leiaRA("\nRA: ");
                printf("Nome: ");
                scanf(" %[^\n]s", dado.nome);
                inserir(&hash, dado);
                break;
            case 2:
                dado.ra = leiaRA("\nRA do aluno a ser removido: ");
                deletar(&hash, dado);
                break;
            case 3:
                dado.ra = leiaRA("\nRA do aluno a ser buscado: ");
                if(buscar(hash, &dado))
                {
                    printf("\nAluno encontrado:");
                    printf("\nRA: %d", dado.ra);
                    printf("\nNome: %s\n", dado.nome);
                }
                else
                    printf("\nAluno NÃO encontrado\n");
                break;
            case 4:
                imprimir(hash);
                break;
            case 5:
                excluirHash(&hash);
                hash = criarHash(tamVetor, maxItens);
                break;
        }
    }while(op != 0);

    return 0;
}