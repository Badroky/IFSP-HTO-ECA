/* =============================================================================
 * DISCIPLINA: PROC3
 * TAREFA: Implementação do Tipo de Dado Abstrato (TDA) para Números Complexos
 *
 * INSTRUÇÕES:
 * 1. Preencha os tipos de dados e os corpos das funções indicadas com '--preencher--'.
 * 2. Respeite as assinaturas e as regras de formato de entrada e saída.
 * 3. Mantenha os ângulos da forma polar normalizados no intervalo (-PI, PI].
 * 4. Dica de Ponto Flutuante: Para evitar que valores nulos sejam impressos como
 *    '-0.00', utilize fabs(val) < 1e-9 ? 0.0 : val antes de exibir com printf.
 * ============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

/* =============================================================================
 * 1. DEFINIÇÃO DOS TIPOS DE DADOS
 * ============================================================================= */

/* 
 * 1.a) Especifique o enum com os formatos suportados:
 *      - RETANGULAR (representação z = a + bi)
 *      - POLAR       (representação z = r ∠ theta)
 */
typedef enum {
    RETANGULAR,
    POLAR
} t_formato;

/* 
 * 1.b) Especifique a estrutura para a representação polar:
 *      - modulo: valor double (r >= 0)
 *      - arg:    argumento/fase double (em radianos)
 */
typedef struct {
    double modulo;
    double arg;
} t_polar;

/* 
 * 1.c) Especifique a estrutura para a representação retangular:
 *      - real: parte real double
 *      - imag: parte imaginária double
 */
typedef struct {
    double real;
    double imag;
} t_retangular;

/* 
 * 1.d) Estrutura principal do TAD Complexo utilizando tagged union:
 *      - f: campo discriminador do formato atual (t_formato)
 *      - union anônima contendo pol (t_polar) e rec (t_retangular)
 */
typedef struct {
    t_formato f;
    union {
        t_polar pol;
        t_retangular rec;
    };
} t_cplx;

typedef t_cplx cplx;
typedef t_cplx CPLX;

/* =============================================================================
 * FUNÇÃO AUXILIAR DE NORMALIZAÇÃO ANGULAR
 * Mantém o argumento estritamente dentro do intervalo (-PI, PI]
 * ============================================================================= */
static double sanitizar(double val) {
    if (fabs(val) < 1e-2) {
        return 0.0;
    }
    return val;
}

static double normaliza_angulo(double theta) {
    while (theta <= -M_PI) theta += 2.0 * M_PI;
    while (theta > M_PI)  theta -= 2.0 * M_PI;
    if (fabs(theta) < 1e-2) theta = 0.0;
    return theta;
}

/* =============================================================================
 * 2. FUNÇÕES DE EXTRAÇÃO DE PROPRIEDADES (GETTERS)
 * Devem funcionar corretamente independentemente do formato interno de 'a'.
 * ============================================================================= */

/*
 * 2.a) Dado um complexo 'a', devolva a sua parte real.
 *      - Se estiver em POLAR: real = modulo * cos(arg)
 */
double re_CPLX(cplx a) {
    if (a.f == POLAR) {
        return a.pol.modulo * cos(a.pol.arg);
    }
    return a.rec.real;
}

/*
 * 2.b) Dado um complexo 'a', devolva a sua parte imaginária.
 *      - Se estiver em POLAR: imag = modulo * sin(arg)
 */
double img_CPLX(cplx a) {
    if (a.f == POLAR) {
        return a.pol.modulo * sin(a.pol.arg);
    }
    return a.rec.imag;
}

/*
 * 2.c) Dado um complexo 'a', devolva o seu módulo (magnitude).
 *      - Se estiver em RETANGULAR: modulo = sqrt(real^2 + imag^2) ou hypot(real, imag)
 */
double mod_CPLX(cplx a) {
    if (a.f == POLAR) {
        return a.pol.modulo;
    }
    return hypot(a.rec.real, a.rec.imag);
}

/*
 * 2.d) Dado um complexo 'a', devolva o seu argumento em radianos (-PI, PI].
 *      - Se estiver em RETANGULAR: arg = atan2(imag, real)
 */
double arg_CPLX(cplx a) {
    if (a.f == POLAR) {
        return normaliza_angulo(a.pol.arg);
    }
    return normaliza_angulo(atan2(a.rec.imag, a.rec.real));
}

/* =============================================================================
 * 3. CONVERSÃO DE FORMATO E DE TIPO
 * ============================================================================= */

/*
 * 3.a) Dado um complexo 'a' e um formato destino 'f', devolva o complexo 
 *      equivalente convertido para o formato especificado.
 */
