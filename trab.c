#include <stdio.h>
#include <stdlib.h>

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
            fprintf(archive, "%dx%d +", dados_compri[j * c + i], j);
        }
        for (; j == p; j++)
        {
            fprintf(archive, "%dx%d >= %d;\n", dados_compri[j * c + i], j, compo_nece[i]);
        }
    }
}

void printComponenteLimite(FILE *archive, int c, int p, int k, int *dados_compri, int *limite)
{
    for (int i = 1; i <= k; i++)
    {
        int j = 1;
        for (; j < p; j++)
        {
            fprintf(archive, "%dx%d +", dados_compri[j * c + i], j);
        }
        for (; j == k; j++)
        {
            fprintf(archive, "%dx%d <= %d;\n", dados_compri[j * c + i], j, limite[k]);
        }
    }
}

void printDeclaracoes(FILE *archive, int p)
{
    int i = 1;
    for (; i < p; i++)
    {
        fprintf(archive, "int x%d; ", i);
    }
    for (; i == p; i++)
    {
        fprintf(archive, "int x%d;", i);
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

    int *funcObjetivo = malloc(sizeof(int) * p);
    printFuncaoObjetivo(arquivo, dados_compri, p, c);
    printComponenteDiario(arquivo, c, p, compo_nece, dados_compri);
    printComponenteLimite(arquivo, c, p, k, dados_compri, limite);
    printDeclaracoes(arquivo, p);

    fprintf(arquivo, "a");

    free(funcObjetivo);
    fclose(arquivo);
};

int main()
{
    int c, p;
    printf("Quais sao as qnt de componentes e a qnt de tipos de comprimidos ? \n");
    if (scanf("%d %d", &c, &p) != 2)
        return 1;
    int *compo_nece = malloc(sizeof(int) * c);
    printf("Quais sao as quantidades diarias necessarias de cada componente ?\n");
    // o usuario deve mandar uma linha com c numeros inteiros
    // isso indica as quantidades diarias necessarias de cada componente q1,q2,..., qc
    for (int i = 0; i < c; i++)
    {
        if (scanf("%d", &compo_nece[i]) != 1)
            break;
    }
    int total_elementos = p * (c + 1);
    int *dados_compri = malloc(sizeof(int) * total_elementos);
    printf("Quais sao as p linhas, cada uma com os dados de um tipo de comprimido ?");
    // Linha: produto
    // Coluna: Componentes do produto
    for (int i = 0; i < total_elementos; i++)
    {
        if (scanf("%d", &dados_compri[i]) != 1)
            break;
    }

    // restricoes
    int k;
    if (scanf("%d", &k) != 1)
        return 4;

    int *limite = malloc(sizeof(int) * (k * 2));
    for (int i = 0; i < k; i += 2)
    {
        // leitura do par <componente, limite>
        if (scanf("%d %d", &limite[i], &limite[i + 1]) != 2)
            break;
    }

    // Cada comprimido i eh descrito com c + 1 numeros inteiros
    // Sendo r[i,1],r[1,2],...,r[i,c] as quantidades de cada componente presente no comprimido
    // v[i] eh o preco, com i = 1,2,...,p

    montaPL(c, p, k, compo_nece, dados_compri, limite);

    free(compo_nece);
    free(dados_compri);

    return 0;
}

// z = for (int i = 1 , i<= p, i++) { z = vi * xi}
// min z;
// restricoes

// int limite = 0;
//  for(int i = 1; i <= p; i++){limite = limite + r[i,ft]*xi}
//  limite <= lt
// para todo t pertencente a [1,k]
// para cada componente limitado, a soma total nao pode ultrapassar o limite

// int componentes =0
//  for(int i =1; i<= p; i++){componentes +=r[i,j]*xi}
// componentes >= qj para
// odo j pertencente a [1,c]
/// t//para cada componente j, a soma da quantidade presente nos comprimidos escolhidos deve ser pelo menos qj
