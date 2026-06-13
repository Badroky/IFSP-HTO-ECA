#include <stdio.h>

#define MAX 10

typedef struct {
    int front;
    int rear;
    int dados [MAX]
} FILA;

void inicializar_fila (FILA *f) {
    f -> front = 0;
    f -> rear = -1;
}

int fila_vazia (FILA *f) {
    return f -> rear == -1;
}

void insere_fila (FILA *f, int valor) {
    if (fila_cheia(f)) {
        printf("[ERRO] Fila cheia.\n");
        return;
    }

    f -> dados[++(f -> rear)] = valor;

    printf("Insere (%d).\n", valor);
}

int remove_fila (FILA *f) {
    if (fila_vazia(f)) {
        printf("[ERRO] Fila vazia.\n");
        return -1;
    }

    return f -> dados[(f -> front)++];
}

void imprimir_fila (FILA *f) {
    printf("Inicio -> ");
    for (int i = f -> front; i <= f -> rear; i++) {
        printf("%d ", f -> dados[i]);
    }

    printf("<- Final\n\n");
}

int main() {
    FILA f;

    inicializar_fila(&f);

    printf("Inserindo elementos:\n");

    insere_fila(&f, 40);
    insere_fila(&f, 30);
    insere_fila(&f, 70);
    insere_fila(&f, 20);

    imprimir_fila(&f);

    printf("Removendo elementos:\n");

    printf("Remove (%d).\n", remove_fila(&f));
    printf("Remove (%d).\n", remove_fila(&f));
    printf("Remove (%d).\n", remove_fila(&f));
    printf("Remove (%d).\n", remove_fila(&f));

    imprimir_fila(&f);

    return 0;
}