cplx converte_CPLX(cplx a, t_formato f) {
    if (a.f == f) return a;
    cplx res;
    res.f = f;
    if (f == RETANGULAR) {
        res.rec.real = re_CPLX(a);
        res.rec.imag = img_CPLX(a);
    } else {
        res.pol.modulo = mod_CPLX(a);
        res.pol.arg = arg_CPLX(a);
    }
    return res;
}

/*
 * 3.b) Dado um número real 'r' e um formato 'f', crie e devolva um CPLX
 *      com valor real 'r' (e parte imaginária 0.0) no formato 'f'.
 */
cplx real_para_CPLX(double r, t_formato f) {
    cplx res;
    res.f = f;
    if (f == RETANGULAR) {
        res.rec.real = r;
        res.rec.imag = 0.0;
    } else {
        res.pol.modulo = fabs(r);
        res.pol.arg = (r < 0.0) ? M_PI : 0.0;
    }
    return res;
}

/* =============================================================================
 * 4. OPERAÇÕES ARITMÉTICAS ENTRE COMPLEXOS
 * Observação: O resultado deve ser devolvido no mesmo formato de 'a'.
 * ============================================================================= */

/*
 * 4.a) Soma entre dois números complexos (a + b).
 *      Dica: Realizar a soma na forma retangular e converter para o formato de 'a'.
 */
cplx somar_CPLX(cplx a, cplx b) {
    cplx res;
    res.f = RETANGULAR;
    res.rec.real = re_CPLX(a) + re_CPLX(b);
    res.rec.imag = img_CPLX(a) + img_CPLX(b);
    return converte_CPLX(res, a.f);
}

/*
 * 4.b) Subtração entre dois números complexos (a - b).
 *      Dica: Realizar a subtração na forma retangular e converter para o formato de 'a'.
 */
cplx subtrair_CPLX(cplx a, cplx b) {
    cplx res;
    res.f = RETANGULAR;
    res.rec.real = re_CPLX(a) - re_CPLX(b);
    res.rec.imag = img_CPLX(a) - img_CPLX(b);
    return converte_CPLX(res, a.f);
}

/*
 * 4.c) Multiplicação entre dois números complexos (a * b).
 *      Dica: Na forma polar, modulo = mod(a)*mod(b) e arg = arg(a)+arg(b).
 */
cplx cplx_mult_CPLX(cplx a, cplx b) {
    cplx res;
    res.f = POLAR;
    res.pol.modulo = mod_CPLX(a) * mod_CPLX(b);
    res.pol.arg = normaliza_angulo(arg_CPLX(a) + arg_CPLX(b));
    return converte_CPLX(res, a.f);
}

/*
 * 4.d) Divisão entre dois números complexos (a / b).
 *      Dica: Na forma polar, modulo = mod(a)/mod(b) e arg = arg(a)-arg(b).
 */
cplx dividir_CPLX(cplx a, cplx b) {
    cplx res;
    res.f = POLAR;
    res.pol.modulo = mod_CPLX(a) / mod_CPLX(b);
    res.pol.arg = normaliza_angulo(arg_CPLX(a) - arg_CPLX(b));
    return converte_CPLX(res, a.f);
}

/* =============================================================================
 * 5. OPERAÇÕES ARITMÉTICAS ENTRE REAL E COMPLEXO
 * O resultado deve ser devolvido no formato do complexo envolvido ('a').
 * ============================================================================= */

/* 5.a) Soma: r + a */
cplx somar_real_CPLX(double r, cplx a) {
    cplx res;
    res.f = RETANGULAR;
    res.rec.real = r + re_CPLX(a);
    res.rec.imag = img_CPLX(a);
    return converte_CPLX(res, a.f);
}

/* 5.b) Subtração: r - a */
cplx subtrair_real_CPLX(double r, cplx a) {
    cplx res;
    res.f = RETANGULAR;
    res.rec.real = r - re_CPLX(a);
    res.rec.imag = -img_CPLX(a);
    return converte_CPLX(res, a.f);
}

/* 5.c) Subtração: a - r */
cplx subtrair_CPLX_real(cplx a, double r) {
    cplx res;
    res.f = RETANGULAR;
    res.rec.real = re_CPLX(a) - r;
    res.rec.imag = img_CPLX(a);
    return converte_CPLX(res, a.f);
}

/* 5.d) Multiplicação por escalar real: a * r */
cplx real_mult_CPLX(cplx a, double r) {
    cplx res;
    res.f = POLAR;
    res.pol.modulo = mod_CPLX(a) * fabs(r);
    double ang = arg_CPLX(a) + (r < 0.0 ? M_PI : 0.0);
    res.pol.arg = normaliza_angulo(ang);
    return converte_CPLX(res, a.f);
}

