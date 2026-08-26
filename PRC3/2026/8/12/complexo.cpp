#include "complexo.hpp"

namespace ifsp {

double Complexo::normalizarAngulo(double angulo) noexcept {
    if (std::isnan(angulo) || std::isinf(angulo)) {
        return angulo;
    }
    while (angulo > PI) angulo -= 2.0 * PI;
    while (angulo <= -PI) angulo += 2.0 * PI;
    return angulo;
}

Complexo::Complexo(double real, double imag, Formato formato) noexcept
    : m_formato(formato) {
    if (formato == Formato::Retangular) {
        m_rec.real = real;
        m_rec.imag = imag;
    } else {
        m_pol.mod = std::abs(real);
        m_pol.arg = normalizarAngulo(imag);
    }
}

Complexo Complexo::retangular(double real, double imag) noexcept {
    Complexo c;
    c.m_formato = Formato::Retangular;
    c.m_rec.real = real;
    c.m_rec.imag = imag;
    return c;
}

Complexo Complexo::polar(double mod, double arg) noexcept {
    Complexo c;
    c.m_formato = Formato::Polar;
    c.m_pol.mod = std::abs(mod);
    c.m_pol.arg = normalizarAngulo(arg);
    return c;
}

double Complexo::real() const noexcept {
    if (m_formato == Formato::Retangular) {
        return m_rec.real;
    }
    return m_pol.mod * std::cos(m_pol.arg);
}

double Complexo::imag() const noexcept {
    if (m_formato == Formato::Retangular) {
        return m_rec.imag;
    }
    return m_pol.mod * std::sin(m_pol.arg);
}

double Complexo::mod() const noexcept {
    if (m_formato == Formato::Polar) {
        return m_pol.mod;
    }
    return std::hypot(m_rec.real, m_rec.imag);
}

double Complexo::arg() const noexcept {
    if (m_formato == Formato::Polar) {
        return m_pol.arg;
    }
    return std::atan2(m_rec.imag, m_rec.real);
}

double Complexo::argGraus() const noexcept {
    return arg() * (180.0 / PI);
}

Complexo Complexo::convertidoPara(Formato novo_formato) const noexcept {
    if (m_formato == novo_formato) {
        return *this;
    }
    if (novo_formato == Formato::Retangular) {
        return Complexo::retangular(real(), imag());
    }
    return Complexo::polar(mod(), arg());
}

Complexo& Complexo::converterPara(Formato novo_formato) noexcept {
    if (m_formato != novo_formato) {
        *this = convertidoPara(novo_formato);
    }
    return *this;
}

Complexo Complexo::conjugado() const noexcept {
    Complexo res = *this;
    if (res.m_formato == Formato::Retangular) {
        res.m_rec.imag = -res.m_rec.imag;
    } else {
        res.m_pol.arg = normalizarAngulo(-res.m_pol.arg);
    }
    return res;
}

Complexo Complexo::potencia(double n) const noexcept {
    const double r_mod = std::pow(mod(), n);
    const double r_arg = arg() * n;
    Complexo res = Complexo::polar(r_mod, r_arg);
    if (m_formato == Formato::Retangular) {
        res.converterPara(Formato::Retangular);
    }
    return res;
}

Complexo Complexo::exp() const noexcept {
    const double x = real();
    const double y = imag();
    const double r_mod = std::exp(x);
    const double r_arg = y;
    Complexo res = Complexo::polar(r_mod, r_arg);
    if (m_formato == Formato::Retangular) {
        res.converterPara(Formato::Retangular);
    }
    return res;
}

std::vector<Complexo> Complexo::raizes(int n) const {
    if (n <= 0) {
        return {};
    }

    std::vector<Complexo> resultados;
    resultados.reserve(static_cast<size_t>(n));

    const double r = mod();
    const double theta = arg();
    const double r_raiz = std::pow(r, 1.0 / static_cast<double>(n));

    for (int k = 0; k < n; ++k) {
        const double arg_k = (theta + 2.0 * PI * static_cast<double>(k)) / static_cast<double>(n);
        Complexo raiz_k = Complexo::polar(r_raiz, arg_k);
        if (m_formato == Formato::Retangular) {
            raiz_k.converterPara(Formato::Retangular);
        }
        resultados.push_back(raiz_k);
    }

    return resultados;
}

Complexo Complexo::operator-() const noexcept {
    if (m_formato == Formato::Retangular) {
        return Complexo::retangular(-m_rec.real, -m_rec.imag);
    }
    return Complexo::polar(m_pol.mod, m_pol.arg + PI);
}

Complexo& Complexo::operator+=(const Complexo& outro) noexcept {
    const double r_real = real() + outro.real();
    const double r_imag = imag() + outro.imag();
    const Formato fmt_orig = m_formato;
    *this = Complexo::retangular(r_real, r_imag);
    if (fmt_orig == Formato::Polar) {
        converterPara(Formato::Polar);
    }
    return *this;
}

Complexo& Complexo::operator-=(const Complexo& outro) noexcept {
    const double r_real = real() - outro.real();
    const double r_imag = imag() - outro.imag();
    const Formato fmt_orig = m_formato;
    *this = Complexo::retangular(r_real, r_imag);
    if (fmt_orig == Formato::Polar) {
        converterPara(Formato::Polar);
    }
    return *this;
}

Complexo& Complexo::operator*=(const Complexo& outro) noexcept {
    const double r_mod = mod() * outro.mod();
    const double r_arg = arg() + outro.arg();
    const Formato fmt_orig = m_formato;
    *this = Complexo::polar(r_mod, r_arg);
    if (fmt_orig == Formato::Retangular) {
        converterPara(Formato::Retangular);
    }
    return *this;
}

Complexo& Complexo::operator/=(const Complexo& outro) {
    const double b_mod = outro.mod();
    if (b_mod == 0.0) {
        throw std::domain_error("Divisao por zero em numero complexo.");
    }
    const double r_mod = mod() / b_mod;
    const double r_arg = arg() - outro.arg();
    const Formato fmt_orig = m_formato;
    *this = Complexo::polar(r_mod, r_arg);
    if (fmt_orig == Formato::Retangular) {
        converterPara(Formato::Retangular);
    }
    return *this;
}

bool Complexo::operator==(const Complexo& outro) const noexcept {
    constexpr double EPSILON = 1e-9;
    return std::abs(real() - outro.real()) < EPSILON &&
           std::abs(imag() - outro.imag()) < EPSILON;
}

std::string Complexo::toString(int precisao) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precisao);
    if (m_formato == Formato::Retangular) {
        const double im = imag();
        const char sinal = (im >= 0.0) ? '+' : '-';
        oss << real() << ' ' << sinal << ' ' << std::abs(im) << "i (Retangular)";
    } else {
        const double graus = argGraus();
        oss << "|z| = " << mod() << ", arg = " << arg()
            << " rad (" << std::setprecision(2) << graus << " graus) (Polar)";
    }
    return oss.str();
}

void Complexo::imprimir(std::ostream& os, int precisao) const {
    os << toString(precisao) << '\n';
}

std::ostream& operator<<(std::ostream& os, const Complexo& c) {
    return os << c.toString();
}

} // namespace ifsp
