#include <stdlib.h>

int main() {
    int *lista;
    lista = malloc(6 * sizeof(int));

    for (int i=0; i<6; i++) {
        lista[i] = i;
    }

    for (int i=0; i<6; i++) {
        printf("%d \n", lista[i]);
    }

    free(lista);
    return 0;
}