/* 5.e) Divisão: a / r */
cplx dividir_CPLX_real(cplx a, double r) {
    cplx res;
    res.f = POLAR;
    res.pol.modulo = mod_CPLX(a) / fabs(r);
    double ang = arg_CPLX(a) - (r < 0.0 ? M_PI : 0.0);
    res.pol.arg = normaliza_angulo(ang);
    return converte_CPLX(res, a.f);
}

/* 5.f) Divisão: r / a */
cplx dividir_real_CPLX(double r, cplx a) {
    cplx res;
    res.f = POLAR;
    res.pol.modulo = fabs(r) / mod_CPLX(a);
    double ang = (r < 0.0 ? M_PI : 0.0) - arg_CPLX(a);
    res.pol.arg = normaliza_angulo(ang);
    return converte_CPLX(res, a.f);
}

/* =============================================================================
 * 6. FUNÇÕES AVANÇADAS E ESPECIAIS
 * ============================================================================= */

/*
 * 6.a) Devolva o conjugado do número complexo 'a'. Mantenha o formato de 'a'.
 *      - Em RETANGULAR: troca o sinal de imag.
 *      - Em POLAR: troca o sinal de arg.
 */
cplx conjugado_CPLX(cplx a) {
    cplx res = a;
    if (a.f == RETANGULAR) {
        res.rec.imag = -a.rec.imag;
    } else {
        res.pol.arg = normaliza_angulo(-a.pol.arg);
    }
    return res;
}

/*
 * 6.b) Dado 'a' e um expoente real 'n', devolva o resultado de a^n (Fórmula de De Moivre).
 *      - Modulo resultante: mod(a)^n
 *      - Argumento resultante: arg(a) * n (normalizado)
 *      - Devolva no formato original de 'a'.
 */
cplx potencia_CPLX(cplx a, double n) {
    cplx res;
    res.f = POLAR;
    res.pol.modulo = pow(mod_CPLX(a), n);
    res.pol.arg = normaliza_angulo(arg_CPLX(a) * n);
    return converte_CPLX(res, a.f);
}

/*
 * 6.c) Dado 'a', devolva e^a (Exponencial Complexa).
 *      - e^(x + iy) = e^x * (cos(y) + i*sin(y)) => Modulo = e^re(a), Arg = img(a)
 *      - Devolva no formato original de 'a'.
 */
cplx exp_CPLX(cplx a) {
    cplx res;
    res.f = POLAR;
    res.pol.modulo = exp(re_CPLX(a));
    res.pol.arg = normaliza_angulo(img_CPLX(a));
    return converte_CPLX(res, a.f);
}

/*
 * 6.d) Dado 'c' e um inteiro positivo 'n', preencha o vetor 'resultados' 
 *      com as n raízes enézimas de 'c'.
 *      - Modulo de cada raiz: mod(c)^(1/n)
 *      - Argumento da k-ésima raiz (k de 0 a n-1): (arg(c) + 2*PI*k) / n
 *      - Cada raiz no vetor deve estar no formato original de 'c'.
 */
void raizes_CPLX(cplx c, int n, cplx resultados[]) {
    if (n <= 0) return;
    double r = mod_CPLX(c);
    double theta = arg_CPLX(c);
    double r_raiz = pow(r, 1.0 / (double)n);
    for (int k = 0; k < n; k++) {
        cplx rk;
        rk.f = POLAR;
        rk.pol.modulo = r_raiz;
        rk.pol.arg = normaliza_angulo((theta + 2.0 * M_PI * (double)k) / (double)n);
        resultados[k] = converte_CPLX(rk, c.f);
    }
}

/* =============================================================================
 * 7. ENTRADA E SAÍDA (I/O)
 * ============================================================================= */

/*
 * 7.a) Imprima o valor de 'a' com 2 casas decimais de acordo com seu formato:
 *      - RETANGULAR: "%.2f + %.2fi\n" ou "%.2f - %.2fi\n"
 *      - POLAR:       "%.2f < %.2f rad\n"
 *      (Trate valores muito próximos de zero com fabs(val) < 1e-9 -> 0.00)
 */
void imprimir_CPLX(cplx a) {
    if (a.f == RETANGULAR) {
        double r = sanitizar(a.rec.real);
        double i = sanitizar(a.rec.imag);
        char sinal = (i >= 0.0) ? '+' : '-';
        printf("%.2f %c %.2fi\n", r, sinal, fabs(i));
    } else {
        double m = sanitizar(a.pol.modulo);
        double t = sanitizar(normaliza_angulo(a.pol.arg));
        printf("%.2f < %.2f rad\n", m, t);
    }
}

/*
 * 7.b) Lê um complexo da entrada padrão:
 *      - Caractere 'R' ou 'r': lê real e imag (dois doubles)
 *      - Caractere 'P' ou 'p': lê modulo e arg (dois doubles)
 */
