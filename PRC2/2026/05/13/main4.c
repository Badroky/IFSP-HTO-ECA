#include <stdio.h>

static int estatica_global = 10;

void segunda() {
    static int estatica_segunda = 50;
    static int teste;
    printf("--- Funcao segunda ---\n");
    printf("Variavel Estatica (Local): valor = %d, endereco = %p\n", estatica_segunda, (void*)&estatica_segunda);
    printf("Variavel Estatica (Local) sem inicializacao: valor = %d, endereco = %p\n", teste, (void*)&teste);
}

void primeira() {
    int local_p1 = 20;
    int local_p2 = 30;
    int local_p3 = 40;
    printf("--- Funcao primeira ---\n");
    printf("Variavel Local 1: valor = %d, endereco = %p\n", local_p1, (void*)&local_p1);
    printf("Variavel Local 2: valor = %d, endereco = %p\n", local_p2, (void*)&local_p2);
    printf("Variavel Local 3: valor = %d, endereco = %p\n", local_p3, (void*)&local_p3);

    printf("Chamando segunda()...\n");
    segunda();
}

int main() {
    printf("--- Funcao main ---\n");
    printf("Variavel Estatica Global: valor = %d, endereco = %p\n", estatica_global, (void*)&estatica_global);
    int local_main = 60;
    printf("Variavel Local main: valor = %d, endereco = %p\n", local_main, (void*)&local_main); // Variável local fictícia para demonstração
    printf("Chamando primeira()...\n");
    primeira();
    return 0;
}