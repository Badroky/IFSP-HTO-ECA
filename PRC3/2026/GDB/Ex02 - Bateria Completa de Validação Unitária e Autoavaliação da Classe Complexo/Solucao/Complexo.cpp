/* =============================================================================
 * DISCIPLINA: Programação Orientada a Objetos / Sistemas de Controle
 * ARQUIVO: Complexo.cpp
 *
 * IMPLEMENTAÇÃO DE ALTA PRECISÃO DA CLASSE COMPLEXO
 *
 * FUNDAMENTAÇÃO CONCEITUAL:
 * Um número complexo z pode ser interpretado geometricamente como um ponto (ou fasor)
 * no plano de Argand-Gauss através de duas métricas canônicas equivalentes:
 *
 * 1. Forma Retangular (Cartesiana):
 *    z = a + bi, onde 'a' representa a projeção no eixo real Re(z) e 'b' a projeção
 *    no eixo imaginário Im(z), satisfazendo a propriedade fundamental i^2 = -1.
 *
 * 2. Forma Polar (Trigonométrica):
 *    z = r * (cos(theta) + i*sin(theta)) = r * e^(i*theta) = r < theta, onde 'r' representa o módulo
 *    ou distância euclidiana à origem (r = |z| >= 0) e 'theta' representa o argumento
 *    angular (fase) orientado em radianos no intervalo (-pi, pi].
 *
 * ARQUITETURA COMPUTACIONAL:
 * - Adota união discriminada (Tagged Union): a memória física é compartilhada
 *   entre a struct cartesiana 'rec' e a struct polar 'pol'.
 * - A tag 'formatoAtual' determina qual representação está ativa e sincronizada.
 * - Toda operação aritmética mista preserva o 'formatoAtual' da instância à esquerda (*this).
 * ============================================================================= */

#include "Complexo.hpp"
#include <iomanip>
#include <sstream>
#include <cmath>

// =============================================================================
// FUNÇÕES UTILITÁRIAS PRIVADAS E ESTÁTICAS
// =============================================================================

/**
 * @brief Normalização do Argumento Angular no Círculo Trigonométrico.
 * Garante que o ângulo pertença estritamente ao intervalo (-PI, PI].
 * Se |theta| < EPSILON, força +0.0 para evitar a geração de "-0.00" sob IEEE-754.
 */
double Complexo::normalizarAngulo(double theta) {
    theta = std::fmod(theta, 2.0 * M_PI);
    while (theta > M_PI)  theta -= 2.0 * M_PI;
    while (theta <= -M_PI) theta += 2.0 * M_PI;
    if (std::abs(theta) < EPSILON) theta = 0.0;
    return theta;
}

/**
 * @brief Teste de Igualdade Aproximada com Tolerância Numérica (Epsilon).
 * Compara dois escalares em ponto flutuante sob uma vizinhança de incerteza EPSILON.
 */
bool Complexo::quaseIgual(double a, double b) {
    return std::abs(a - b) < EPSILON;
}

// =============================================================================
// 1. FORMA CANÔNICA ORTODOXA
// =============================================================================

/**
 * @brief Construtor Padrão (Elemento Neutro Aditivo).
 * Inicializa como 0.0 + 0.0i em formato RETANGULAR.
 */
Complexo::Complexo() : formatoAtual(RETANGULAR) {
    rec.real = 0.0;
    rec.imag = 0.0;
}

/**
 * @brief Construtor de Cópia (Semântica de Valor).
 * Clona a tag discriminante e copia estritamente o payload ativo da união.
 */
Complexo::Complexo(const Complexo& outro) : formatoAtual(outro.formatoAtual) {
    if (formatoAtual == RETANGULAR) {
        rec = outro.rec;
    } else {
        pol = outro.pol;
    }
}

/**
 * @brief Operador de Atribuição por Cópia (Copy Assignment).
 * Trata autoatribuição e copia os dados correspondentes ao formato ativo de outro.
 */
