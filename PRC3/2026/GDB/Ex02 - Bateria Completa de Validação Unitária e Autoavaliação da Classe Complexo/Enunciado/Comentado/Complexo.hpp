#ifndef COMPLEXO_HPP
#define COMPLEXO_HPP

/* =============================================================================
 * DISCIPLINA: Programação Orientada a Objetos / Sistemas de Controle
 * ARQUIVO: Complexo.hpp
 * ============================================================================= */

#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @enum Formato
 * @brief Identificador de tag para a união discriminada (Tagged Union).
 * Indica qual campo da união anônima interna possui dados válidos e sincronizados.
 */
enum Formato {
    RETANGULAR, ///< Representação retangular/cartesiana: z = real + imag * i
    POLAR       ///< Representação polar/trigonométrica: z = modulo ∠ arg
};

/**
 * @class Complexo
 * @brief TAD para representação e manipulação de números complexos com suporte
 * a união discriminada (tagged union), aritmética mista, funções transcendentais e literais.
 */
class Complexo {
private:
    /**
     * @struct Polar
     * @brief Armazena o par ordenado polar (módulo e argumento angular).
     */
    struct Polar {
        double modulo; ///< Raio polar r (r >= 0.0).
        double arg;    ///< Ângulo theta em radianos no intervalo (-pi, pi].
    };

    /**
     * @struct Retangular
     * @brief Armazena o par ordenado cartesiano (parte real e parte imaginária).
     */
    struct Retangular {
        double real; ///< Coordenada no eixo real (eixo x).
        double imag; ///< Coordenada no eixo imaginário (eixo y).
    };

    Formato formatoAtual; ///< Tag discriminante indicando a representação ativa da união.
    union {
        Polar pol;        ///< Dados ativos quando formatoAtual == POLAR.
        Retangular rec;   ///< Dados ativos quando formatoAtual == RETANGULAR.
    };

    /// @brief Limiar de tolerância numérica para comparação de ponto flutuante e zero infinitesimal.
    static constexpr double EPSILON = 1e-9;

    /**
     * @brief Normaliza qualquer ângulo para o intervalo cíclico fundamental (-pi, pi].
     * @details Subtrai ou adiciona voltas completas de 2*pi enquanto theta > pi ou theta <= -pi.
     * Se |theta| < EPSILON, força o valor para 0.0 positivo para evitar a impressão de -0.00.
     * @param theta Ângulo original em radianos.
     * @return Ângulo normalizado em (-pi, pi].
     */
    static double normalizarAngulo(double theta);

    /**
     * @brief Verifica igualdade aproximada entre dois escalares em ponto flutuante.
     * @details Avalia se |a - b| < EPSILON.
     * @param a Primeiro valor escalar.
     * @param b Segundo valor escalar.
     * @return true se a diferença absoluta for inferior a EPSILON; false caso contrário.
     */
    static bool quaseIgual(double a, double b);

public:
    // =========================================================================
    // 1. FORMA CANÔNICA ORTODOXA
    // =========================================================================

    /**
     * @brief Construtor padrão da classe.
     * @details Inicializa o número complexo como o elemento nulo (0.0 + 0.0i)
     * e configura formatoAtual = RETANGULAR.
     */
    Complexo();

    /**
     * @brief Construtor de cópia.
     * @details Clona o formatoAtual e copia o payload exato da união interna
     * (rec ou pol) a partir do objeto 'outro'.
     * @param outro Instância constante de onde os dados serão copiados.
     */
    Complexo(const Complexo& outro);

    /**
     * @brief Operador de atribuição por cópia (Copy Assignment).
     * @details Trata autoatribuição (this != &outro). Se forem instâncias distintas,
     * sincroniza formatoAtual e copia o membro ativo da união de 'outro'.
     * @param outro Instância a ser atribuída a *this.
     * @return Referência ao objeto atual (*this) para encadeamento.
     */
    Complexo& operator=(const Complexo& outro);

    /**
     * @brief Destrutor da classe.
     * @details Como a união armazena structs triviais sem ponteiros brutos dinâmicos,
     * apenas finaliza o ciclo de vida da instância.
     */
    ~Complexo();

