//Escreva um programa que leia um número N e: 1.Crie dinamicamente e leia um vetor de inteiros de N posições; 2. Leia um número inteiro C e conte e mostre os múltiplos desse número que existem no vetor.
#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, C, conta = 0;
    int *vetor;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &N);

    vetor = (int*)malloc(N * sizeof(int));

    if(vetor == NULL){
        printf("[ERRO] Memoria insuficiente.");
        return 1;
    }

    for(int i = 0; i < N; i++){
        printf("Digite o elemento %d: ", i + 1);
        scanf("%d", &vetor[i]);
    }

    printf("Digite o número C: ");
    scanf("%d", &C);

    for(int i = 0; i < N; i++){
        if(vetor[i] % C == 0){
            conta++;
        }
    }

    printf("Existem %d múltiplos de %d no vetor.", conta, C);

    free(vetor);
    return 0;
}

