#ifndef COMPLEXO_HPP
#define COMPLEXO_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cstdint>

namespace ifsp {

/**
 * @brief Enumeração fortemente tipada para o formato do número complexo.
 */
enum class Formato : uint8_t {
    Retangular,
    Polar
};

/**
 * @brief Classe moderna e otimizada para representação e aritmética de Números Complexos.
 * Suporta formatos retangular (algébrico) e polar, com operadores sobrecarregados,
 * construtores nomeados, alta performance e semântica de valor.
 */
class Complexo {
public:
    struct PolarData {
        double mod{0.0};
        double arg{0.0}; // Ângulo em radianos [-pi, pi]
    };

    struct RetangularData {
        double real{0.0};
        double imag{0.0};
    };

private:
    Formato m_formato{Formato::Retangular};
    union {
        PolarData m_pol;
        RetangularData m_rec;
    };

    static constexpr double PI = 3.141592653589793238462643383279502884;

    static double normalizarAngulo(double angulo) noexcept;

public:
    // Construtores
    constexpr Complexo() noexcept : m_formato(Formato::Retangular), m_rec{0.0, 0.0} {}
    Complexo(double real, double imag, Formato formato = Formato::Retangular) noexcept;

    // Métodos de fábrica estáticos (Named Constructors)
    static Complexo retangular(double real, double imag) noexcept;
    static Complexo polar(double mod, double arg) noexcept;

    // Getters de formato e estado
    constexpr Formato formato() const noexcept { return m_formato; }
    constexpr bool ehRetangular() const noexcept { return m_formato == Formato::Retangular; }
    constexpr bool ehPolar() const noexcept { return m_formato == Formato::Polar; }

    // Consultas Matemáticas (Getters)
    double real() const noexcept;
    double imag() const noexcept;
    double mod() const noexcept;
    double arg() const noexcept;
    double argGraus() const noexcept;

    // Conversão de representação
    Complexo convertidoPara(Formato novo_formato) const noexcept;
    Complexo& converterPara(Formato novo_formato) noexcept;

    // Funções Matemáticas Avançadas
    Complexo conjugado() const noexcept;
    Complexo potencia(double n) const noexcept;
    Complexo exp() const noexcept;
    std::vector<Complexo> raizes(int n) const;

    // Operadores Aritméticos Unários
    Complexo operator+() const noexcept { return *this; }
    Complexo operator-() const noexcept;

    // Operadores Aritméticos Compostos
    Complexo& operator+=(const Complexo& outro) noexcept;
    Complexo& operator-=(const Complexo& outro) noexcept;
    Complexo& operator*=(const Complexo& outro) noexcept;
    Complexo& operator/=(const Complexo& outro);

    // Operadores Aritméticos Binários (Friend / Inlined)
    friend Complexo operator+(Complexo a, const Complexo& b) noexcept { return a += b; }
    friend Complexo operator-(Complexo a, const Complexo& b) noexcept { return a -= b; }
    friend Complexo operator*(Complexo a, const Complexo& b) noexcept { return a *= b; }
    friend Complexo operator/(Complexo a, const Complexo& b) { return a /= b; }

    // Comparações
    bool operator==(const Complexo& outro) const noexcept;
    bool operator!=(const Complexo& outro) const noexcept { return !(*this == outro); }

    // Impressão e Formatação
    std::string toString(int precisao = 4) const;
    void imprimir(std::ostream& os = std::cout, int precisao = 4) const;

    friend std::ostream& operator<<(std::ostream& os, const Complexo& c);
};

// Aliases convenientes
using CPLX = Complexo;
using cplx = Complexo;

} // namespace ifsp

#endif // COMPLEXO_HPP