    // =========================================================================
    // 2. CONSTRUTORES DE CONVERSÃO E TIPOS PRIMITIVOS
    // =========================================================================

    /**
     * @brief Construtor principal parametrizado para double.
     * @details 
     * - Se f == RETANGULAR: armazena rec.real = real e rec.imag = imag.
     * - Se f == POLAR: armazena pol.modulo = real e pol.arg = normalizarAngulo(imag).
     * @param real Parte real ou magnitude (módulo), conforme o formato.
     * @param imag Parte imaginária ou ângulo em radianos (padrão: 0.0).
     * @param f Tag de formato desejada (padrão: RETANGULAR).
     */
    Complexo(double real, double imag = 0.0, Formato f = RETANGULAR);

    /**
     * @brief Construtor de conversão para parâmetros do tipo float.
     * @details Realiza cast explícito para double e delega ao construtor principal.
     */
    Complexo(float real, float imag = 0.0f, Formato f = RETANGULAR);

    /**
     * @brief Construtor de conversão para parâmetros do tipo int.
     * @details Realiza cast explícito para double e delega ao construtor principal.
     */
    Complexo(int real, int imag = 0, Formato f = RETANGULAR);

    /**
     * @brief Construtor de conversão para parâmetros do tipo long long int.
     * @details Realiza cast explícito para double e delega ao construtor principal.
     */
    Complexo(long long real, long long imag = 0, Formato f = RETANGULAR);

    /**
     * @brief Atribuição a partir de escalar double.
     * @details Converte a instância para formato RETANGULAR, define rec.real = r
     * e zera a parte imaginária (rec.imag = 0.0).
     * @param r Escalar real de atribuição.
     * @return Referência a *this.
     */
    Complexo& operator=(double r);

    /**
     * @brief Atribuição a partir de inteiro primitivo.
     * @details Promove o inteiro para double e delega para operator=(double).
     * @param r Inteiro de atribuição.
     * @return Referência a *this.
     */
    Complexo& operator=(int r);

    // =========================================================================
    // 3. OPERADORES DE CONVERSÃO EXPLÍCITA (CASTS)
    // =========================================================================

    /**
     * @brief Cast explícito para double.
     * @details Retorna o valor da componente real (calculada por real()).
     */
    explicit operator double() const;

    /**
     * @brief Cast explícito para float.
     * @details Retorna a componente real convertida para float.
     */
    explicit operator float() const;

    /**
     * @brief Cast explícito para int.
     * @details Trunca e retorna a componente real como inteiro primitivo.
     */
    explicit operator int() const;

    /**
     * @brief Avaliação booleana da instância.
     * @details Retorna true se modulo() > EPSILON; false se o número for considerado nulo.
     */
    explicit operator bool() const;

    // =========================================================================
    // 4. MÉTODOS DE ACESSO (GETTERS) E CONVERSÃO DE FORMATO
    // =========================================================================

    /**
     * @brief Obtém a componente real cartesiana do número complexo.
     * @details Se formatoAtual == RETANGULAR, lê rec.real diretamente.
     * Se formatoAtual == POLAR, computa pol.modulo * cos(pol.arg).
     * @return Componente real em dupla precisão.
     */
    double real() const;

    /**
     * @brief Obtém a componente imaginária cartesiana do número complexo.
     * @details Se formatoAtual == RETANGULAR, lê rec.imag diretamente.
     * Se formatoAtual == POLAR, computa pol.modulo * sin(pol.arg).
     * @return Componente imaginária em dupla precisão.
     */
    double imag() const;

    /**
     * @brief Obtém a magnitude/módulo (r) do número complexo.
     * @details Se formatoAtual == POLAR, lê pol.modulo diretamente.
     * Se formatoAtual == RETANGULAR, computa std::hypot(rec.real, rec.imag).
     * @return Módulo r >= 0.0.
     */
    double modulo() const;

    /**
     * @brief Obtém o argumento/fase angular (theta) do número complexo em radianos.
     * @details Se formatoAtual == POLAR, lê pol.arg diretamente.
     * Se formatoAtual == RETANGULAR, computa std::atan2(rec.imag, rec.real).
     * @return Argumento normalizado no intervalo (-pi, pi].
     */
    double arg() const;

