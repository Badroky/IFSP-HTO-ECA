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
}

Complexo::Complexo(const Complexo& outro) {
    // --preencher--
}

Complexo& Complexo::operator=(const Complexo& outro) {
    // --preencher--
}

Complexo::~Complexo() {
    // --preencher--
}

// =============================================================================
// 2. CONSTRUTORES DE CONVERSÃO E TIPOS PRIMITIVOS
// =============================================================================

Complexo::Complexo(double real, double imag, Formato f) {
    // --preencher--
}

Complexo::Complexo(float real, float imag, Formato f) {
    // --preencher--
}

Complexo::Complexo(int real, int imag, Formato f) {
    // --preencher--
}

Complexo::Complexo(long long real, long long imag, Formato f) {
    // --preencher--
}

Complexo& Complexo::operator=(double r) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator=(int r) {
    // --preencher--
    return *this;
}

// =============================================================================
// 3. OPERADORES DE CONVERSÃO EXPLÍCITA (CAST)
// =============================================================================

Complexo::operator double() const {
    // --preencher--
    return 0.0;
}

Complexo::operator float() const {
    // --preencher--
    return 0.0f;
}

Complexo::operator int() const {
    // --preencher--
    return 0;
}

Complexo::operator bool() const {
    // --preencher--
    return false;
}

// =============================================================================
// 4. MÉTODOS DE ACESSO (GETTERS) E CONVERSÃO DE FORMATO
// =============================================================================

double Complexo::real() const {
    // --preencher--
    return 0.0;
}

double Complexo::imag() const {
    // --preencher--
    return 0.0;
}

double Complexo::modulo() const {
    // --preencher--
    return 0.0;
}

double Complexo::arg() const {
    // --preencher--
    return 0.0;
}

Formato Complexo::formato() const {
    // --preencher--
    return RETANGULAR;
}

Complexo Complexo::converterPara(Formato novoFormato) const {
    // --preencher--
    return Complexo();
}

// =============================================================================
// 5. OPERADORES ARITMÉTICOS BINÁRIOS
// =============================================================================

Complexo Complexo::operator+(const Complexo& b) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::operator-(const Complexo& b) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::operator*(const Complexo& b) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::operator/(const Complexo& b) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::operator+(double r) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::operator-(double r) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::operator*(double r) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::operator/(double r) const {
    // --preencher--
    return Complexo();
}

Complexo operator+(double r, const Complexo& c) {
    // --preencher--
    return Complexo();
}

Complexo operator-(double r, const Complexo& c) {
    // --preencher--
    return Complexo();
}

Complexo operator*(double r, const Complexo& c) {
    // --preencher--
    return Complexo();
}

Complexo operator/(double r, const Complexo& c) {
    // --preencher--
    return Complexo();
}

// =============================================================================
// 6. OPERADORES DE ATRIBUIÇÃO COMPOSTA
// =============================================================================

Complexo& Complexo::operator+=(const Complexo& b) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator-=(const Complexo& b) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator*=(const Complexo& b) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator/=(const Complexo& b) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator+=(double r) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator-=(double r) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator*=(double r) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator/=(double r) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator^=(double expoente) {
    // --preencher--
    return *this;
}

Complexo& Complexo::operator^=(const Complexo& expoente) {
    // --preencher--
    return *this;
}

// =============================================================================
// 7. OPERADORES UNÁRIOS
// =============================================================================

Complexo Complexo::operator-() const {
    // --preencher--
    return Complexo();
}

Complexo& Complexo::operator++() {
    // --preencher--
    return *this;
}

Complexo Complexo::operator++(int) {
    // --preencher--
    return Complexo();
}

Complexo& Complexo::operator--() {
    // --preencher--
    return *this;
}

Complexo Complexo::operator--(int) {
    // --preencher--
    return Complexo();
}

// =============================================================================
// 8. OPERADORES DE COMPARAÇÃO
// =============================================================================

bool Complexo::operator==(const Complexo& outro) const {
    // --preencher--
    return false;
}

