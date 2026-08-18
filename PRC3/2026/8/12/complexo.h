#ifndef COMPLEXO_H
#define COMPLEXO_H

/*
Tipo de dado abstrato para numeros complexos.
Suporta representacao retangular e polar.
*/

/*
1a) Formato: retangular ou polar
*/
typedef enum {
    RETANGULAR,
    POLAR
} t_formato;

/*
1b) Formato polar: modulo e argumento (double)
*/
typedef struct {
    double modulo;
    double argumento;
} t_polar;

/*
1c) Formato retangular: parte real e imaginaria (double)
*/
typedef struct {
    double real;
    double imaginaria;
} t_retangular;

typedef struct {
    t_formato f;
    union {
        t_polar pol;
        t_retangular rec;
    };
} t_cplx;

/* o template original usa "cplx" e "CPLX" como se fossem o mesmo tipo —
   os dois apelidos abaixo resolvem isso e deixam o resto do codigo igual */
typedef t_cplx cplx;
typedef t_cplx CPLX;

/*
2 - Dado um formato e um complexo, devolve o valor cplx no formato especificado
*/
cplx converte_CPLX(cplx a, t_formato f);

/*
3 - Soma de dois CPLX em qualquer formato. Devolve no formato de 'a'.
*/
cplx somar_CPLX(cplx a, cplx b);

/*
4 - Diferenca de dois CPLX em qualquer formato. Devolve no formato de 'a'.
*/
cplx subtrair_CPLX(cplx a, cplx b);

/*
5 - Produto de dois CPLX em qualquer formato. Devolve no formato de 'a'.
*/
cplx multiplicar_CPLX(cplx a, cplx b);

/*
6 - Divisao de dois CPLX em qualquer formato. Devolve no formato de 'a'.
*/
cplx dividir_CPLX(cplx a, cplx b);

/*
7 - Conjugado de um CPLX em qualquer formato. Mantem o formato de 'a'.
*/
cplx conjugado_CPLX(cplx a);

/*
8 - Modulo de um CPLX em qualquer formato.
*/
double mod_CPLX(cplx a);

/*
9 - Argumento de um CPLX em qualquer formato.
*/
double arg_CPLX(cplx a);

/*
10 - Parte imaginaria de um CPLX em qualquer formato.
*/
double img_CPLX(cplx a);

/*
10 - Parte real de um CPLX em qualquer formato.
*/
double re_CPLX(cplx a);

/*
11 - 'a' elevado a 'n' (double). Teorema de De Moivre facilita em formato polar.
*/
cplx potencia_CPLX(cplx a, double n);

/*
12 - "e" (constante de Euler) elevado a 'a'.
*/
cplx exp_CPLX(cplx a);

/*
13 - Imprime o valor de um CPLX de acordo com seu formato.
*/
void imprimir_CPLX(cplx a);

/*
Bonus 14 - Calcula as n raizes enesimas de um CPLX.
*/
void raizes_CPLX(cplx c, int n, cplx resultados[]);

#endif