    /**
     * @brief Consulta o formato atualmente ativo na união discriminada.
     * @return RETANGULAR ou POLAR.
     */
    Formato formato() const;

    /**
     * @brief Cria e retorna uma nova instância convertida para o formato requisitado.
     * @details Se formatoAtual já for igual a novoFormato, retorna uma cópia idêntica.
     * Caso contrário, mapeia as coordenadas (retangular <-> polar) e ativa o novo formato.
     * @param novoFormato Formato alvo da conversão (RETANGULAR ou POLAR).
     * @return Novo objeto Complexo representado no novo formato.
     */
    Complexo converterPara(Formato novoFormato) const;

    // =========================================================================
    // 5. OPERADORES ARITMÉTICOS BINÁRIOS
    // Nota didática: As operações binárias devem sempre preservar o formatoAtual
    // do operando localizado à esquerda da expressão (*this).
    // =========================================================================

    /**
     * @brief Adição entre números complexos (z1 + z2).
     * @details Soma partes reais e imaginárias: (x1 + x2) + i*(y1 + y2).
     * Converte o resultado final para o formatoAtual de *this.
     */
    Complexo operator+(const Complexo& b) const;

    /**
     * @brief Subtração entre números complexos (z1 - z2).
     * @details Subtrai partes reais e imaginárias: (x1 - x2) + i*(y1 - y2).
     * Converte o resultado final para o formatoAtual de *this.
     */
    Complexo operator-(const Complexo& b) const;

    /**
     * @brief Multiplicação entre números complexos (z1 * z2).
     * @details
     * - Se ambos forem POLAR: calcula diretamente r = r1 * r2 e theta = theta1 + theta2.
     * - Caso contrário: aplica a álgebra cartesiana (x1*x2 - y1*y2) + i*(x1*y2 + y1*x2).
     * O resultado deve preservar o formatoAtual de *this.
     */
    Complexo operator*(const Complexo& b) const;

    /**
     * @brief Divisão entre números complexos (z1 / z2).
     * @details
     * - Se ambos forem POLAR: calcula diretamente r = r1 / r2 e theta = theta1 - theta2.
     * - Caso contrário: multiplica numerador e denominador pelo conjugado de b.
     * O resultado deve preservar o formatoAtual de *this.
     */
    Complexo operator/(const Complexo& b) const;

    /**
     * @brief Adição entre complexo e escalar real (z + r).
     */
    Complexo operator+(double r) const;

    /**
     * @brief Subtração entre complexo e escalar real (z - r).
     */
    Complexo operator-(double r) const;

    /**
     * @brief Multiplicação entre complexo e escalar real (z * r).
     */
    Complexo operator*(double r) const;

    /**
     * @brief Divisão entre complexo e escalar real (z / r).
     */
    Complexo operator/(double r) const;

    /**
     * @brief Adição comutativa: escalar real à esquerda e complexo à direita (r + z).
     */
    friend Complexo operator+(double r, const Complexo& c);

    /**
     * @brief Subtração: escalar real à esquerda e complexo à direita (r - z).
     */
    friend Complexo operator-(double r, const Complexo& c);

    /**
     * @brief Multiplicação comutativa: escalar real à esquerda e complexo à direita (r * z).
     */
    friend Complexo operator*(double r, const Complexo& c);

    /**
     * @brief Divisão: escalar real no numerador e complexo no denominador (r / z).
     */
    friend Complexo operator/(double r, const Complexo& c);

    // =========================================================================
    // 6. OPERADORES DE ATRIBUIÇÃO COMPOSTA
    // =========================================================================

    /// @brief Soma acumulada com outro complexo: *this = *this + b.
    Complexo& operator+=(const Complexo& b);

    /// @brief Subtração acumulada com outro complexo: *this = *this - b.
    Complexo& operator-=(const Complexo& b);

    /// @brief Multiplicação acumulada com outro complexo: *this = *this * b.
    Complexo& operator*=(const Complexo& b);

