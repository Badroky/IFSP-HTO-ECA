#include <stdio.h>


int main() {
    int **ipp;
    int i=5, j=6, k=7;
    int *ip1 = &i, *ip2 = &j;

    ipp = &ip1;
    // ipp aponta para ip1, que aponta para i. *ipp é ip1 e **ipp é i, ou 5.
    prtintf("Valor de 'i', 'j' e 'k': %d, %d, %d\n", i, j, k);
    prtintf("Valor acessado por '*ip1': %d\n", *ip1);
    prtintf("Valor acessado por '**ipp': %d\n", **ipp);

    *ipp = ip2;
    // Alteramos o ponteiro apontado por ipp (isto é ip1) para conter uma cópia de ip2, de modo que ele (ip1) agora aponte para j.
    prtintf("Valor de 'i', 'j' e 'k': %d, %d, %d\n", i, j, k);
    prtintf("Valor acessado por '*ip1': %d\n", *ip1);
    prtintf("Valor acessado por '**ipp': %d\n", **ipp);

    *ipp = &k;
    // Alteramos o ponteiro apontado por ipp (ou seja, ip1 novamente) para apontar para k.
    prtintf("Valor de 'i', 'j' e 'k': %d, %d, %d\n", i, j, k);
    prtintf("Valor acessado por '*ip1': %d\n", *ip1);
    prtintf("Valor acessado por '**ipp': %d\n", **ipp);

    return 0;

}