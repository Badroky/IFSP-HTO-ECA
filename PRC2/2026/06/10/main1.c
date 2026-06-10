#include <stdio.h>

#define MAX 10

typedef struct {
    int topo;
    int dados [MAX];
    
} PILHA;

void inicializar_pilha (PILHA *p){
    p -> topo = -1;
}

int pilha_vazia (PILHA *p){
    return p -> topo == -1;
}

int pilha_cheia (PILHA *p){
    return p -> topo == MAX - 1;
}

void insere(PILHA *p, int valor){
    if (pilha_cheia(p)){
        printf("[ERRO] Pilha cheia.\n");
        return;
    }
    
    p -> dados[++p -> topo] = valor;

    printf("Valor %d inserido na pilha.\n", valor);
}

int remover (PILHA *p){
    if (pilha_vazia(p)){
        printf("[ERRO] Pilha vazia.\n");
        return -1;
    }

    return p -> dados[p -> topo--];

}

void imprimir_pilha (PILHA *p){
    printf("Topo -> ");

    for (int i = p -> topo; i >= 0; i--){
        printf("%d ", p -> dados[i]);
    }

    printf("\n\n");
}