    /// @brief Divisão acumulada com outro complexo: *this = *this / b.
    Complexo& operator/=(const Complexo& b);

    /// @brief Soma acumulada com escalar real: *this = *this + r.
    Complexo& operator+=(double r);

    /// @brief Subtração acumulada com escalar real: *this = *this - r.
    Complexo& operator-=(double r);

    /// @brief Multiplicação acumulada com escalar real: *this = *this * r.
    Complexo& operator*=(double r);

    /// @brief Divisão acumulada com escalar real: *this = *this / r.
    Complexo& operator/=(double r);

    /// @brief Potenciação acumulada com expoente real: *this = *this ^ expoente.
    Complexo& operator^=(double expoente);

    /// @brief Potenciação acumulada com expoente complexo: *this = *this ^ expoente.
    Complexo& operator^=(const Complexo& expoente);

    // =========================================================================
    // 7. OPERADORES UNÁRIOS E INCREMENTOS
    // =========================================================================

    /**
     * @brief Operador unário de negação simétrica (-z).
     * @details
     * - Se RETANGULAR: inverte o sinal de ambas as coordenadas (-real, -imag).
     * - Se POLAR: preserva o módulo e adiciona pi ao argumento (pol.arg + M_PI).
     */
    Complexo operator-() const;

    /**
     * @brief Pré-incremento (++z).
     * @details Adiciona 1.0 à componente real e retorna a referência da própria instância (*this).
     */
    Complexo& operator++();

    /**
     * @brief Pós-incremento (z++).
     * @details Salva o estado anterior em cópia, adiciona 1.0 à componente real de *this
     * e retorna a cópia com o valor original.
     */
    Complexo operator++(int);

    /**
     * @brief Pré-decremento (--z).
     * @details Subtrai 1.0 da componente real e retorna a referência da própria instância (*this).
     */
    Complexo& operator--();

    /**
     * @brief Pós-decremento (z--).
     * @details Salva o estado anterior em cópia, subtrai 1.0 da componente real de *this
     * e retorna a cópia com o valor original.
     */
    Complexo operator--(int);

    // =========================================================================
    // 8. OPERADORES DE COMPARAÇÃO
    // Comparam igualdade considerando tolerância de ponto flutuante (EPSILON).
    // =========================================================================

    /**
     * @brief Verifica igualdade entre dois números complexos.
     * @return true se |real1 - real2| < EPSILON e |imag1 - imag2| < EPSILON.
     */
    bool operator==(const Complexo& outro) const;

    /**
     * @brief Verifica desigualdade entre dois números complexos (!(*this == outro)).
     */
    bool operator!=(const Complexo& outro) const;

    /**
     * @brief Verifica se o complexo é igual a um escalar real (parte imaginária próxima de zero).
     */
    bool operator==(double r) const;

    /**
     * @brief Verifica se o complexo é diferente de um escalar real.
     */
    bool operator!=(double r) const;

    /**
     * @brief Comutativo: compara igualdade entre escalar real à esquerda e complexo à direita.
     */
    friend bool operator==(double r, const Complexo& c);

    /**
     * @brief Comutativo: compara desigualdade entre escalar real à esquerda e complexo à direita.
     */
    friend bool operator!=(double r, const Complexo& c);

    // =========================================================================
    // 9. OPERADORES DE POTENCIAÇÃO
    // =========================================================================

    /**
     * @brief Eleva o número complexo a um expoente real: z^expoente.
     * @details Delega a execução para o método membro potencia(expoente).
     */
    Complexo operator^(double expoente) const;

    /**
     * @brief Eleva o número complexo a um expoente inteiro: z^expoente.
     * @details Promove o inteiro para double e calcula a potência.
     */
    Complexo operator^(int expoente) const;

    /**
     * @brief Potenciação complexa geral entre dois complexos: z1^z2.
     * @details Aplica a definição formal: z1^z2 = exp(z2 * ln(z1)).
     * Caso a base z1 possua módulo nulo (|z1| < EPSILON), retorna 0.0 + 0.0i.
     */
    Complexo operator^(const Complexo& expoente) const;

