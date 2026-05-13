#include <stdio.h>

int main() {
    int valor = 500;
    int *ptr = &valor;
    int **pptr = &ptr;

    printf("--- Acesso Direto ---\n");
    printf("Valor de 'valor': %d\n", valor);

    printf("\n--- Acesso por ponteiro simples ---\n");
    printf("Conteudo de 'ptr' (endereco de valor): %p\n", ptr);
    printf("Valor acessado por '*ptr': %d\n", *ptr);

    printf("\n--- Acesso por ponteiro para ponteiro ---\n");
    printf("Conteudo de 'pptr' (endereco de ptr): %p\n", pptr);
    printf("Valor acessado por '**pptr': %d\n", **pptr);

    return 0;
}