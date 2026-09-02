#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complexo.h"

static double sanitizar(double val) {
    if (fabs(val) < 1e-9) {
        return 0.0;
    }
    return val;
}

static void print_label(const char *label, cplx c, t_format fout) {
    printf("%s", label);
    imprimir_CPLX(converte_CPLX(c, fout));
}

int main(void) {
    int n;
    double r;
    char f_out_ch;

    if (scanf("%d %lf %c", &n, &r, &f_out_ch) != 3) {
        return 0;
    }
    t_format f_out = (f_out_ch == 'P' || f_out_ch == 'p') ? POLAR : RETANGULAR;

    char f_a;
    double a1, a2;
    if (scanf(" %c %lf %lf", &f_a, &a1, &a2) != 3) {
        return 0;
    }
    cplx A = (f_a == 'P' || f_a == 'p') ? criar_polar(a1, a2) : criar_retangular(a1, a2);

    char f_b;
    double b1, b2;
    if (scanf(" %c %lf %lf", &f_b, &b1, &b2) != 3) {
        return 0;
    }
    cplx B = (f_b == 'P' || f_b == 'p') ? criar_polar(b1, b2) : criar_retangular(b1, b2);

    print_label("A = ", A, f_out);
    print_label("B = ", B, f_out);

    printf("PARTS A: MOD=%.2f ARG=%.2f RE=%.2f IMG=%.2f\n",
           sanitizar(mod_CPLX(A)), sanitizar(arg_CPLX(A)),
           sanitizar(re_CPLX(A)), sanitizar(img_CPLX(A)));
    printf("PARTS B: MOD=%.2f ARG=%.2f RE=%.2f IMG=%.2f\n",
           sanitizar(mod_CPLX(B)), sanitizar(arg_CPLX(B)),
           sanitizar(re_CPLX(B)), sanitizar(img_CPLX(B)));

    print_label("CONJ(A) = ", conjugado_CPLX(A), f_out);
    print_label("CONJ(B) = ", conjugado_CPLX(B), f_out);

    print_label("A + B = ", somar_CPLX(A, B), f_out);
    print_label("A - B = ", subtrair_CPLX(A, B), f_out);
    print_label("A * B = ", multiplicar_CPLX(A, B), f_out);
    print_label("A / B = ", dividir_CPLX(A, B), f_out);

    cplx c_r = criar_retangular(r, 0.0);
    print_label("R + A = ", somar_CPLX(c_r, A), f_out);
    print_label("R - A = ", subtrair_CPLX(c_r, A), f_out);
    print_label("A - R = ", subtrair_CPLX(A, c_r), f_out);
    print_label("R * A = ", multiplicar_CPLX(c_r, A), f_out);
    print_label("A / R = ", dividir_CPLX(A, c_r), f_out);
    print_label("R / A = ", dividir_CPLX(c_r, A), f_out);

    print_label("A ^ R = ", potencia_CPLX(A, r), f_out);
    print_label("exp(A) = ", exp_CPLX(A), f_out);

    printf("RAIZES DE A (ordem %d):\n", n);
    cplx *raizes = (cplx *)malloc(n * sizeof(cplx));
    if (raizes != NULL) {
        raizes_CPLX(A, n, raizes);
        for (int k = 0; k < n; k++) {
            printf("Raiz %d: ", k);
            imprimir_CPLX(converte_CPLX(raizes[k], f_out));
        }
        free(raizes);
    }

    return 0;
}