    /**
     * @brief Potenciação de uma base real estritamente positiva por expoente complexo: base^z.
     * @details Aplica base^z = exp(z * ln(base)). Se base <= 0.0, retorna 0.0 + 0.0i.
     */
    friend Complexo operator^(double base, const Complexo& expoente);

    // =========================================================================
    // 10. FUNÇÕES MATEMÁTICAS AVANÇADAS
    // =========================================================================

    /**
     * @brief Retorna o conjugado complexo z*.
     * @details
     * - Se RETANGULAR: retorna a - bi.
     * - Se POLAR: retorna r ∠ (-theta).
     */
    Complexo conjugado() const;

    /**
     * @brief Calcula a potência real pelo Teorema de De Moivre.
     * @details Calcula r_res = r^n e theta_res = theta * n, retornando
     * no mesmo formatoAtual da instância original.
     * @param n Expoente real da potência.
     */
    Complexo potencia(double n) const;

    /**
     * @brief Calcula a função exponencial de base natural e: exp(z).
     * @details Para z = x + iy: exp(z) = e^x * (cos(y) + i*sin(y)).
     * Preserva o formatoAtual de *this no retorno.
     */
    Complexo exponencial() const;

    /**
     * @brief Calcula o logaritmo natural do ramo principal: log(z).
     * @details ln(z) = ln(|z|) + i*arg(z).
     * Se |z| < EPSILON, assume singularidade retornando valor representativo infinitesimal.
     */
    Complexo log() const;

    /**
     * @brief Computa as n raízes enézimas do complexo via Fórmula de De Moivre.
     * @details Módulo de cada raiz: r_k = r^(1/n).
     * Argumento angular da k-ésima raiz: theta_k = (theta + 2*pi*k) / n, com k variando de 0 até n-1.
     * Armazena as raízes sequencialmente no vetor resultados.
     * @param n Ordem da raiz (número estritamente positivo).
     * @param resultados Array pré-alocado de dimensão mínima n para armazenar as raízes.
     */
    void raizes(int n, Complexo resultados[]) const;

    // =========================================================================
    // 11. FUNÇÕES TRIGONOMÉTRICAS COMPLEXAS
    // =========================================================================

    /**
     * @brief Seno complexo (método membro): sin(x + iy) = sin(x)*cosh(y) + i*cos(x)*sinh(y).
     */
    Complexo sin() const;

    /**
     * @brief Cosseno complexo (método membro): cos(x + iy) = cos(x)*cosh(y) - i*sin(x)*sinh(y).
     */
    Complexo cos() const;

    /**
     * @brief Tangente complexa (método membro): tan(z) = sin(z) / cos(z).
     */
    Complexo tan() const;

    /// @brief Seno complexo via função amiga / ADL.
    friend Complexo sin(const Complexo& z);

    /// @brief Cosseno complexo via função amiga / ADL.
    friend Complexo cos(const Complexo& z);

    /// @brief Tangente complexa via função amiga / ADL.
    friend Complexo tan(const Complexo& z);

    // =========================================================================
    // 12. FUNÇÕES HIPERBÓLICAS COMPLEXAS
    // =========================================================================

    /**
     * @brief Seno hiperbólico complexo (método membro): sinh(x + iy) = sinh(x)*cos(y) + i*cosh(x)*sin(y).
     */
    Complexo sinh() const;

    /**
     * @brief Cosseno hiperbólico complexo (método membro): cosh(x + iy) = cosh(x)*cos(y) + i*sinh(x)*sin(y).
     */
    Complexo cosh() const;

    /**
     * @brief Tangente hiperbólica complexa (método membro): tanh(z) = sinh(z) / cosh(z).
     */
    Complexo tanh() const;

    /// @brief Seno hiperbólico complexo via função amiga / ADL.
    friend Complexo sinh(const Complexo& z);

    /// @brief Cosseno hiperbólico complexo via função amiga / ADL.
    friend Complexo cosh(const Complexo& z);

    /// @brief Tangente hiperbólica complexa via função amiga / ADL.
    friend Complexo tanh(const Complexo& z);

