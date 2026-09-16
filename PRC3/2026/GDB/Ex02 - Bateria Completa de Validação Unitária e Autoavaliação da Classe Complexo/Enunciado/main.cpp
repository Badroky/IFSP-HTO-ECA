/* =============================================================================
 * DISCIPLINA: Programação Orientada a Objetos / Sistemas de Controle
 * ATIVIDADE: Bateria Completa de Validação Unitária (Cobertura Total da API)
 * ARQUIVO: main.cpp
 * ============================================================================= */

#include "Complexo.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ANSI_VERDE    "\x1b[32m"
#define ANSI_VERMELHO "\x1b[31m"
#define ANSI_RESET    "\x1b[0m"

static void imprimirStatus(const std::string& rotulo, bool aprovado) {
    std::cout << rotulo << ": ";
    if (aprovado) {
        std::cout << ANSI_VERDE << "APROVADO" << ANSI_RESET << "\n";
    } else {
        std::cout << ANSI_VERMELHO << "REPROVADO" << ANSI_RESET << "\n";
    }
}

static bool check(double obtido, double esperado, double tol = 1e-4) {
    return std::abs(obtido - esperado) <= tol;
}

static bool check(const Complexo& obtido, const Complexo& esperado, double tol = 1e-4) {
    return check(obtido.real(), esperado.real(), tol) && check(obtido.imag(), esperado.imag(), tol);
}