cplx ler_CPLX() {
    char tipo;
    double v1, v2;
    cplx c;
    if (scanf(" %c %lf %lf", &tipo, &v1, &v2) == 3) {
        if (tipo == 'P' || tipo == 'p') {
            c.f = POLAR;
            c.pol.modulo = v1;
            c.pol.arg = normaliza_angulo(v2);
        } else {
            c.f = RETANGULAR;
            c.rec.real = v1;
            c.rec.imag = v2;
        }
    }
    return c;
}

/* =============================================================================
 * 8. FUNÇÃO PRINCIPAL (Bateria de Testes)
 * 
 * Ordem de leitura da entrada:
 * 1. n (inteiro): ordem das raízes enézimas (n >= 1)
 * 2. r (double): escalar real / expoente
 * 3. f_out_char (char: 'R'/'r' ou 'P'/'p'): formato desejado de saída
 * 4. Complexo A (usando ler_CPLX)
 * 5. Complexo B (usando ler_CPLX)
 * 
 * Regra de exibição:
 * Todos os resultados complexos impressos devem ser convertidos para o formato f_out.
 * ============================================================================= */
int main() {
    // 1. Declare as variáveis necessárias (n, r, f_out_char, a, b, etc.)
    int n;
    double r;
    char f_out_char;

    // 2. Realize a leitura dos dados de entrada (n, r, formato de saída, A e B)
    if (scanf("%d %lf %c", &n, &r, &f_out_char) != 3) {
        return 0;
    }

    t_formato f_out = (f_out_char == 'P' || f_out_char == 'p') ? POLAR : RETANGULAR;

    cplx A = ler_CPLX();
    cplx B = ler_CPLX();

    // 3. Exibição de A e B no formato de saída definido
    printf("A = ");
    imprimir_CPLX(converte_CPLX(A, f_out));

    printf("B = ");
    imprimir_CPLX(converte_CPLX(B, f_out));

    // 4. Propriedades fundamentais (use fabs para evitar -0.00)
    printf("PARTS A: MOD=%.2f ARG=%.2f RE=%.2f IMG=%.2f\n",
        sanitizar(mod_CPLX(A)), sanitizar(arg_CPLX(A)),
        sanitizar(re_CPLX(A)), sanitizar(img_CPLX(A)));
    printf("PARTS B: MOD=%.2f ARG=%.2f RE=%.2f IMG=%.2f\n",
        sanitizar(mod_CPLX(B)), sanitizar(arg_CPLX(B)),
        sanitizar(re_CPLX(B)), sanitizar(img_CPLX(B)));

    //printf("PARTS A: MOD=%.2f ARG=%.2f RE=%.2f IMG=%.2f\n", ...);
    //printf("PARTS B: MOD=%.2f ARG=%.2f RE=%.2f IMG=%.2f\n", ...);

    // 5. Conjugados
    printf("CONJ(A) = ");
    imprimir_CPLX(converte_CPLX(conjugado_CPLX(A), f_out));

    printf("CONJ(B) = ");
    imprimir_CPLX(converte_CPLX(conjugado_CPLX(B), f_out));

    // 6. Operações entre Complexos
    printf("A + B = ");
    imprimir_CPLX(converte_CPLX(somar_CPLX(A, B), f_out));

    printf("A - B = ");
    imprimir_CPLX(converte_CPLX(subtrair_CPLX(A, B), f_out));

    printf("A * B = ");
    imprimir_CPLX(converte_CPLX(cplx_mult_CPLX(A, B), f_out));

    printf("A / B = ");
    imprimir_CPLX(converte_CPLX(dividir_CPLX(A, B), f_out));

    // 7. Operações com o Escalar Real R
    printf("R + A = ");
    imprimir_CPLX(converte_CPLX(somar_real_CPLX(r, A), f_out));

    printf("R - A = ");
    imprimir_CPLX(converte_CPLX(subtrair_real_CPLX(r, A), f_out));

    printf("A - R = ");
    imprimir_CPLX(converte_CPLX(subtrair_CPLX_real(A, r), f_out));

    printf("R * A = ");
    imprimir_CPLX(converte_CPLX(real_mult_CPLX(A, r), f_out));

    printf("A / R = ");
    imprimir_CPLX(converte_CPLX(dividir_CPLX_real(A, r), f_out));

    printf("R / A = ");
    imprimir_CPLX(converte_CPLX(dividir_real_CPLX(r, A), f_out));

    // 8. Potência e Exponencial
    printf("A ^ R = ");
    imprimir_CPLX(converte_CPLX(potencia_CPLX(A, r), f_out));

    printf("exp(A) = ");
    imprimir_CPLX(converte_CPLX(exp_CPLX(A), f_out));

    // 9. Raízes Enézimas
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
    /* lembrando que o código já estava pronto, só adaptei para ficar em um arquivo só, eu tinha feito o de antes que eram 3 arquivos ;) */
}