Complexo& Complexo::operator=(const Complexo& outro) {
    if (this != &outro) {
        formatoAtual = outro.formatoAtual;
        if (formatoAtual == RETANGULAR) {
            rec = outro.rec;
        } else {
            pol = outro.pol;
        }
    }
    return *this;
}

/**
 * @brief Destrutor da Classe.
 * Como todos os membros residem na stack (sem ponteiros dinâmicos), é trivial.
 */
Complexo::~Complexo() {
}

// =============================================================================
// 2. CONSTRUTORES DE CONVERSÃO E TIPOS PRIMITIVOS
// =============================================================================

/**
 * @brief Construtor Principal Parametrizado.
 * Atribui coordenadas retangulares ou polares conforme a tag 'f'.
 * Em formato POLAR, normaliza automaticamente o ângulo fornecido para (-PI, PI].
 */
Complexo::Complexo(double real, double imag, Formato f) : formatoAtual(f) {
    if (f == RETANGULAR) {
        rec.real = real;
        rec.imag = imag;
    } else {
        pol.modulo = real;
        pol.arg = normalizarAngulo(imag);
    }
}

Complexo::Complexo(float real, float imag, Formato f)
    : Complexo(static_cast<double>(real), static_cast<double>(imag), f) {}

Complexo::Complexo(int real, int imag, Formato f)
    : Complexo(static_cast<double>(real), static_cast<double>(imag), f) {}

Complexo::Complexo(long long real, long long imag, Formato f)
    : Complexo(static_cast<double>(real), static_cast<double>(imag), f) {}

/**
 * @brief Atribuição Escalar a partir de double.
 * Converte a representação ativa para RETANGULAR com parte imaginária nula.
 */
Complexo& Complexo::operator=(double r) {
    formatoAtual = RETANGULAR;
    rec.real = r;
    rec.imag = 0.0;
    return *this;
}

/**
 * @brief Atribuição Escalar a partir de int.
 */
Complexo& Complexo::operator=(int r) {
    return *this = static_cast<double>(r);
}

// =============================================================================
// 3. OPERADORES DE CONVERSÃO EXPLÍCITA (CASTS)
// =============================================================================

Complexo::operator double() const {
    return real();
}

Complexo::operator float() const {
    return static_cast<float>(real());
}

Complexo::operator int() const {
    return static_cast<int>(real());
}

Complexo::operator bool() const {
    return modulo() > EPSILON;
}

// =============================================================================
// 4. MÉTODOS DE ACESSO (GETTERS) E CONVERSÃO DE FORMATO
// =============================================================================

double Complexo::real() const {
    if (formatoAtual == RETANGULAR) {
        return rec.real;
    }
    return pol.modulo * std::cos(pol.arg);
}

double Complexo::imag() const {
    if (formatoAtual == RETANGULAR) {
        return rec.imag;
    }
    return pol.modulo * std::sin(pol.arg);
}

double Complexo::modulo() const {
    if (formatoAtual == POLAR) {
        return pol.modulo;
    }
    return std::hypot(rec.real, rec.imag);
}

double Complexo::arg() const {
    if (formatoAtual == POLAR) {
        return pol.arg;
    }
    return normalizarAngulo(std::atan2(rec.imag, rec.real));
}

Formato Complexo::formato() const {
    return formatoAtual;
}

Complexo Complexo::converterPara(Formato novoFormato) const {
    if (formatoAtual == novoFormato) {
        return *this;
    }
    if (novoFormato == RETANGULAR) {
        return Complexo(real(), imag(), RETANGULAR);
    } else {
        return Complexo(modulo(), arg(), POLAR);
    }
}

// =============================================================================
// 5. OPERADORES ARITMÉTICOS BINÁRIOS
// Todos os resultados preservam o formatoAtual do operando da esquerda (*this).
// =============================================================================

