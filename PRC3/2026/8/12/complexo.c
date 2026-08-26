#include "complexo.h"
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static double normalizar_angulo(double arg) {
    while (arg > M_PI) arg -= 2.0 * M_PI;
    while (arg <= - M_PI) arg += 2.0 * M_PI;
    return arg;
}


cplx criar_retangular(double real, double imag) {
    cplx c;
    c.f = RETANGULAR;
    c.rec.real = real;
    c.rec.imag = imag;
    return c;
}

cplx criar_polar(double mod, double arg) {
    cplx c;
    c.f = POLAR;
    c.pol.mod = fabs(mod);
    c.pol.arg = normalizar_angulo(arg);
    return c;
}

/*8, 9, 10 - dado um CPLX em qualquer formato, devolva o modulo, o argumento e a parte imaginaria respectivamente. */
double mod_CPLX(cplx a){
    if (a.f == POLAR) {
        return fabs(a.pol.mod);
    }
    return hypot(a.rec.real, a.rec.imag);
}

double arg_CPLX(cplx a){
   if(a.f == POLAR) {
       return normalizar_angulo(a.pol.arg);
   }
   return atan2(a.rec.imag, a.rec.real);
}

double re_CPLX(cplx a){
    if (a.f == RETANGULAR) {
        return a.rec.real;
    }
    return a.pol.mod * cos(a.pol.arg);
}

double img_CPLX(cplx a){
    if (a.f == RETANGULAR) {
        return a.rec.imag;
    }
    return a.pol.mod * sin(a.pol.arg);
}

/* 2 */
cplx converte_CPLX(cplx a, format f) {
    if (a.f == f) {
        return a;
    }
    
    cplx res;
    res.f = f;
    
    if (f == RETANGULAR) {
        res.rec.real = re_CPLX(a);
        res.rec.imag = img_CPLX(a);
    } else {
        res.pol.mod = mod_CPLX(a);
        res.pol.arg = arg_CPLX(a);
    }
    
    return res;
}

/* 3, 4, 5, 6, 7 */
cplx somar_CPLX(cplx a, cplx b) {
    double r_real = re_CPLX(a) + re_CPLX(b);
    double r_imag = img_CPLX(a) + img_CPLX(b);
    cplx res = criar_retangular(r_real, r_imag);
    return converte_CPLX(res, a.f);
}

cplx subtrair_CPLX(cplx a, cplx b) {
    double r_real = re_CPLX(a) - re_CPLX(b);
    double r_imag = img_CPLX(a) - img_CPLX(b);
    cplx res = criar_retangular(r_real, r_imag);
    return converte_CPLX(res, a.f);
}

cplx multiplicar_CPLX(cplx a, cplx b) {
    double r_mod = mod_CPLX(a) * mod_CPLX(b);
    double r_arg = arg_CPLX(a) + arg_CPLX(b);
    cplx res = criar_polar(r_mod, r_arg);
    return converte_CPLX(res, a.f);
}

cplx dividir_CPLX(cplx a, cplx b) {
    double mod_b = mod_CPLX(b);
    if (mod_b == 0.0) {
        printf("[ERRO (básico)] Num pode essas coisas po, num inventa abobrinha. ;)\n");
        return a;
    }
    double r_mod = mod_CPLX(a) / mod_b;
    double r_arg = arg_CPLX(a) - arg_CPLX(b);
    cplx res = criar_polar(r_mod, r_arg);
    return converte_CPLX(res, a.f);
}

cplx conjugado_CPLX(cplx a) {
    cplx res = a;
    if (a.f == RETANGULAR) {
        res.rec.imag = -a.rec.imag;
    } else {
        res.pol.arg = -a.pol.arg;
    }
    return res;
}

/* 11, 12, 14 */
CPLX potencia_CPLX(CPLX a, double n) {
    double r_mod = pow(mod_CPLX(a), n);
    double r_arg = arg_CPLX(a) * n;
    CPLX res = criar_polar(r_mod, r_arg);
    return converte_CPLX(res, a.f);
}

CPLX exp_CPLX(CPLX a) {
    double x = re_CPLX(a);
    double y = img_CPLX(a);
    double r_mod = exp(x);
    double r_arg = y;
    CPLX res = criar_polar(r_mod, r_arg);
    return converte_CPLX(res, a.f);
}

void raizes_CPLX(cplx c, int n, cplx resultados[]) {
    if (n <= 0) return;
    double r = mod_CPLX(c);
    double theta = arg_CPLX(c);
    double r_raiz = pow(r, 1.0 / (double)n);
    
    for (int k = 0; k < n; k++) {
        double arg_k = (theta + 2.0 * M_PI * (double)k) / (double)n;
        cplx raiz_k = criar_polar(r_raiz, arg_k);
        resultados[k] = converte_CPLX(raiz_k, c.f);
    }
}

/* 13 */
void imprimir_CPLX(cplx a) {
    if (a.f == RETANGULAR) {
        char sinal = (a.rec.imag >= 0) ? '+' : '-';
        printf("%.4f %c %.4fi (Retangular)\n", a.rec.real, sinal, fabs(a.rec.imag));
    } else {
        double arg_graus = arg_CPLX(a) * (180.0 / M_PI);
        printf("|z| = %.4f, arg = %.4f rad (%.2f graus) (Polar)\n", a.pol.mod, a.pol.arg, arg_graus);
    }
}
