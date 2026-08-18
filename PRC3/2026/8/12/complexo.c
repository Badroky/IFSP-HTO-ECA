#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complexo.h"

/* nem todo ambiente expoe M_PI por padrao (depende do -std usado),
entao garantimos que ele exista de qualquer jeito */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* ----------------------------------------------------------------------
converte_CPLX: a funcao mais importante do arquivo.
Todas as outras (soma, produto, potencia...) chamam ela por baixo
dos panos em vez de duplicar a formula de conversao. Isso evita ter
a mesma matematica escrita em varios lugares (o famoso "nao se repita").
---------------------------------------------------------------------- */
cplx converte_CPLX(cplx a, t_formato f){
    cplx r;
    
    if (a.f == f) {
        return a;               /* ja esta no formato pedido, nao ha o que fazer */
    }

if (f == RETANGULAR) {
    /* vindo de POLAR -> RETANGULAR : projeta o vetor (modulo, angulo)
    nos eixos real e imaginario com cosseno e seno */
    r.f = RETANGULAR;
    r.rec.real       = a.pol.modulo * cos(a.pol.argumento);
    r.rec.imaginaria = a.pol.modulo * sin(a.pol.argumento);
} else {
/* vindo de RETANGULAR -> POLAR : Pitagoras da o modulo,
atan2 da o angulo (atan2 e melhor que atan pois considera
o sinal dos dois catetos e cobre os 4 quadrantes) */
r.f = POLAR;
r.pol.modulo    = sqrt(a.rec.real * a.rec.real + a.rec.imaginaria * a.rec.imaginaria);
r.pol.argumento = atan2(a.rec.imaginaria, a.rec.real);
}
return r;
}

/* ----------------------------------------------------------------------
soma e subtracao: matematicamente so existe formula simples em
RETANGULAR (soma parte a parte). Por isso a estrategia e sempre:
1) converter os dois operandos pra RETANGULAR
2) fazer a conta
3) converter o resultado de volta pro formato de 'a' (regra do enunciado)
---------------------------------------------------------------------- */
cplx somar_CPLX(cplx a, cplx b){
    cplx ar = converte_CPLX(a, RETANGULAR);
    cplx br = converte_CPLX(b, RETANGULAR);
    cplx r;
    
    r.f = RETANGULAR;
    r.rec.real       = ar.rec.real       + br.rec.real;
    r.rec.imaginaria = ar.rec.imaginaria + br.rec.imaginaria;
    
    return converte_CPLX(r, a.f);   /* devolve no formato original de 'a' */
}

cplx subtrair_CPLX(cplx a, cplx b){
    cplx ar = converte_CPLX(a, RETANGULAR);
    cplx br = converte_CPLX(b, RETANGULAR);
    cplx r;
    
    r.f = RETANGULAR;
    r.rec.real       = ar.rec.real       - br.rec.real;
    r.rec.imaginaria = ar.rec.imaginaria - br.rec.imaginaria;
    
    return converte_CPLX(r, a.f);
}

/* ----------------------------------------------------------------------
multiplicacao e divisao: e o oposto da soma. Em RETANGULAR a formula
tem 4 multiplicacoes e envolve i^2 = -1 (mais conta e mais chance de
erro). Em POLAR e so multiplicar/dividir modulos e somar/subtrair
angulos. Por isso a conversao aqui e pra POLAR, nao pra RETANGULAR.
---------------------------------------------------------------------- */
cplx multiplicar_CPLX(cplx a, cplx b){
    cplx ap = converte_CPLX(a, POLAR);
    cplx bp = converte_CPLX(b, POLAR);
    cplx r;
    
    r.f = POLAR;
    r.pol.modulo    = ap.pol.modulo * bp.pol.modulo;
    r.pol.argumento = ap.pol.argumento + bp.pol.argumento;
    
    return converte_CPLX(r, a.f);
}

cplx dividir_CPLX(cplx a, cplx b){
    cplx ap = converte_CPLX(a, POLAR);
    cplx bp = converte_CPLX(b, POLAR);
    cplx r;
    
    r.f = POLAR;
    
    if (bp.pol.modulo == 0.0) {
        /* divisao por zero: nao existe resultado valido.
        avisamos no stderr (nao atrapalha a saida normal do programa)
        e devolvemos 0 pra nao travar a execucao */
        fprintf(stderr, "Erro: divisao por complexo de modulo zero\n");
        r.pol.modulo    = 0.0;
        r.pol.argumento = 0.0;
        return converte_CPLX(r, a.f);
    }

r.pol.modulo    = ap.pol.modulo / bp.pol.modulo;
r.pol.argumento = ap.pol.argumento - bp.pol.argumento;

return converte_CPLX(r, a.f);
}