Complexo Complexo::operator+(const Complexo& b) const {
    Complexo res(real() + b.real(), imag() + b.imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator-(const Complexo& b) const {
    Complexo res(real() - b.real(), imag() - b.imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator*(const Complexo& b) const {
    if (formatoAtual == POLAR && b.formatoAtual == POLAR) {
        return Complexo(pol.modulo * b.pol.modulo, normalizarAngulo(pol.arg + b.pol.arg), POLAR);
    }
    double r1 = real(), i1 = imag();
    double r2 = b.real(), i2 = b.imag();
    Complexo res(r1 * r2 - i1 * i2, r1 * i2 + i1 * r2, RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator/(const Complexo& b) const {
    if (formatoAtual == POLAR && b.formatoAtual == POLAR) {
        return Complexo(pol.modulo / b.pol.modulo, normalizarAngulo(pol.arg - b.pol.arg), POLAR);
    }
    double r1 = real(), i1 = imag();
    double r2 = b.real(), i2 = b.imag();
    double denom = r2 * r2 + i2 * i2;
    Complexo res((r1 * r2 + i1 * i2) / denom, (i1 * r2 - r1 * i2) / denom, RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator+(double r) const {
    Complexo res(real() + r, imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator-(double r) const {
    Complexo res(real() - r, imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator*(double r) const {
    if (formatoAtual == POLAR) {
        if (r >= 0.0) {
            return Complexo(pol.modulo * r, pol.arg, POLAR);
        } else {
            return Complexo(pol.modulo * (-r), normalizarAngulo(pol.arg + M_PI), POLAR);
        }
    }
    return Complexo(rec.real * r, rec.imag * r, RETANGULAR);
}

Complexo Complexo::operator/(double r) const {
    if (formatoAtual == POLAR) {
        if (r >= 0.0) {
            return Complexo(pol.modulo / r, pol.arg, POLAR);
        } else {
            return Complexo(pol.modulo / (-r), normalizarAngulo(pol.arg + M_PI), POLAR);
        }
    }
    return Complexo(rec.real / r, rec.imag / r, RETANGULAR);
}

Complexo operator+(double r, const Complexo& c) {
    Complexo res(r + c.real(), c.imag(), RETANGULAR);
    return res.converterPara(c.formato());
}

Complexo operator-(double r, const Complexo& c) {
    Complexo res(r - c.real(), -c.imag(), RETANGULAR);
    return res.converterPara(c.formato());
}

Complexo operator*(double r, const Complexo& c) {
    return c * r;
}

Complexo operator/(double r, const Complexo& c) {
    Complexo num(r, 0.0, RETANGULAR);
    Complexo res = num / c;
    return res.converterPara(c.formato());
}

// =============================================================================
// 6. OPERADORES DE ATRIBUIÇÃO COMPOSTA
// =============================================================================

Complexo& Complexo::operator+=(const Complexo& b) {
    *this = *this + b;
    return *this;
}

Complexo& Complexo::operator-=(const Complexo& b) {
    *this = *this - b;
    return *this;
}

Complexo& Complexo::operator*=(const Complexo& b) {
    *this = *this * b;
    return *this;
}

Complexo& Complexo::operator/=(const Complexo& b) {
    *this = *this / b;
    return *this;
}

Complexo& Complexo::operator+=(double r) {
    *this = *this + r;
    return *this;
}

Complexo& Complexo::operator-=(double r) {
    *this = *this - r;
    return *this;
}

Complexo& Complexo::operator*=(double r) {
    *this = *this * r;
    return *this;
}

Complexo& Complexo::operator/=(double r) {
    *this = *this / r;
    return *this;
}

Complexo& Complexo::operator^=(double expoente) {
    *this = *this ^ expoente;
    return *this;
}

Complexo& Complexo::operator^=(const Complexo& expoente) {
    *this = *this ^ expoente;
    return *this;
}

// =============================================================================
// 7. OPERADORES UNÁRIOS E INCREMENTOS
// =============================================================================

Complexo Complexo::operator-() const {
    if (formatoAtual == RETANGULAR) {
        return Complexo(-rec.real, -rec.imag, RETANGULAR);
    } else {
        return Complexo(pol.modulo, normalizarAngulo(pol.arg + M_PI), POLAR);
    }
}

Complexo& Complexo::operator++() {
    if (formatoAtual == RETANGULAR) {
        rec.real += 1.0;
    } else {
        *this = Complexo(real() + 1.0, imag(), RETANGULAR).converterPara(POLAR);
    }
    return *this;
}

Complexo Complexo::operator++(int) {
    Complexo copia(*this);
    ++(*this);
    return copia;
}

Complexo& Complexo::operator--() {
    if (formatoAtual == RETANGULAR) {
        rec.real -= 1.0;
    } else {
        *this = Complexo(real() - 1.0, imag(), RETANGULAR).converterPara(POLAR);
    }
    return *this;
}

Complexo Complexo::operator--(int) {
    Complexo copia(*this);
    --(*this);
    return copia;
}

// =============================================================================
// 8. OPERADORES DE COMPARAÇÃO COM TOLERÂNCIA EPSILON
// =============================================================================

bool Complexo::operator==(const Complexo& outro) const {
    return quaseIgual(real(), outro.real()) && quaseIgual(imag(), outro.imag());
}

bool Complexo::operator!=(const Complexo& outro) const {
    return !(*this == outro);
}

bool Complexo::operator==(double r) const {
    return quaseIgual(real(), r) && quaseIgual(imag(), 0.0);
}

bool Complexo::operator!=(double r) const {
    return !(*this == r);
}

bool operator==(double r, const Complexo& c) {
    return c == r;
}

bool operator!=(double r, const Complexo& c) {
    return c != r;
}

// =============================================================================
// 9. OPERADORES DE POTENCIAÇÃO
// =============================================================================

Complexo Complexo::operator^(double expoente) const {
    return potencia(expoente);
}

Complexo Complexo::operator^(int expoente) const {
    return potencia(static_cast<double>(expoente));
}

Complexo Complexo::operator^(const Complexo& expoente) const {
    if (modulo() < EPSILON) {
        return Complexo(0.0, 0.0, formatoAtual);
    }
    Complexo log_base = this->log();
    Complexo produto = expoente * log_base;
    Complexo res = produto.exponencial();
    return res.converterPara(formatoAtual);
}

Complexo operator^(double base, const Complexo& expoente) {
    if (base <= 0.0) {
        return Complexo(0.0, 0.0, expoente.formato());
    }
    Complexo produto = expoente * std::log(base);
    Complexo res = produto.exponencial();
    return res.converterPara(expoente.formato());
}

// =============================================================================
// 10. FUNÇÕES MATEMÁTICAS AVANÇADAS
// =============================================================================

Complexo Complexo::conjugado() const {
    if (formatoAtual == RETANGULAR) {
        return Complexo(rec.real, -rec.imag, RETANGULAR);
    } else {
        return Complexo(pol.modulo, normalizarAngulo(-pol.arg), POLAR);
    }
}

Complexo Complexo::potencia(double n) const {
    if (modulo() < EPSILON) {
        return Complexo(0.0, 0.0, formatoAtual);
    }
    double r_novo = std::pow(modulo(), n);
    double theta_novo = normalizarAngulo(arg() * n);
    Complexo res(r_novo, theta_novo, POLAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::exponencial() const {
    double r = std::exp(real());
    double theta = normalizarAngulo(imag());
    Complexo res(r, theta, POLAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::log() const {
    double r = modulo();
    if (r < EPSILON) {
        Complexo singular(-1e9, 0.0, RETANGULAR);
        return singular.converterPara(formatoAtual);
    }
    double ln_r = std::log(r);
    double theta = arg();
    Complexo res(ln_r, theta, RETANGULAR);
    return res.converterPara(formatoAtual);
}

void Complexo::raizes(int n, Complexo resultados[]) const {
    if (n <= 0) return;
    double R = std::pow(modulo(), 1.0 / static_cast<double>(n));
    double theta_base = arg();
    for (int k = 0; k < n; ++k) {
        double theta_k = normalizarAngulo((theta_base + 2.0 * M_PI * static_cast<double>(k)) / static_cast<double>(n));
        Complexo rk(R, theta_k, POLAR);
        resultados[k] = rk.converterPara(formatoAtual);
    }
}

// =============================================================================
// 11. FUNÇÕES TRIGONOMÉTRICAS COMPLEXAS
// =============================================================================

Complexo Complexo::sin() const {
    double x = real();
    double y = imag();
    Complexo res(std::sin(x) * std::cosh(y), std::cos(x) * std::sinh(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::cos() const {
    double x = real();
    double y = imag();
    Complexo res(std::cos(x) * std::cosh(y), -std::sin(x) * std::sinh(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::tan() const {
    return this->sin() / this->cos();
}

Complexo sin(const Complexo& z) {
    return z.sin();
}

Complexo cos(const Complexo& z) {
    return z.cos();
}

Complexo tan(const Complexo& z) {
    return z.tan();
}

// =============================================================================
// 12. FUNÇÕES HIPERBÓLICAS COMPLEXAS
// =============================================================================

Complexo Complexo::sinh() const {
    double x = real();
    double y = imag();
    Complexo res(std::sinh(x) * std::cos(y), std::cosh(x) * std::sin(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::cosh() const {
    double x = real();
    double y = imag();
    Complexo res(std::cosh(x) * std::cos(y), std::sinh(x) * std::sin(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::tanh() const {
    return this->sinh() / this->cosh();
}

Complexo sinh(const Complexo& z) {
    return z.sinh();
}

Complexo cosh(const Complexo& z) {
    return z.cosh();
}

Complexo tanh(const Complexo& z) {
    return z.tanh();
}

// =============================================================================
// 13. FUNÇÕES AMIGAS AUXILIARES (PADRÃO STL / ADL)
// =============================================================================

double real(const Complexo& c) {
    return c.real();
}

double imag(const Complexo& c) {
    return c.imag();
}

double abs(const Complexo& c) {
    return c.modulo();
}

double arg(const Complexo& c) {
    return c.arg();
}

Complexo exp(const Complexo& z) {
    return z.exponencial();
}

Complexo log(const Complexo& z) {
    return z.log();
}

// =============================================================================
// 14. OPERADORES DE FLUXO (I/O STREAMS)
// =============================================================================

std::ostream& operator<<(std::ostream& os, const Complexo& c) {
    std::ios_base::fmtflags flags_anteriores = os.flags();
    std::streamsize precisao_anterior = os.precision();

    os << std::fixed << std::setprecision(2);

    if (c.formato() == RETANGULAR) {
        double r = c.real();
        double i = c.imag();
        if (std::abs(r) < Complexo::EPSILON) r = 0.0;
        if (std::abs(i) < Complexo::EPSILON) i = 0.0;

        if (i >= 0.0) {
            os << r << " + " << i << "i";
        } else {
            os << r << " - " << -i << "i";
        }
    } else {
        double m = c.modulo();
        double a = c.arg();
        if (std::abs(m) < Complexo::EPSILON) m = 0.0;
        if (std::abs(a) < Complexo::EPSILON) a = 0.0;

        os << m << " < " << a << " rad";
    }

    os.flags(flags_anteriores);
    os.precision(precisao_anterior);
    return os;
}

std::istream& operator>>(std::istream& is, Complexo& c) {
    double r = 0.0, i = 0.0;
    if (is >> r >> i) {
        c = Complexo(r, i, RETANGULAR);
    }
    return is;
}

// =============================================================================
// 15. LITERAIS DEFINIDOS PELO USUÁRIO (USER-DEFINED LITERALS - UDL)
// =============================================================================

Complexo operator""_i(long double imag) {
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

Complexo operator""_j(long double imag) {
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

Complexo operator""_i(unsigned long long int imag) {
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

Complexo operator""_j(unsigned long long int imag) {
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

double operator""_deg(long double graus) {
    return static_cast<double>(graus) * (M_PI / 180.0);
}

double operator""_deg(unsigned long long int graus) {
    return static_cast<double>(graus) * (M_PI / 180.0);
}

double operator""_rad(long double rad) {
    return static_cast<double>(rad);
}

double operator""_rad(unsigned long long int rad) {
    return static_cast<double>(rad);
}
