#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define main main_orig
#include "main.c"
#undef main

void test_ordenar_crescente() {
    sensor v[3] = {
        {1, "tipoA", 3.0, 10.0, 0.0, 0},
        {2, "tipoB", 1.0, 10.0, 0.0, 0},
        {3, "tipoC", 2.0, 10.0, 0.0, 0}
    };

    ordenar(v, 3, 1); // crescente = 1

    assert(v[0].valor_atual == 1.0);
    assert(v[1].valor_atual == 2.0);
    assert(v[2].valor_atual == 3.0);

    printf("test_ordenar_crescente passed.\n");
}

void test_ordenar_decrescente() {
    sensor v[3] = {
        {1, "tipoA", 1.0, 10.0, 0.0, 0},
        {2, "tipoB", 3.0, 10.0, 0.0, 0},
        {3, "tipoC", 2.0, 10.0, 0.0, 0}
    };

    ordenar(v, 3, 0); // decrescente = 0

    assert(v[0].valor_atual == 3.0);
    assert(v[1].valor_atual == 2.0);
    assert(v[2].valor_atual == 1.0);

    printf("test_ordenar_decrescente passed.\n");
}

void test_ordenar_edge_cases() {
    // 1 element array
    sensor v1[1] = {
        {1, "tipoA", 3.0, 10.0, 0.0, 0}
    };
    ordenar(v1, 1, 1);
    assert(v1[0].valor_atual == 3.0);

    // Already sorted array
    sensor v2[3] = {
        {1, "tipoA", 1.0, 10.0, 0.0, 0},
        {2, "tipoB", 2.0, 10.0, 0.0, 0},
        {3, "tipoC", 3.0, 10.0, 0.0, 0}
    };
    ordenar(v2, 3, 1);
    assert(v2[0].valor_atual == 1.0);
    assert(v2[1].valor_atual == 2.0);
    assert(v2[2].valor_atual == 3.0);

    // Empty array (0 elements) - to ensure no out of bounds
    sensor v3[1];
    ordenar(v3, 0, 1);

    printf("test_ordenar_edge_cases passed.\n");
}

int main() {
    printf("Running test_ordenar...\n");
    test_ordenar_crescente();
    test_ordenar_decrescente();
    test_ordenar_edge_cases();
    printf("All tests passed!\n");
    return 0;
}