/* ----------------------------------------------------------------------
conjugado: NAO precisa converter formato (por isso nao chama
converte_CPLX aqui). Em RETANGULAR so inverte o sinal da parte
imaginaria; em POLAR so inverte o sinal do angulo (espelha no eixo
real). Fazer via conversao funcionaria, mas seria trabalho a mais
pra um calculo que ja e trivial no proprio formato de 'a'.
---------------------------------------------------------------------- */
cplx conjugado_CPLX(cplx a){
    cplx r = a;   /* copia tudo, so muda o sinal do que precisa */
    
    if (a.f == RETANGULAR) {
        r.rec.imaginaria = -a.rec.imaginaria;
    } else {
    r.pol.argumento = -a.pol.argumento;
}
return r;
}

/* ----------------------------------------------------------------------
os 4 "getters": mod, arg, parte imaginaria, parte real.
Mesma logica em todos: se o dado ja esta guardado direto na struct,
devolve na hora (custo zero); senao, calcula a partir do outro
formato. Isso evita converter a struct inteira so pra ler um numero.
---------------------------------------------------------------------- */
double mod_CPLX(cplx a){
    if (a.f == POLAR) {
        return a.pol.modulo;
    }
return sqrt(a.rec.real * a.rec.real + a.rec.imaginaria * a.rec.imaginaria);
}

double arg_CPLX(cplx a){
    if (a.f == POLAR) {
        return a.pol.argumento;
    }
return atan2(a.rec.imaginaria, a.rec.real);
}

double img_CPLX(cplx a){
    if (a.f == RETANGULAR) {
        return a.rec.imaginaria;
    }
return a.pol.modulo * sin(a.pol.argumento);
}

double re_CPLX(cplx a){
    if (a.f == RETANGULAR) {
        return a.rec.real;
    }
return a.pol.modulo * cos(a.pol.argumento);
}

/* ----------------------------------------------------------------------
potencia (Teorema de De Moivre): (mod, ang)^n = (mod^n, ang*n).
So funciona simples em POLAR -- em RETANGULAR teria que expandir
um binomio de Newton pra cada n, o que e generico mas muito mais
caro e mais sujeito a erro de arredondamento.
---------------------------------------------------------------------- */
cplx potencia_CPLX(cplx a, double n){
    cplx ap = converte_CPLX(a, POLAR);
    cplx r;
    
    r.f = POLAR;
    r.pol.modulo    = pow(ap.pol.modulo, n);
    r.pol.argumento = ap.pol.argumento * n;
    
    return converte_CPLX(r, a.f);
}

/* ----------------------------------------------------------------------
exponencial: e^(x + yi) = e^x * (cos(y) + i*sen(y))  -- formula de Euler.
Repara que aqui usamos re_CPLX/img_CPLX (os getters de cima) em vez
de acessar a.rec.real direto: assim a funcao aceita 'a' em QUALQUER
formato de entrada sem precisar de um if extra.
---------------------------------------------------------------------- */
cplx exp_CPLX(cplx a){
    double x = re_CPLX(a);
    double y = img_CPLX(a);
    cplx r;
    
    r.f = POLAR;
    r.pol.modulo    = exp(x);   /* exp() do math.h: "e" elevado a x */
    r.pol.argumento = y;
    
    return converte_CPLX(r, a.f);
}

/* ----------------------------------------------------------------------
imprimir: formato de exibicao muda conforme a.f. Em retangular,
troca o sinal impresso ("+" ou "-") pra nao aparecer "2.0 + -3.0i"
feio na tela.
---------------------------------------------------------------------- */
void imprimir_CPLX(cplx a){
    if (a.f == RETANGULAR) {
        if (a.rec.imaginaria >= 0) {
            printf("%.4f + %.4fi\n", a.rec.real, a.rec.imaginaria);
        } else {
        printf("%.4f - %.4fi\n", a.rec.real, -a.rec.imaginaria);
    }
} else {
printf("%.4f * (cos(%.4f) + i*sen(%.4f))\n",
a.pol.modulo, a.pol.argumento, a.pol.argumento);
}
}

/* ----------------------------------------------------------------------
raizes enezimas: formula geral das raizes de um numero complexo.
Para n raizes de c = (mod, ang):
modulo_raiz = mod^(1/n)                 (igual pra todas as raizes)
angulo_k    = (ang + 2*pi*k) / n ,  k = 0..n-1
O "+2*pi*k" e o que gera as n raizes DIFERENTES (sem ele so acharia
uma). Isso so e simples em POLAR -- por isso convertemos c primeiro.
---------------------------------------------------------------------- */
void raizes_CPLX(cplx c, int n, cplx resultados[]){
    int k;
    cplx cp;
    double modulo_raiz;
    
    if (n <= 0) {
        return;   /* nao existe "raiz de ordem 0 ou negativa", nao faz nada */
    }

    cp = converte_CPLX(c, POLAR);
    modulo_raiz = pow(cp.pol.modulo, 1.0/n);

    for (k = 0; k < n; k++) {
        cplx r;
        r.f = POLAR;
        r.pol.modulo = modulo_raiz;
        r.pol.argumento = (cp.pol.argumento + 2.0 * M_PI * k) / n;
        resultados[k] = converte_CPLX(r, c.f); /* devolve no formato de entrada c */
    }

}