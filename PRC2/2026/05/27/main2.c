//  Faça um programa que leia quatro números a, b, c e d, que serão as dimensões de duas matrizes: (a x b) e (c x d), dinamicamente e: 1. Crie e leia os valores de cada matriz, dadas as dimensões delas; 2. Crie e construa uma matriz que seja o porduto dessas duas matrizes; 3. imprima as duas matrizes e o produtro entre elas, se existir.
#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, c, d;
    printf("Digite as dimensões da primeira matriz (a x b): ");
    scanf("%d %d", &a, &b);
    printf("Digite as dimensões da segunda matriz (c x d): ");
    scanf("%d %d", &c, &d);

    // Verificar se o produto é possível
    if (b != c) {
        printf("O produto das matrizes não é possível. O número de colunas da primeira matriz deve ser igual ao número de linhas da segunda matriz.\n");
        return 1;
    }

    // Alocar memória para as matrizes
    int **matriz1 = (int **)malloc(a * sizeof(int *));
    for (int i = 0; i < a; i++) {
        matriz1[i] = (int *)malloc(b * sizeof(int));
    }

    int **matriz2 = (int **)malloc(c * sizeof(int *));
    for (int i = 0; i < c; i++) {
        matriz2[i] = (int *)malloc(d * sizeof(int));
    }

    int **produto = (int **)malloc(a * sizeof(int *));
    for (int i = 0; i < a; i++) {
        produto[i] = (int *)malloc(d * sizeof(int));
    }

    // Ler os valores da primeira matriz
    printf("Digite os valores da primeira matriz:\n");
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            scanf("%d", &matriz1[i][j]);
        }
    }

    // Ler os valores da segunda matriz
    printf("Digite os valores da segunda matriz:\n");
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%d", &matriz2[i][j]);
        }
    }

    // Calcular o produto das matrizes
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < d; j++) {
            produto[i][j] = 0;
            for (int k = 0; k < b; k++) {
                produto[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    // Imprimir as matrizes
    printf("Primeira matriz:\n");
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%d ", matriz1[i][j]);
        }
        printf("\n");
    }

    printf("Segunda matriz:\n");
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < d; j++) {
            printf("%d ", matriz2[i][j]);
        }
        printf("\n");
    }

    printf("Produto das matrizes:\n");
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < d; j++) {
            printf("%d ", produto[i][j]);
        }
        printf("\n");
    }

    // Liberar memória alocada
    for (int i = 0; i < a; i++) {
        free(matriz1[i]);
    }
    free(matriz1);

    for (int i = 0; i < c; i++) {
        free(matriz2[i]);
    }
    free(matriz2);

    for (int i = 0; i < a; i++) {
        free(produto[i]);
    }
    free(produto);

    return 0;
}