#include <stdio.h>
#include <stdlib.h>

void printFuncaoObjetivo(FILE *archive, int *dados_compri, int p, int c);

void printComponenteDiario(FILE *archive, int c, int p, int *compo_nece, int *dados_compri);

void printComponenteLimite(FILE *archive, int c, int p, int k, int *dados_compri, int *limite);

void printComponenteNaoNegativo(FILE *archive, int p);

void printDeclaracoes(FILE *archive, int p);

void montaPL(int c, int p, int k, int *compo_nece, int *dados_compri, int *limite);

int main()
{
    int c, p;
    printf("Quais sao as qnt de componentes e a qnt de tipos de comprimidos ? \n");
    if (scanf("%d %d", &c, &p) != 2)
        return 1;
    int *compo_nece = malloc(sizeof(int) * c);
    printf("Quais sao as quantidades diarias necessarias de cada componente ? \n");
    for (int i = 0; i < c; i++)
    {
        if (scanf("%d", &compo_nece[i]) != 1)
            return 2;
    }
    int total_elementos = p * (c + 1);
    int *dados_compri = malloc(sizeof(int) * total_elementos);
    printf("Quais sao as p linhas, cada uma com os dados de um tipo de comprimido ? \n");
    for (int i = 0; i < total_elementos; i++)
    {
        if (scanf("%d", &dados_compri[i]) != 1)
            return 3;
    }

    printf("Quais sao os k pares de limitacoes ? \n");
    int k;
    if (scanf("%d", &k) != 1)
        return 4;

    int tamLimite = k * 2;
    int *limite = malloc(sizeof(int) * tamLimite);

    printf("Quais os k pares de  ? \n");
    for (int i = 0; i < tamLimite; i += 2)
    {
        if (scanf("%d %d", &limite[i], &limite[i + 1]) != 2)
            return 5;
    }

    montaPL(c, p, k, compo_nece, dados_compri, limite);

    free(compo_nece);
    free(dados_compri);
    free(limite);

    return 0;
}

void printFuncaoObjetivo(FILE *archive, int *dados_compri, int p, int c)
{
    fprintf(archive, "min: ");
    for (int xDaVez = 1; xDaVez <= p; xDaVez++)
    {
        int indicePreco = ((xDaVez - 1) * (c + 1)) + c;

        if (dados_compri[indicePreco] != 0)
        {
            fprintf(archive, "%d x%d + ", dados_compri[indicePreco], xDaVez);
        }
    }

    fseek(archive, -3, SEEK_CUR);
    fprintf(archive, ";\n");
};

void printComponenteDiario(FILE *archive, int c, int p, int *compo_nece, int *dados_compri)
{
    for (int i = 1; i <= c; i++)
    {
        int j = 1;
        for (; j < p; j++)
        {
            fprintf(archive, "%dx%d +", dados_compri[(j - 1) * (c + 1) + i - 1], j);
        }
        for (; j == p; j++)
        {
            fprintf(archive, "%dx%d >= %d;\n", dados_compri[(j - 1) * (c + 1) + i - 1], j, compo_nece[i - 1]);
        }
    }
}

void printComponenteLimite(FILE *archive, int c, int p, int k, int *dados_compri, int *limite)
{
    int tam = k * 2;
    for (int i = 1; i <= tam; i += 2)
    {
        int j = 1;
        for (; j < p; j++)
        {
            //(j - 1) * c + i - 1
            fprintf(archive, "%dx%d +", dados_compri[(j - 1) * (c + 1) + limite[i - 1] - 1], j);
        }
        for (; j == p; j++)
        {
            fprintf(archive, "%dx%d <= %d;\n", dados_compri[(j - 1) * (c + 1) + limite[i - 1] - 1], j, limite[i]);
        }
    }
}

void printComponenteNaoNegativo(FILE *archive, int p)
{
    for (int i = 1; i <= p; i++)
    {
        fprintf(archive, "x%d >= 0;\n", i);
    }
}

void printDeclaracoes(FILE *archive, int p)
{
    int i = 1;
    fprintf(archive, "int ");
    for (; i < p; i++)
    {
        fprintf(archive, "x%d, ", i);
    }
    for (; i == p; i++)
    {
        fprintf(archive, "x%d;\n", i);
    }
}

void montaPL(int c, int p, int k, int *compo_nece, int *dados_compri, int *limite)
{
    if (!compo_nece || !dados_compri || !limite)
        return;

    FILE *arquivo;
    arquivo = fopen("saida.lp", "w+");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printFuncaoObjetivo(arquivo, dados_compri, p, c);
    printComponenteDiario(arquivo, c, p, compo_nece, dados_compri);
    printComponenteLimite(arquivo, c, p, k, dados_compri, limite);
    printComponenteNaoNegativo(arquivo, p);
    printDeclaracoes(arquivo, p);

    fclose(arquivo);
};
