#ifndef COMPLEXO_H
#define COMPLEXO_H

#include <stdio.h>

/* a) Enumeração para o formato do número complexo */
typedef enum {
    RETANGULAR;
    POLAR;
} t_formato;

typedef t_formato t_format;
typedef t_formato format;

/* b) Estrutura para o formato polar */
typedef struct {
    double mod; /* módulo do número complexo */
    double arg; /* 'arg' para argumento (ângulo em radianos se nao me engano) */
} t_polar;

/* c) Estrutura pro formato retang */
typedef struct {
    double real;
    double imag;
} t_retangular;

/* estrutura principal do professor */
typedef struct{
    t_format f;
    union{
        t_polar pol;
        t_retangular rec;
    };
} t_cplx;

/* aliases :) */
typedef t_cplx cplx;
typedef t_cplx CPLX;

/* explicação */
cplx criar_retangular(double real, double imag);
cplx criar_polar(double mod, double arg);


cplx converte_cplx(cplx a, format f);/*2 - dado um formato e um complexo devolva o valor cplx no formato especificado.*/

cplx somar_CPLX(cplx a, cplx b);
cplx subtrair_CPLX(cplx a, cplx b);
cplx multiplicar_CPLX(cplx a, cplx b);
cplx dividir_CPLX(cplx a, cplx b);

cplx conjugado_CPLX(cplx a);/*7 - dado um CPLX em qualquer formato, devolva o resultado do conjugado. Mantenha o formato de a.*/

double mod_CPLX(cplx a);/* 8 - dado um CPLX em qualquer formato, devolva o modulo.*/
double arg_CPLX(cplx a);/* 9 - dado um CPLX em qualquer formato, devolva o argumento.*/
double re_CPLX(cplx a);/* 10.1 - dado um CPLX em qualquer formato, devolva a parte real.*/
double img_CPLX(cplx a);/* 10.2 - dado um CPLX em qualquer formato, devolva a parte imaginária.*/

cplx potencia_CPLX(cplx a, double n);
cplx exp_CPLX(cplx a);
void raizes_CPLX(cplx c, int n, cplx resultados[]);

void imprimir_CPLX(cplx a);

#endif