    // =========================================================================
    // 13. FUNÇÕES AMIGAS AUXILIARES (COMPATIBILIDADE STL / ADL)
    // Permitem a sintaxe idêntica a std::complex e <cmath> por Argument-Dependent Lookup.
    // =========================================================================

    /// @brief Retorna a parte real do complexo c.
    friend double real(const Complexo& c);

    /// @brief Retorna a parte imaginária do complexo c.
    friend double imag(const Complexo& c);

    /// @brief Retorna o módulo/magnitude absoluta |c|.
    friend double abs(const Complexo& c);

    /// @brief Retorna a fase angular em radianos arg(c).
    friend double arg(const Complexo& c);

    /// @brief Computa a exponencial natural exp(z).
    friend Complexo exp(const Complexo& z);

    /// @brief Computa o logaritmo natural principal log(z).
    friend Complexo log(const Complexo& z);

    // =========================================================================
    // 14. OPERADORES DE FLUXO (I/O STREAMS)
    // =========================================================================

    /**
     * @brief Inserção em fluxo de saída (impressão formatada).
     * @details
     * - Configura a precisão fixa para 2 casas decimais (std::fixed, std::setprecision(2)).
     * - Se |valor| < EPSILON, substitui o valor por 0.0 para evitar "-0.00".
     * - Se RETANGULAR: formata como "a + bi" ou "a - bi" (com sinal positivo ou negativo explícito).
     * - Se POLAR: formata como "r < theta rad".
     * @param os Fluxo de saída (ex: std::cout).
     * @param c Objeto complexo constante a ser impresso.
     * @return Referência ao fluxo de saída para encadeamento.
     */
    friend std::ostream& operator<<(std::ostream& os, const Complexo& c);

    /**
     * @brief Extração a partir de fluxo de entrada (leitura de dados).
     * @details Realiza a leitura sequencial de dois números em ponto flutuante (parte real e imaginária)
     * e instancia o objeto no formato RETANGULAR.
     * @param is Fluxo de entrada (ex: std::cin).
     * @param c Instância de destino para os valores lidos.
     * @return Referência ao fluxo de entrada para encadeamento.
     */
    friend std::istream& operator>>(std::istream& is, Complexo& c);
};

// =============================================================================
// 15. LITERAIS DEFINIDOS PELO USUÁRIO (USER-DEFINED LITERALS)
// Permitem notação expressiva nativa: 2.5_i, 3.5_j, 180.0_deg, 3.14_rad.
// =============================================================================

/**
 * @brief Literal imaginário 'i' para ponto flutuante (ex.: 2.5_i).
 * @return Número complexo 0.0 + imag*i em formato RETANGULAR.
 */
Complexo operator""_i(long double imag);

/**
 * @brief Literal imaginário 'j' para ponto flutuante na notação de engenharia (ex.: 2.5_j).
 * @return Número complexo 0.0 + imag*i em formato RETANGULAR.
 */
Complexo operator""_j(long double imag);

/**
 * @brief Literal imaginário 'i' para números inteiros (ex.: 3_i).
 * @return Número complexo 0.0 + imag*i em formato RETANGULAR.
 */
Complexo operator""_i(unsigned long long int imag);

/**
 * @brief Literal imaginário 'j' para números inteiros (ex.: 3_j).
 * @return Número complexo 0.0 + imag*i em formato RETANGULAR.
 */
Complexo operator""_j(unsigned long long int imag);

/**
 * @brief Converte um valor escalar de graus para radianos (ponto flutuante).
 * @details Multiplica o valor por (pi / 180.0).
 */
double operator""_deg(long double graus);

/**
 * @brief Converte um valor escalar de graus para radianos (inteiro).
 * @details Multiplica o valor por (pi / 180.0).
 */
double operator""_deg(unsigned long long int graus);

/**
 * @brief Retorna diretamente o valor escalar fornecido em radianos (ponto flutuante).
 */
double operator""_rad(long double rad);

/**
 * @brief Retorna diretamente o valor escalar fornecido em radianos (inteiro).
 */
double operator""_rad(unsigned long long int rad);

#endif // COMPLEXO_HPP