/* =============================================================================
 * DISCIPLINA: Programação Orientada a Objetos
 * ARQUIVO: Complexo.cpp
 *
 * TEMPLATE DE IMPLEMENTAÇÃO DA CLASS COMPLEXO (C++)
 * ============================================================================= */
 
//acesse o link para obter mais detalhes sobre os arquivos
// https://onlinegdb.com/cnlwWX26vv

#include "Complexo.hpp"
#include <iomanip>
#include <sstream>

// =============================================================================
// FUNÇÕES UTILITÁRIAS PRIVADAS E ESTÁTICAS
// =============================================================================

double Complexo::normalizarAngulo(double theta) {
    while (theta > M_PI)  theta -= 2.0 * M_PI;
    while (theta <= -M_PI) theta += 2.0 * M_PI;
    if (std::abs(theta) < EPSILON) theta = 0.0;
    return theta;
}

bool Complexo::quaseIgual(double a, double b) {
    return std::abs(a - b) < EPSILON;
}

// =============================================================================
// 1. FORMA CANÔNICA ORTODOXA
// =============================================================================

Complexo::Complexo() {
    // --preencher--
    formatoAtual = RETANGULAR;
    rec.real = 0.0;
    rec.imag = 0.0;
}

Complexo::Complexo(const Complexo& outro) {
    // --preencher--
    formatoAtual = outro.formatoAtual;
    if (formatoAtual == RETANGULAR) {
        rec = outro.rec;
    } else {
        pol = outro.pol;
    }
}

