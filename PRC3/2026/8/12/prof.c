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
    // --preencher--
} t_formato;

/* 
 * 1.b) Especifique a estrutura para a representação polar:
 *      - modulo: valor double (r >= 0)
 *      - arg:    argumento/fase double (em radianos)
 */
typedef struct {
    // --preencher--
} t_polar;

/* 
 * 1.c) Especifique a estrutura para a representação retangular:
 *      - real: parte real double
 *      - imag: parte imaginária double
 */
typedef struct {
    // --preencher--
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
static double normaliza_angulo(double theta) {
    while (theta <= -M_PI) theta += 2.0 * M_PI;
    while (theta > M_PI)  theta -= 2.0 * M_PI;
    if (fabs(theta) < 1e-9) theta = 0.0;
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
    // --preencher--
}

/*
 * 2.b) Dado um complexo 'a', devolva a sua parte imaginária.
 *      - Se estiver em POLAR: imag = modulo * sin(arg)
 */
double img_CPLX(cplx a) {
    // --preencher--
}

/*
 * 2.c) Dado um complexo 'a', devolva o seu módulo (magnitude).
 *      - Se estiver em RETANGULAR: modulo = sqrt(real^2 + imag^2) ou hypot(real, imag)
 */
double mod_CPLX(cplx a) {
    // --preencher--
}

/*
 * 2.d) Dado um complexo 'a', devolva o seu argumento em radianos (-PI, PI].
 *      - Se estiver em RETANGULAR: arg = atan2(imag, real)
 */
double arg_CPLX(cplx a) {
    // --preencher--
}

/* =============================================================================
 * 3. CONVERSÃO DE FORMATO E DE TIPO
 * ============================================================================= */

/*
 * 3.a) Dado um complexo 'a' e um formato destino 'f', devolva o complexo 
 *      equivalente convertido para o formato especificado.
 */
cplx converte_CPLX(cplx a, t_formato f) {
    // --preencher--
}

/*
 * 3.b) Dado um número real 'r' e um formato 'f', crie e devolva um CPLX
 *      com valor real 'r' (e parte imaginária 0.0) no formato 'f'.
 */
cplx real_para_CPLX(double r, t_formato f) {
    // --preencher--
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
    // --preencher--
}

/*
 * 4.b) Subtração entre dois números complexos (a - b).
 *      Dica: Realizar a subtração na forma retangular e converter para o formato de 'a'.
 */
cplx subtrair_CPLX(cplx a, cplx b) {
    // --preencher--
}

/*
 * 4.c) Multiplicação entre dois números complexos (a * b).
 *      Dica: Na forma polar, modulo = mod(a)*mod(b) e arg = arg(a)+arg(b).
 */
cplx cplx_mult_CPLX(cplx a, cplx b) {
    // --preencher--
}

/*
 * 4.d) Divisão entre dois números complexos (a / b).
 *      Dica: Na forma polar, modulo = mod(a)/mod(b) e arg = arg(a)-arg(b).
 */
cplx dividir_CPLX(cplx a, cplx b) {
    // --preencher--
}

/* =============================================================================
 * 5. OPERAÇÕES ARITMÉTICAS ENTRE REAL E COMPLEXO
 * O resultado deve ser devolvido no formato do complexo envolvido ('a').
 * ============================================================================= */

/* 5.a) Soma: r + a */
cplx somar_real_CPLX(double r, cplx a) {
    // --preencher--
}

/* 5.b) Subtração: r - a */
cplx subtrair_real_CPLX(double r, cplx a) {
    // --preencher--
}

/* 5.c) Subtração: a - r */
cplx subtrair_CPLX_real(cplx a, double r) {
    // --preencher--
}

/* 5.d) Multiplicação por escalar real: a * r */
cplx real_mult_CPLX(cplx a, double r) {
    // --preencher--
}

/* 5.e) Divisão: a / r */
cplx dividir_CPLX_real(cplx a, double r) {
    // --preencher--
}

/* 5.f) Divisão: r / a */
cplx dividir_real_CPLX(double r, cplx a) {
    // --preencher--
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
    // --preencher--
}

/*
 * 6.b) Dado 'a' e um expoente real 'n', devolva o resultado de a^n (Fórmula de De Moivre).
 *      - Modulo resultante: mod(a)^n
 *      - Argumento resultante: arg(a) * n (normalizado)
 *      - Devolva no formato original de 'a'.
 */
cplx potencia_CPLX(cplx a, double n) {
    // --preencher--
}

/*
 * 6.c) Dado 'a', devolva e^a (Exponencial Complexa).
 *      - e^(x + iy) = e^x * (cos(y) + i*sin(y)) => Modulo = e^re(a), Arg = img(a)
 *      - Devolva no formato original de 'a'.
 */
cplx exp_CPLX(cplx a) {
    // --preencher--
}

/*
 * 6.d) Dado 'c' e um inteiro positivo 'n', preencha o vetor 'resultados' 
 *      com as n raízes enézimas de 'c'.
 *      - Modulo de cada raiz: mod(c)^(1/n)
 *      - Argumento da k-ésima raiz (k de 0 a n-1): (arg(c) + 2*PI*k) / n
 *      - Cada raiz no vetor deve estar no formato original de 'c'.
 */
void raizes_CPLX(cplx c, int n, cplx resultados[]) {
    // --preencher--
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
    // --preencher--
}

/*
 * 7.b) Lê um complexo da entrada padrão:
 *      - Caractere 'R' ou 'r': lê real e imag (dois doubles)
 *      - Caractere 'P' ou 'p': lê modulo e arg (dois doubles)
 */
cplx ler_CPLX() {
    // --preencher--
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
    // --preencher--

    // 2. Realize a leitura dos dados de entrada (n, r, formato de saída, A e B)
    // --preencher--

    // 3. Exibição de A e B no formato de saída definido
    printf("A = ");
    // --preencher: converter e imprimir A--

    printf("B = ");
    // --preencher: converter e imprimir B--

    // 4. Propriedades fundamentais (use fabs para evitar -0.00)
    // --preencher: imprimir partes de A e partes de B no formato especificado--
    
    //printf("PARTS A: MOD=%.2f ARG=%.2f RE=%.2f IMG=%.2f\n", ...);
    //printf("PARTS B: MOD=%.2f ARG=%.2f RE=%.2f IMG=%.2f\n", ...);

    // 5. Conjugados
    printf("CONJ(A) = ");
    // --preencher: calcular conjugado de A, converter e imprimir--

    printf("CONJ(B) = ");
    // --preencher: calcular conjugado de B, converter e imprimir--

    // 6. Operações entre Complexos
    printf("A + B = ");
    // --preencher: somar A e B, converter e imprimir--

    printf("A - B = ");
    // --preencher: subtrair B de A, converter e imprimir--

    printf("A * B = ");
    // --preencher: multiplicar A por B, converter e imprimir--

    printf("A / B = ");
    // --preencher: dividir A por B, converter e imprimir--

    // 7. Operações com o Escalar Real R
    printf("R + A = ");
    // --preencher: somar r com A, converter e imprimir--

    printf("R - A = ");
    // --preencher: subtrair A de r, converter e imprimir--

    printf("A - R = ");
    // --preencher: subtrair r de A, converter e imprimir--

    printf("R * A = ");
    // --preencher: multiplicar r por A, converter e imprimir--

    printf("A / R = ");
    // --preencher: dividir A por r, converter e imprimir--

    printf("R / A = ");
    // --preencher: dividir r por A, converter e imprimir--

    // 8. Potência e Exponencial
    printf("A ^ R = ");
    // --preencher: calcular A elevado a r, converter e imprimir--

    printf("exp(A) = ");
    // --preencher: calcular exp(A), converter e imprimir--

    // 9. Raízes Enézimas
    // --preencher: alocar vetor para n complexos, chamar raizes_CPLX,
    //              imprimir cada raiz no formato "Raiz %d: " e liberar memória--
    // printf("RAIZES DE A (ordem %d):\n", n);
    // printf("Raiz %d: ", k);

    return 0;
}