bool Complexo::operator!=(const Complexo& outro) const {
    // --preencher--
    return false;
}

bool Complexo::operator==(double r) const {
    // --preencher--
    return false;
}

bool Complexo::operator!=(double r) const {
    // --preencher--
    return false;
}

bool operator==(double r, const Complexo& c) {
    // --preencher--
    return false;
}

bool operator!=(double r, const Complexo& c) {
    // --preencher--
    return false;
}

// =============================================================================
// 9. OPERADOR DE POTENCIAÇÃO (operator^)
// =============================================================================

Complexo Complexo::operator^(double expoente) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::operator^(int expoente) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::operator^(const Complexo& expoente) const {
    // --preencher--
    return Complexo();
}

Complexo operator^(double base, const Complexo& expoente) {
    // --preencher--
    return Complexo();
}

// =============================================================================
// 10. FUNÇÕES MATEMÁTICAS AVANÇADAS
// =============================================================================

Complexo Complexo::conjugado() const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::potencia(double n) const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::exponencial() const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::log() const {
    // --preencher--
    return Complexo();
}

void Complexo::raizes(int n, Complexo resultados[]) const {
    // --preencher--
}

// =============================================================================
// 11. FUNÇÕES TRIGONOMÉTRICAS COMPLEXAS
// =============================================================================

Complexo Complexo::sin() const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::cos() const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::tan() const {
    // --preencher--
    return Complexo();
}

Complexo sin(const Complexo& z) {
    // --preencher--
    return Complexo();
}

Complexo cos(const Complexo& z) {
    // --preencher--
    return Complexo();
}

Complexo tan(const Complexo& z) {
    // --preencher--
    return Complexo();
}

// =============================================================================
// 12. FUNÇÕES HIPERBÓLICAS COMPLEXAS
// =============================================================================

Complexo Complexo::sinh() const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::cosh() const {
    // --preencher--
    return Complexo();
}

Complexo Complexo::tanh() const {
    // --preencher--
    return Complexo();
}

Complexo sinh(const Complexo& z) {
    // --preencher--
    return Complexo();
}

Complexo cosh(const Complexo& z) {
    // --preencher--
    return Complexo();
}

Complexo tanh(const Complexo& z) {
    // --preencher--
    return Complexo();
}

// =============================================================================
// 13. FUNÇÕES AMIGAS AUXILIARES (PADRÃO STL / ADL)
// =============================================================================

double real(const Complexo& c) {
    // --preencher--
    return 0.0;
}

double imag(const Complexo& c) {
    // --preencher--
    return 0.0;
}

double abs(const Complexo& c) {
    // --preencher--
    return 0.0;
}

double arg(const Complexo& c) {
    // --preencher--
    return 0.0;
}

Complexo exp(const Complexo& z) {
    // --preencher--
    return Complexo();
}

Complexo log(const Complexo& z) {
    // --preencher--
    return Complexo();
}

// =============================================================================
// 14. OPERADORES DE FLUXO (I/O STREAMS)
// =============================================================================

std::ostream& operator<<(std::ostream& os, const Complexo& c) {
    // --preencher--
    return os;
}

std::istream& operator>>(std::istream& is, Complexo& c) {
    // --preencher--
    return is;
}

// =============================================================================
// 15. LITERAIS DEFINIDOS PELO USUÁRIO (USER-DEFINED LITERALS)
// =============================================================================

Complexo operator""_i(long double imag) {
    // --preencher--
    return Complexo();
}

Complexo operator""_j(long double imag) {
    // --preencher--
    return Complexo();
}

Complexo operator""_i(unsigned long long int imag) {
    // --preencher--
    return Complexo();
}

Complexo operator""_j(unsigned long long int imag) {
    // --preencher--
    return Complexo();
}

double operator""_deg(long double graus) {
    // --preencher--
    return 0.0;
}

double operator""_deg(unsigned long long int graus) {
    // --preencher--
    return 0.0;
}

double operator""_rad(long double rad) {
    // --preencher--
    return 0.0;
}

double operator""_rad(unsigned long long int rad) {
    // --preencher--
    return 0.0;
}