Complexo& Complexo::operator=(const Complexo& outro) {
    // --preencher--
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

Complexo::~Complexo() {
    // --preencher--
}

// =============================================================================
// 2. CONSTRUTORES DE CONVERSÃO E TIPOS PRIMITIVOS
// =============================================================================

Complexo::Complexo(double real, double imag, Formato f) {
    // --preencher--
    formatoAtual = f;
    if (f == RETANGULAR) {
        rec.real = real;
        rec.imag = imag;
    } else {
        pol.modulo = real;
        pol.arg = normalizarAngulo(imag);
    }
}

Complexo::Complexo(float real, float imag, Formato f) {
    // --preencher--
    *this = Complexo(static_cast<double>(real), static_cast<double>(imag), f);
}

Complexo::Complexo(int real, int imag, Formato f) {
    // --preencher--
    *this = Complexo(static_cast<double>(real), static_cast<double>(imag), f);
}

Complexo::Complexo(long long real, long long imag, Formato f) {
    // --preencher--
    *this = Complexo(static_cast<double>(real), static_cast<double>(imag), f);
}

Complexo& Complexo::operator=(double r) {
    // --preencher--
    formatoAtual = RETANGULAR;
    rec.real = r;
    rec.imag = 0.0;
    return *this;
}

Complexo& Complexo::operator=(int r) {
    // --preencher--
    *this = static_cast<double>(r);
    return *this;
}

// =============================================================================
// 3. OPERADORES DE CONVERSÃO EXPLÍCITA (CAST)
// =============================================================================

Complexo::operator double() const {
    // --preencher--
    return real();
}

Complexo::operator float() const {
    // --preencher--
    return static_cast<float>(real());
}

Complexo::operator int() const {
    // --preencher--
    return static_cast<int>(real());
}

Complexo::operator bool() const {
    // --preencher--
    return modulo() > EPSILON;
}

// =============================================================================
// 4. MÉTODOS DE ACESSO (GETTERS) E CONVERSÃO DE FORMATO
// =============================================================================

double Complexo::real() const {
    // --preencher--
    if (formatoAtual == RETANGULAR) {
        return rec.real;
    }
    return pol.modulo * std::cos(pol.arg);
}

double Complexo::imag() const {
    // --preencher--
    if (formatoAtual == RETANGULAR) {
        return rec.imag;
    }
    return pol.modulo * std::sin(pol.arg);
}

double Complexo::modulo() const {
    // --preencher--
    if (formatoAtual == POLAR) {
        return pol.modulo;
    }
    return std::hypot(rec.real, rec.imag);
}

double Complexo::arg() const {
    // --preencher--
    if (formatoAtual == POLAR) {
        return pol.arg;
    }
    return normalizarAngulo(std::atan2(rec.imag, rec.real));
}

Formato Complexo::formato() const {
    // --preencher--
    return formatoAtual;
}

Complexo Complexo::converterPara(Formato novoFormato) const {
    // --preencher--
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
// =============================================================================

Complexo Complexo::operator+(const Complexo& b) const {
    // --preencher--
    Complexo res(real() + b.real(), imag() + b.imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator-(const Complexo& b) const {
    // --preencher--
    Complexo res(real() - b.real(), imag() - b.imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator*(const Complexo& b) const {
    // --preencher--
    if (formatoAtual == POLAR && b.formatoAtual == POLAR) {
        return Complexo(pol.modulo * b.pol.modulo, normalizarAngulo(pol.arg + b.pol.arg), POLAR);
    }
    double r1 = real(), i1 = imag();
    double r2 = b.real(), i2 = b.imag();
    Complexo res(r1 * r2 - i1 * i2, r1 * i2 + i1 * r2, RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator/(const Complexo& b) const {
    // --preencher--
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
    // --preencher--
    Complexo res(real() + r, imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator-(double r) const {
    // --preencher--
    Complexo res(real() - r, imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::operator*(double r) const {
    // --preencher--
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
    // --preencher--
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
    // --preencher--
    Complexo res(r + c.real(), c.imag(), RETANGULAR);
    return res.converterPara(c.formato());
}

Complexo operator-(double r, const Complexo& c) {
    // --preencher--
    Complexo res(r - c.real(), -c.imag(), RETANGULAR);
    return res.converterPara(c.formato());
}

Complexo operator*(double r, const Complexo& c) {
    // --preencher--
    return c * r;
}

Complexo operator/(double r, const Complexo& c) {
    // --preencher--
    Complexo num(r, 0.0, RETANGULAR);
    Complexo res = num / c;
    return res.converterPara(c.formato());
}

// =============================================================================
// 6. OPERADORES DE ATRIBUIÇÃO COMPOSTA
// =============================================================================

Complexo& Complexo::operator+=(const Complexo& b) {
    // --preencher--
    *this = *this + b;
    return *this;
}

Complexo& Complexo::operator-=(const Complexo& b) {
    // --preencher--
    *this = *this - b;
    return *this;
}

Complexo& Complexo::operator*=(const Complexo& b) {
    // --preencher--
    *this = *this * b;
    return *this;
}

Complexo& Complexo::operator/=(const Complexo& b) {
    // --preencher--
    *this = *this / b;
    return *this;
}

Complexo& Complexo::operator+=(double r) {
    // --preencher--
    *this = *this + r;
    return *this;
}

Complexo& Complexo::operator-=(double r) {
    // --preencher--
    *this = *this - r;
    return *this;
}

Complexo& Complexo::operator*=(double r) {
    // --preencher--
    *this = *this * r;
    return *this;
}

Complexo& Complexo::operator/=(double r) {
    // --preencher--
    *this = *this / r;
    return *this;
}

Complexo& Complexo::operator^=(double expoente) {
    // --preencher--
    *this = *this ^ expoente;
    return *this;
}

Complexo& Complexo::operator^=(const Complexo& expoente) {
    // --preencher--
    *this = *this ^ expoente;
    return *this;
}

// =============================================================================
// 7. OPERADORES UNÁRIOS
// =============================================================================

Complexo Complexo::operator-() const {
    // --preencher--
    if (formatoAtual == RETANGULAR) {
        return Complexo(-rec.real, -rec.imag, RETANGULAR);
    } else {
        return Complexo(pol.modulo, normalizarAngulo(pol.arg + M_PI), POLAR);
    }
}

Complexo& Complexo::operator++() {
    // --preencher--
    if (formatoAtual == RETANGULAR) {
        rec.real += 1.0;
    } else {
        *this = Complexo(real() + 1.0, imag(), RETANGULAR).converterPara(POLAR);
    }
    return *this;
}

Complexo Complexo::operator++(int) {
    // --preencher--
    Complexo copia(*this);
    ++(*this);
    return copia;
}

Complexo& Complexo::operator--() {
    // --preencher--
    if (formatoAtual == RETANGULAR) {
        rec.real -= 1.0;
    } else {
        *this = Complexo(real() - 1.0, imag(), RETANGULAR).converterPara(POLAR);
    }
    return *this;
}

Complexo Complexo::operator--(int) {
    // --preencher--
    Complexo copia(*this);
    --(*this);
    return copia;
}

// =============================================================================
// 8. OPERADORES DE COMPARAÇÃO
// =============================================================================

bool Complexo::operator==(const Complexo& outro) const {
    // --preencher--
    return quaseIgual(real(), outro.real()) && quaseIgual(imag(), outro.imag());
}

bool Complexo::operator!=(const Complexo& outro) const {
    // --preencher--
    return !(*this == outro);
}

bool Complexo::operator==(double r) const {
    // --preencher--
    return quaseIgual(real(), r) && quaseIgual(imag(), 0.0);
}

bool Complexo::operator!=(double r) const {
    // --preencher--
    return !(*this == r);
}

bool operator==(double r, const Complexo& c) {
    // --preencher--
    return c == r;
}

bool operator!=(double r, const Complexo& c) {
    // --preencher--
    return c != r;
}

// =============================================================================
// 9. OPERADOR DE POTENCIAÇÃO (operator^)
// =============================================================================

Complexo Complexo::operator^(double expoente) const {
    // --preencher--
    return potencia(expoente);
}

Complexo Complexo::operator^(int expoente) const {
    // --preencher--
    return potencia(static_cast<double>(expoente));
}

Complexo Complexo::operator^(const Complexo& expoente) const {
    // --preencher--
    if (modulo() < EPSILON) {
        return Complexo(0.0, 0.0, formatoAtual);
    }
    Complexo log_base = this->log();
    Complexo produto = expoente * log_base;
    Complexo res = produto.exponencial();
    return res.converterPara(formatoAtual);
}

Complexo operator^(double base, const Complexo& expoente) {
    // --preencher--
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
    // --preencher--
    if (formatoAtual == RETANGULAR) {
        return Complexo(rec.real, -rec.imag, RETANGULAR);
    } else {
        return Complexo(pol.modulo, normalizarAngulo(-pol.arg), POLAR);
    }
}

Complexo Complexo::potencia(double n) const {
    // --preencher--
    if (modulo() < EPSILON) {
        return Complexo(0.0, 0.0, formatoAtual);
    }
    double r_novo = std::pow(modulo(), n);
    double theta_novo = normalizarAngulo(arg() * n);
    Complexo res(r_novo, theta_novo, POLAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::exponencial() const {
    // --preencher--
    double r = std::exp(real());
    double theta = normalizarAngulo(imag());
    Complexo res(r, theta, POLAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::log() const {
    // --preencher--
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
    // --preencher--
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
    // --preencher--
    double x = real();
    double y = imag();
    Complexo res(std::sin(x) * std::cosh(y), std::cos(x) * std::sinh(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::cos() const {
    // --preencher--
    double x = real();
    double y = imag();
    Complexo res(std::cos(x) * std::cosh(y), -std::sin(x) * std::sinh(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::tan() const {
    // --preencher--
    return this->sin() / this->cos();
}

Complexo sin(const Complexo& z) {
    // --preencher--
    return z.sin();
}

Complexo cos(const Complexo& z) {
    // --preencher--
    return z.cos();
}

Complexo tan(const Complexo& z) {
    // --preencher--
    return z.tan();
}

// =============================================================================
// 12. FUNÇÕES HIPERBÓLICAS COMPLEXAS
// =============================================================================

Complexo Complexo::sinh() const {
    // --preencher--
    double x = real();
    double y = imag();
    Complexo res(std::sinh(x) * std::cos(y), std::cosh(x) * std::sin(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::cosh() const {
    // --preencher--
    double x = real();
    double y = imag();
    Complexo res(std::cosh(x) * std::cos(y), std::sinh(x) * std::sin(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

Complexo Complexo::tanh() const {
    // --preencher--
    return this->sinh() / this->cosh();
}

Complexo sinh(const Complexo& z) {
    // --preencher--
    return z.sinh();
}

Complexo cosh(const Complexo& z) {
    // --preencher--
    return z.cosh();
}

Complexo tanh(const Complexo& z) {
    // --preencher--
    return z.tanh();
}

// =============================================================================
// 13. FUNÇÕES AMIGAS AUXILIARES (PADRÃO STL / ADL)
// =============================================================================

double real(const Complexo& c) {
    // --preencher--
    return c.real();
}

double imag(const Complexo& c) {
    // --preencher--
    return c.imag();
}

double abs(const Complexo& c) {
    // --preencher--
    return c.modulo();
}

double arg(const Complexo& c) {
    // --preencher--
    return c.arg();
}

Complexo exp(const Complexo& z) {
    // --preencher--
    return z.exponencial();
}

Complexo log(const Complexo& z) {
    // --preencher--
    return z.log();
}

// =============================================================================
// 14. OPERADORES DE FLUXO (I/O STREAMS)
// =============================================================================

std::ostream& operator<<(std::ostream& os, const Complexo& c) {
    // --preencher--
    std::ios_base::fmtflags flags_anteriores = os.flags();
    std::streamsize precisao_anterior = os.precision();

    os << std::fixed << std::setprecision(2);

    if (c.formato() == RETANGULAR) {
        double r = c.real();
        double i = c.imag();
        if (std::abs(r) < 0.005) r = 0.0;
        if (std::abs(i) < 0.005) i = 0.0;

        if (i >= 0.0) {
            os << r << " + " << i << "i";
        } else {
            os << r << " - " << -i << "i";
        }
    } else {
        double m = c.modulo();
        double a = c.arg();
        if (std::abs(m) < 0.005) m = 0.0;
        if (std::abs(a) < 0.005) a = 0.0;

        os << m << " < " << a << " rad";
    }
    os.flags(flags_anteriores);
    os.precision(precisao_anterior);
    return os;
}

std::istream& operator>>(std::istream& is, Complexo& c) {
    // --preencher--
    double r = 0.0, i = 0.0;
    if (is >> r >> i) {
        c = Complexo(r, i, RETANGULAR);
    }
    return is;
}

// =============================================================================
// 15. LITERAIS DEFINIDOS PELO USUÁRIO (USER-DEFINED LITERALS)
// =============================================================================

Complexo operator""_i(long double imag) {
    // --preencher--
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

Complexo operator""_j(long double imag) {
    // --preencher--
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

Complexo operator""_i(unsigned long long int imag) {
    // --preencher--
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

Complexo operator""_j(unsigned long long int imag) {
    // --preencher--
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

double operator""_deg(long double graus) {
    // --preencher--
    return static_cast<double>(graus) * (M_PI / 180.0);
}

double operator""_deg(unsigned long long int graus) {
    // --preencher--
    return static_cast<double>(graus) * (M_PI / 180.0);
}

double operator""_rad(long double rad) {
    // --preencher--
    return static_cast<double>(rad);
}

double operator""_rad(unsigned long long int rad) {
    // --preencher--
    return static_cast<double>(rad);
}
