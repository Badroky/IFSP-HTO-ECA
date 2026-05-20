#include <stdlib.h>
#include <stdio.h>

int main() {
    int *lista;
    lista = malloc(60000000000000 * sizeof(int));

    if (lista) {
        for (int i=0; i<6; i++) {
            printf ("%d \n", lista[i]);
        }
    }
    else {
        printf("Memoria insuficiente.\n");
        exit(1);
    }

    free(lista);
    return 0;
}