int main() {
    bool todos_ok = true;

    // TESTE 01: CONSTRUTORES, ATRIBUICAO ESCALAR, CASTS E GETTERS
    Complexo c_padrao;
    Complexo c_double(3.0, 4.0, RETANGULAR);
    Complexo c_float(3.0f, 4.0f, RETANGULAR);
    Complexo c_int(3, 4, RETANGULAR);
    Complexo c_ll(3LL, 4LL, RETANGULAR);
    Complexo c_copia(c_double);

    Complexo c_atrib;
    c_atrib = c_double;

    Complexo c_atrib_d;
    c_atrib_d = 7.5;

    Complexo c_atrib_i;
    c_atrib_i = 10;

    Complexo c_polar = c_double.converterPara(POLAR);

    double d_val = static_cast<double>(c_double);
    float f_val = static_cast<float>(c_double);
    int i_val = static_cast<int>(c_double);
    bool b_val = static_cast<bool>(c_double);
    bool b_zero = static_cast<bool>(c_padrao);

    bool t01 = check(c_padrao.real(), 0.0) && check(c_padrao.imag(), 0.0)
            && check(c_double.real(), 3.0) && check(c_double.imag(), 4.0)
            && check(c_float.real(), 3.0) && check(c_int.real(), 3.0) && check(c_ll.real(), 3.0)
            && check(c_copia.real(), 3.0) && check(c_atrib.real(), 3.0)
            && check(c_atrib_d.real(), 7.5) && check(c_atrib_d.imag(), 0.0)
            && check(c_atrib_i.real(), 10.0) && check(c_atrib_i.imag(), 0.0)
            && (c_polar.formato() == POLAR) && check(c_polar.modulo(), 5.0)
            && check(c_polar.arg(), std::atan2(4.0, 3.0))
            && check(d_val, 3.0) && check(f_val, 3.0f) && (i_val == 3)
            && b_val && !b_zero;

    imprimirStatus("[TESTE 01] Construtores e Conversao de Formato", t01);
    todos_ok = todos_ok && t01;

    // TESTE 02: OPERACOES ARITMETICAS BASICAS (COMPLEXO x COMPLEXO)
    Complexo z1(2.0, 3.0, RETANGULAR);
    Complexo z2(4.0, -1.0, RETANGULAR);

    Complexo soma_cc = z1 + z2;
    Complexo sub_cc = z1 - z2;
    Complexo mul_cc = z1 * z2;
    Complexo div_cc = z1 / z2;

    bool t02 = check(soma_cc, Complexo(6.0, 2.0))
            && check(sub_cc, Complexo(-2.0, 4.0))
            && check(mul_cc, Complexo(11.0, 10.0))
            && check(div_cc, Complexo(5.0 / 17.0, 14.0 / 17.0));

    imprimirStatus("[TESTE 02] Operacoes Aritmeticas Basicas", t02);
    todos_ok = todos_ok && t02;

    // TESTE 03: ARITMETICA COM ESCALAR REAL E COMUTATIVIDADE
    Complexo z(2.0, 5.0);

    bool t03 = check(z + 3.0, Complexo(5.0, 5.0))
            && check(3.0 + z, Complexo(5.0, 5.0))
            && check(z - 1.0, Complexo(1.0, 5.0))
            && check(5.0 - z, Complexo(3.0, -5.0))
            && check(z * 2.0, Complexo(4.0, 10.0))
            && check(2.0 * z, Complexo(4.0, 10.0))
            && check(z / 2.0, Complexo(1.0, 2.5))
            && check(29.0 / z, Complexo(2.0, -5.0));

    imprimirStatus("[TESTE 03] Aritmetica com Escalar e Comutatividade", t03);
    todos_ok = todos_ok && t03;

    // TESTE 04: ATRIBUICAO COMPOSTA (COMPLEXO E DOUBLE)
    Complexo ac(1.0, 1.0);
    ac += Complexo(2.0, 3.0);
    ac -= Complexo(1.0, -1.0);
    ac += 3.0;
    ac -= 1.0;
    ac *= 2.0;
    ac /= 2.0;
    ac *= Complexo(1.0, 1.0);
    ac /= Complexo(1.0, 1.0);

    Complexo ac_pot(1.0, 1.0);
    ac_pot ^= 2.0;
    ac_pot ^= Complexo(1.0, 0.0, RETANGULAR);

    bool t04 = check(ac, Complexo(4.0, 5.0)) && check(ac_pot, Complexo(0.0, 2.0));
    imprimirStatus("[TESTE 04] Atribuicao Composta", t04);
    todos_ok = todos_ok && t04;

    // TESTE 05: OPERADORES UNARIOS E INCREMENTOS
    Complexo un(3.0, -4.0);
    Complexo neg = -un;

    Complexo inc = un;
    Complexo pre_inc = ++inc;
    Complexo pos_inc = inc++;

    Complexo pre_dec = --inc;
    Complexo pos_dec = inc--;

    bool t05 = check(neg, Complexo(-3.0, 4.0))
            && check(pre_inc, Complexo(4.0, -4.0))
            && check(pos_inc, Complexo(4.0, -4.0))
            && check(pre_dec, Complexo(4.0, -4.0))
            && check(pos_dec, Complexo(4.0, -4.0))
            && check(inc, Complexo(3.0, -4.0));

    imprimirStatus("[TESTE 05] Operadores Unarios e Incrementos", t05);
    todos_ok = todos_ok && t05;

    // TESTE 06: COMPARADORES E IGUALDADE COM EPSILON
    Complexo eq1(2.0, 3.0);
    Complexo eq2(2.0 + 1e-10, 3.0 - 1e-10);
    Complexo dif(2.0, 4.0);
    Complexo real_puro(5.0, 0.0);

    bool t06 = (eq1 == eq2)
            && !(eq1 != eq2)
            && (eq1 != dif)
            && (real_puro == 5.0)
            && (5.0 == real_puro)
            && !(real_puro != 5.0)
            && !(5.0 != real_puro)
            && (eq1 != 2.0)
            && (2.0 != eq1);

    imprimirStatus("[TESTE 06] Comparadores e Igualdade com Epsilon", t06);
    todos_ok = todos_ok && t06;

    // TESTE 07: OPERADORES DE POTENCIACAO
    Complexo base(1.0, 1.0);
    Complexo pot_d = base ^ 2.0;
    Complexo pot_i = base ^ 2;
    Complexo pot_c = base ^ Complexo(2.0, 0.0);
    Complexo base_real_c = 2.0 ^ Complexo(3.0, 0.0);

    bool t07 = check(pot_d, Complexo(0.0, 2.0))
            && check(pot_i, Complexo(0.0, 2.0))
            && check(pot_c, Complexo(0.0, 2.0))
            && check(base_real_c, Complexo(8.0, 0.0));

    imprimirStatus("[TESTE 07] Potenciacao Real e Complexa", t07);
    todos_ok = todos_ok && t07;

    // TESTE 08: CONJUGADO, POTENCIA, EXPONENCIAL E LOGARITMO
    Complexo conj_in(3.0, -7.0);
    Complexo conj_res = conj_in.conjugado();
    Complexo pot_res = Complexo(2.0, 0.0).potencia(3.0);

    Complexo euler(0.0, M_PI);
    Complexo exp_membro = euler.exponencial();
    Complexo exp_amiga = exp(euler);

    Complexo log_in(-1.0, 0.0);
    Complexo log_membro = log_in.log();
    Complexo log_amiga = log(log_in);

    bool t08 = check(conj_res, Complexo(3.0, 7.0))
            && check(pot_res, Complexo(8.0, 0.0))
            && check(exp_membro, Complexo(-1.0, 0.0))
            && check(exp_amiga, Complexo(-1.0, 0.0))
            && check(log_membro.real(), 0.0) && check(log_membro.imag(), M_PI)
            && check(log_amiga.real(), 0.0) && check(log_amiga.imag(), M_PI);

    imprimirStatus("[TESTE 08] Conjugado, Exponencial e Logaritmo", t08);
    todos_ok = todos_ok && t08;

    // TESTE 09: RAIZES ENEZIMAS (DE MOIVRE)
    Complexo raiz_in(-16.0, 0.0);
    Complexo rz[4];
    raiz_in.raizes(4, rz);

    bool t09 = check(rz[0], Complexo(1.41421356, 1.41421356))
            && check(rz[1], Complexo(-1.41421356, 1.41421356))
            && check(rz[2], Complexo(-1.41421356, -1.41421356))
            && check(rz[3], Complexo(1.41421356, -1.41421356));

    imprimirStatus("[TESTE 09] Raizes Enezimas", t09);
    todos_ok = todos_ok && t09;

    // TESTE 10: FUNCOES TRIGONOMETRICAS COMPLEXAS
    Complexo ang(1.0, 1.0);
    Complexo sin_m = ang.sin();
    Complexo cos_m = ang.cos();
    Complexo tan_m = ang.tan();

    Complexo sin_a = sin(ang);
    Complexo cos_a = cos(ang);
    Complexo tan_a = tan(ang);

    Complexo sin_esp(std::sin(1.0) * std::cosh(1.0), std::cos(1.0) * std::sinh(1.0));
    Complexo cos_esp(std::cos(1.0) * std::cosh(1.0), -std::sin(1.0) * std::sinh(1.0));

    bool t10 = check(sin_m, sin_esp) && check(sin_a, sin_esp)
            && check(cos_m, cos_esp) && check(cos_a, cos_esp)
            && check(tan_m, sin_esp / cos_esp) && check(tan_a, sin_esp / cos_esp);

    imprimirStatus("[TESTE 10] Funcoes Trigonometricas", t10);
    todos_ok = todos_ok && t10;

    // TESTE 11: FUNCOES HIPERBOLICAS COMPLEXAS
    Complexo hip(0.5, 0.8);
    Complexo sinh_m = hip.sinh();
    Complexo cosh_m = hip.cosh();
    Complexo tanh_m = hip.tanh();

    Complexo sinh_a = sinh(hip);
    Complexo cosh_a = cosh(hip);
    Complexo tanh_a = tanh(hip);

    Complexo sinh_esp(std::sinh(0.5) * std::cos(0.8), std::cosh(0.5) * std::sin(0.8));
    Complexo cosh_esp(std::cosh(0.5) * std::cos(0.8), std::sinh(0.5) * std::sin(0.8));

    bool t11 = check(sinh_m, sinh_esp) && check(sinh_a, sinh_esp)
            && check(cosh_m, cosh_esp) && check(cosh_a, cosh_esp)
            && check(tanh_m, sinh_esp / cosh_esp) && check(tanh_a, sinh_esp / cosh_esp);

    imprimirStatus("[TESTE 11] Funcoes Hiperbolicas", t11);
    todos_ok = todos_ok && t11;

    // TESTE 12: FUNCOES LIVRES (STL/ADL), FLUXOS I/O E LITERAIS DE USUARIO
    Complexo c_stl(3.0, 4.0);
    double r_f = real(c_stl);
    double i_f = imag(c_stl);
    double m_f = abs(c_stl);
    double a_f = arg(c_stl);

    std::stringstream ss_out;
    ss_out << c_stl;

    Complexo c_cin;
    std::stringstream ss_in("7.5 -2.5");
    ss_in >> c_cin;

    Complexo lit_i_ld = 2.5_i;
    Complexo lit_j_ld = 3.5_j;
    Complexo lit_i_ull = 4_i;
    Complexo lit_j_ull = 5_j;

    double ang_deg_ld = 180.0_deg;
    double ang_deg_ull = 180_deg;
    double ang_rad_ld = 3.141592653589793_rad;
    double ang_rad_ull = 3_rad;

    bool t12 = check(r_f, 3.0) && check(i_f, 4.0) && check(m_f, 5.0)
            && check(a_f, std::atan2(4.0, 3.0))
            && (ss_out.str() == "3.00 + 4.00i")
            && check(c_cin, Complexo(7.5, -2.5))
            && check(lit_i_ld, Complexo(0.0, 2.5))
            && check(lit_j_ld, Complexo(0.0, 3.5))
            && check(lit_i_ull, Complexo(0.0, 4.0))
            && check(lit_j_ull, Complexo(0.0, 5.0))
            && check(ang_deg_ld, M_PI)
            && check(ang_deg_ull, M_PI)
            && check(ang_rad_ld, 3.141592653589793)
            && check(ang_rad_ull, 3.0);

    imprimirStatus("[TESTE 12] Funcoes Livres e Literais de Usuario", t12);
    todos_ok = todos_ok && t12;

    std::cout << "RESULTADO GLOBAL: ";
    if (todos_ok) {
        std::cout << ANSI_VERDE << "TODOS OS RECURSOS FORAM VALIDADOS COM SUCESSO" << ANSI_RESET << "\n";
    } else {
        std::cout << ANSI_VERMELHO << "FALHA NA VALIDACAO DE UM OU MAIS RECURSOS" << ANSI_RESET << "\n";
    }

    return 0;
}