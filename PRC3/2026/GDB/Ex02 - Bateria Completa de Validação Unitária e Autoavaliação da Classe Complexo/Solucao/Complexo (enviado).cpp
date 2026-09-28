/* =============================================================================
 * DISCIPLINA: Programacao Orientada a Objetos / Sistemas de Controle
 * ARQUIVO: Complexo.cpp
 *
 * GUIA PEDAGOGICO E TEMPLATE DE IMPLEMENTACAO DA CLASSE COMPLEXO
 *
 * FUNDAMENTACAO CONCEITUAL:
 * Um numero complexo z pode ser interpretado geometricamente como um ponto (ou fasor)
 * no plano de Argand-Gauss atraves de duas metricas canonicas equivalentes:
 *
 * 1. Forma Retangular (Cartesiana):
 *    z = a + bi, onde 'a' representa a projecao no eixo real Re(z) e 'b' a projecao
 *    no eixo imaginario Im(z), satisfazendo a propriedade fundamental i^2 = -1.
 *
 * 2. Forma Polar (Trigonometrica):
 *    z = r * (cos(theta) + i*sin(theta)) = r * e^(i*theta) = r < theta, onde 'r' representa o modulo
 *    ou distancia euclidiana a origem (r = |z| >= 0) e 'theta' representa o argumento
 *    angular (fase) orientado em radianos.
 *
 * O modelo computacional desta classe adota uma Uniao Discriminada (Tagged Union):
 * - Memoria compartilhada entre as estruturas 'rec' (a, b) e 'pol' (r, theta).
 * - A tag 'formatoAtual' atua como sentinela de validade: apenas o par ordenado
 *   correspondente ao formato ativo reflete o estado instantaneo do objeto.
 * - Toda operacao aritmetica mista deve gerar um resultado que preserve o formato
 *   da instancia receptora a esquerda (*this).
 * ============================================================================= */

#include "Complexo.hpp"
#include <iomanip>
#include <sstream>

// =============================================================================
// FUNCOES UTILITARIAS ESTATICAS / PRIVADAS
// =============================================================================

/**
 * @brief Normalizacao do Argumento Angular no Circulo Trigonometrico.
 *
 * FUNDAMENTACAO MATEMATICA:
 * O argumento de um fasor no plano complexo possui natureza periodica com periodo fundamental
 * T = 2*PI radianos:
 *                      theta = theta + 2*k*PI, para k pertencente aos inteiros
 *
 * O ramo principal (determinacao principal do argumento) restringe o angulo ao intervalo:
 *                               -PI < theta <= PI
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Reduza o angulo somando ou subtraindo sucessivas revolucoes completas de 2*PI radianos
 *   ate que o valor pertenca estritamente ao semiplano (-PI, PI].
 * - Tratamento de Ponto Flutuante: Devido ao padrao IEEE-754, representacoes decimais
 *   podem gerar o valor especial -0.00 quando valores negativos infinitesimais convergem a zero.
 *   Se |theta| < EPSILON, atribua theta = +0.0 explicitamente.
 */
double Complexo::normalizarAngulo(double theta) {
    theta = std::fmod (theta, 2.0 * M_PI);
    while (theta > M_PI)  theta -= 2.0 * M_PI;
    while (theta <= -M_PI) theta += 2.0 * M_PI;
    if (std::abs(theta) < EPSILON) theta = 0.0;
    return theta;
}

/**
 * @brief Teste de Igualdade Aproximada com Tolerancia Numerica (Epsilon).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Operacoes em aritmetica de ponto flutuante de dupla precisao (IEEE-754) introduzem erros
 * de truncamento e arredondamento que impedem a comparacao exata por igualdade binaria (==).
 * Dois escalares 'a' e 'b' sao considerados indistinguiveis se a distancia metrica entre eles
 * estiver contida em uma vizinhanca epsilon:
 *                              |a - b| < EPSILON
 */
bool Complexo::quaseIgual(double a, double b) {
    return std::abs(a - b) < EPSILON;
}

// =============================================================================
// 1. FORMA CANONICA ORTODOXA
// =============================================================================

/**
 * @brief Construtor Padrao (Elemento Neutro Aditivo).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Instancia a identidade aditiva no plano complexo:
 *                             z = 0 + 0i = 0 < 0 rad
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Configure 'formatoAtual' como RETANGULAR.
 * - Zere individualmente as coordenadas 'rec.real' e 'rec.imag'.
 */
Complexo::Complexo() : formatoAtual(RETANGULAR) {
    // TODO: Configurar formatoAtual para RETANGULAR e inicializar rec.real = 0.0 e rec.imag = 0.0
    rec.real = 0.0;
    rec.imag = 0.0;
}

/**
 * @brief Construtor de Copia (Semantica de Valor).
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Copie a tag 'outro.formatoAtual' para 'formatoAtual'.
 * - Inspecione a tag: se RETANGULAR, copie a estrutura 'rec'; se POLAR, copie a estrutura 'pol'.
 * - Nao acesse membros inativos da uniao para evitar leitura de memoria indeterminada.
 */
Complexo::Complexo(const Complexo& outro) : formatoAtual(outro.formatoAtual) {
    // TODO: Copiar formatoAtual e o payload ativo correspondente (rec ou pol)
    if (formatoAtual == RETANGULAR) {
        rec = outro.rec;
    } else {
        pol = outro.pol;
    }
}

/**
 * @brief Operador de Atribuicao por Copia (Copy Assignment Operator).
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Proteja contra autoatribuicao comparando ponteiros: if (this != &outro).
 * - Sincronize o formato interno copiando a tag e o par ordenado ativo de 'outro'.
 * - Retorne a referencia da propria instancia (*this) para viabilizar atribuicoes em cadeia.
 */
Complexo& Complexo::operator=(const Complexo& outro) {
    // TODO: Tratar autoatribuicao, sincronizar uniao e retornar *thi
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
 *
 * DIRETRIZ PEDAGOGICA:
 * Como a tagged union e composta exclusivamente por tipos primitivos agregados (structs de double)
 * sem alocacao dinamica na heap (RAII estrito), o destrutor padrao assegura a liberacao correta.
 */
Complexo::~Complexo() {
    // TODO: Finalizar ciclo de vida
}

// =============================================================================
// 2. CONSTRUTORES DE CONVERSAO E TIPOS PRIMITIVOS
// =============================================================================

/**
 * @brief Construtor Principal Parametrizado.
 *
 * FUNDAMENTACAO MATEMATICA:
 * - Mapeamento Retangular: Os parametros fornecidos representam a parte real (a) e imaginaria (b).
 * - Mapeamento Polar: O primeiro parametro determina o raio polar (r = |z| >= 0), enquanto o
 *   segundo parametro estabelece a fase angular (theta), exigindo normalizacao para (-PI, PI].
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Atribua a tag 'f' a 'formatoAtual'.
 * - Se f == RETANGULAR: grave 'real' em rec.real e 'imag' em rec.imag.
 * - Se f == POLAR: grave 'real' em pol.modulo e normalizarAngulo(imag) em pol.arg.
 */
Complexo::Complexo(double real, double imag, Formato f) : formatoAtual(f) {
    // TODO: Inicializar a uniao de acordo com a tag f (lembre-se de normalizar o angulo se POLAR)
    if (f == RETANGULAR) {
        rec.real = real;
        rec.imag = imag;
    } else {
        pol.modulo = real;
        pol.arg = normalizarAngulo(imag);
    }
}

/**
 * @brief Construtor de Conversao: Ponto Flutuante de Precisao Simples (float).
 *
 * DIRETRIZ PEDAGOGICA:
 * Converte escalares float promovendo-os para double e delega a criacao ao construtor principal.
 */
Complexo::Complexo(float real, float imag, Formato f) : Complexo(static_cast<double>(real), static_cast<double>(imag), f){
    // TODO: Promover floats para double e delegar inicializacao
}

/**
 * @brief Construtor de Conversao: Inteiro com Sinal (int).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Todo numero inteiro k pode ser imerso canonicamente no corpo dos numeros complexos
 * atraves da reta real: z = k + 0i.
 */
Complexo::Complexo(int real, int imag, Formato f) : Complexo(static_cast<double>(real), static_cast<double>(imag), f){
    // TODO: Converter inteiros para double e delegar inicializacao
}

/**
 * @brief Construtor de Conversao: Inteiro Longo (long long).
 */
Complexo::Complexo(long long real, long long imag, Formato f) : Complexo(static_cast<double>(real), static_cast<double>(imag), f){
    // TODO: Converter long long para double e delegar inicializacao
}

/**
 * @brief Atribuicao Escalar com Ponto Flutuante (double).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Projeta um numero real puro 'r' no plano complexo: z = r + 0i.
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - O formato de destino deve ser forcado para RETANGULAR.
 * - Atribua rec.real = r e zere a componente imaginaria rec.imag = 0.0.
 */
Complexo& Complexo::operator=(double r) {
    // TODO: Redefinir para RETANGULAR, rec.real = r, rec.imag = 0.0 e retornar *this
    formatoAtual = RETANGULAR;
    rec.real = r;
    rec.imag = 0.0;
    return *this;
}

/**
 * @brief Atribuicao Escalar com Inteiro (int).
 */
Complexo& Complexo::operator=(int r) {
    // TODO: Promover para double e reutilizar operator=(double)
    return *this = static_cast<double>(r);
}

// =============================================================================
// 3. OPERADORES DE CONVERSAO EXPLICITA (CASTS)
// =============================================================================

/**
 * @brief Projecao Ortogonal Real (Cast Explicito para double).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Mapeia o numero complexo em sua projecao unidimensional sobre o eixo das abscissas:
 *                           Re(z) = a = r * cos(theta)
 */
Complexo::operator double() const {
    // TODO: Retornar a parte real da representacao
    return real();
}

/**
 * @brief Projecao Ortogonal Real em Precisao Simples (float).
 */
Complexo::operator float() const {
    // TODO: Retornar a parte real convertida para float
    return static_cast<float>(real());
}

/**
 * @brief Truncamento Inteiro da Componente Real (int).
 */
Complexo::operator int() const {
    // TODO: Retornar a parte real truncada como int
    return static_cast<int>(real());;
}

/**
 * @brief Avaliacao de Nulidade Logica (Cast Explicito para bool).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Um numero complexo e nulo se e somente se sua distancia euclidiana ate a origem
 * for equivalente a zero (|z| = 0).
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Retorne true se o modulo for estritamente superior ao limiar numerico EPSILON.
 */
Complexo::operator bool() const {
    // TODO: Retornar verdadeiro se modulo() > EPSILON
    return modulo() > EPSILON;
}

// =============================================================================
// 4. METODOS DE ACESSO (GETTERS) E CONVERSAO DE FORMATO
// =============================================================================

/**
 * @brief Recuperacao da Parte Real: Re(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 * - Se em coordenadas retangulares: Re(z) = a.
 * - Se em coordenadas polares, aplica a decomposicao trigonometrica:
 *                           Re(z) = r * cos(theta)
 */
double Complexo::real() const {
    // TODO: Obter a componente real diretamente de 'rec' ou calculando r * cos(theta)
    if (formatoAtual == RETANGULAR) {
        return rec.real;
    }
    return pol.modulo * std::cos(pol.arg);
}

/**
 * @brief Recuperacao da Parte Imaginaria: Im(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 * - Se em coordenadas retangulares: Im(z) = b.
 * - Se em coordenadas polares, aplica a decomposicao trigonometrica:
 *                           Im(z) = r * sin(theta)
 */
double Complexo::imag() const {
    // TODO: Obter a componente imaginaria diretamente de 'rec' ou calculando r * sin(theta)
    if (formatoAtual == RETANGULAR) {
        return rec.imag;
    }
    return pol.modulo * std::sin(pol.arg);
}

/**
 * @brief Calculo do Modulo / Magnitude Fasorial: |z|.
 *
 * FUNDAMENTACAO MATEMATICA:
 * - Se em coordenadas polares: |z| = r.
 * - Se em coordenadas retangulares, aplica o Teorema de Pitagoras:
 *                           |z| = sqrt(a^2 + b^2)
 *   Dica: Utilize std::hypot(a, b) para prevenir overflow ou underflow intermediario.
 */
double Complexo::modulo() const {
    // TODO: Obter o modulo diretamente de 'pol' ou calculando std::hypot(real, imag)
    if (formatoAtual == POLAR) {
        return pol.modulo;
    }
    return std::hypot(rec.real, rec.imag);
}

/**
 * @brief Calculo do Argumento Principal: Arg(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 * - Se em coordenadas polares: Arg(z) = theta.
 * - Se em coordenadas retangulares, aplica o arco-tangente de dois argumentos:
 *                        Arg(z) = atan2(b, a)
 *   que determina o quadrante correto do vetor no intervalo (-PI, PI].
 */
double Complexo::arg() const {
    // TODO: Obter o angulo diretamente de 'pol' ou calculando std::atan2(imag, real)
    if (formatoAtual == POLAR) {
        return pol.arg;
    }
    return normalizarAngulo(std::atan2(rec.imag, rec.real));
}

/**
 * @brief Consulta do Formato Interno Ativo.
 */
Formato Complexo::formato() const {
    // TODO: Retornar formatoAtual
    return formatoAtual;
}

/**
 * @brief Conversao Mutua de Coordenadas (Retangular <-> Polar).
 *
 * FUNDAMENTACAO MATEMATICA:
 * As relacoes de transformacao bijetiva entre os sistemas de coordenadas sao dadas por:
 *
 *   [Retangular -> Polar]:
 *      r = sqrt(a^2 + b^2)
 *      theta = atan2(b, a)
 *
 *   [Polar -> Retangular]:
 *      a = r * cos(theta)
 *      b = r * sin(theta)
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Se formatoAtual ja for igual ao novoFormato, retorne uma copia direta de *this.
 * - Caso contrario, construa e retorne uma nova instancia no novo formato requisitado
 *   utilizando os getters auxiliares da classe.
 */
Complexo Complexo::converterPara(Formato novoFormato) const {
    // TODO: Realizar a conversao de coordenadas preservando o valor matematico invariante
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
// 5. OPERADORES ARITMETICOS BINARIOS
// ATENCAO PEDAGOGICA: O numero complexo resultante de qualquer operacao binaria
// deve SEMPRE adotar o formatoAtual da instancia a esquerda (*this).
// =============================================================================

/**
 * @brief Adicao Complexa: z1 + z2.
 *
 * FUNDAMENTACAO MATEMATICA:
 * A soma opera linearmente sobre as componentes cartesianas:
 *                (a1 + b1*i) + (a2 + b2*i) = (a1 + a2) + (b1 + b2)*i
 */
Complexo Complexo::operator+(const Complexo& b) const {
    // TODO: Somar partes reais e imaginarias, convertendo o resultado para formatoAtual
    Complexo res(real() + b.real(), imag() + b.imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Subtracao Complexa: z1 - z2.
 *
 * FUNDAMENTACAO MATEMATICA:
 * A diferenca atua sobre as componentes cartesianas:
 *                (a1 + b1*i) - (a2 + b2*i) = (a1 - a2) + (b1 - b2)*i
 */
Complexo Complexo::operator-(const Complexo& b) const {
    // TODO: Subtrair partes reais e imaginarias, convertendo o resultado para formatoAtual
    Complexo res(real() - b.real(), imag() - b.imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Multiplicacao Complexa: z1 * z2.
 *
 * FUNDAMENTACAO MATEMATICA:
 * A multiplicacao pode ser executada por duas vias:
 *
 * 1. Via Polar (Teorema de De Moivre para Produtos):
 *    (r1 < theta1) * (r2 < theta2) = (r1 * r2) < (theta1 + theta2)
 *    Multiplicam-se os modulos e somam-se os argumentos angulares.
 *
 * 2. Via Cartesiana (Propriedade Distributiva com i^2 = -1):
 *    (a1 + b1*i) * (a2 + b2*i) = (a1*a2 - b1*b2) + (a1*b2 + b1*a2)*i
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Se *this e 'b' estiverem ambos em formato POLAR, utilize a via polar (eficiencia O(1)).
 * - Caso contrario, opere em coordenadas cartesianas e converta o resultado para o formato de *this.
 */
Complexo Complexo::operator*(const Complexo& b) const {
    // TODO: Implementar produto complexo com otimizacao polar
    if (formatoAtual == POLAR && b.formatoAtual == POLAR) {
        return Complexo(pol.modulo * b.pol.modulo, normalizarAngulo(pol.arg + b.pol.arg), POLAR);
    }
    double r1 = real(), i1 = imag();
    double r2 = b.real(), i2 = b.imag();
    Complexo res(r1 * r2 - i1 * i2, r1 * i2 + i1 * r2, RETANGULAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Divisao Complexa: z1 / z2.
 *
 * FUNDAMENTACAO MATEMATICA:
 * A divisao pode ser executada por duas vias:
 *
 * 1. Via Polar:
 *    (r1 < theta1) / (r2 < theta2) = (r1 / r2) < (theta1 - theta2)
 *    Dividem-se os modulos e subtraem-se os argumentos angulares.
 *
 * 2. Via Cartesiana (Multiplicacao pelo Conjugado do Divisor):
 *    (a1 + b1*i) / (a2 + b2*i) = [(a1*a2 + b1*b2) + (b1*a2 - a1*b2)*i] / (a2^2 + b2^2)
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Se *this e 'b' estiverem ambos em formato POLAR, utilize a via polar.
 * - Caso contrario, execute a formula retangular dividindo pela norma ao quadrado (a2^2 + b2^2).
 * - O resultado final deve manter o formatoAtual de *this.
 */
Complexo Complexo::operator/(const Complexo& b) const {
    // TODO: Implementar quociente complexo com otimizacao polar
    if (formatoAtual == POLAR && b.formatoAtual == POLAR) {
        return Complexo(pol.modulo / b.pol.modulo, normalizarAngulo(pol.arg - b.pol.arg), POLAR);
    }
    double r1 = real(), i1 = imag();
    double r2 = b.real(), i2 = b.imag();
    double denom = r2 * r2 + i2 * i2;
    Complexo res((r1 * r2 + i1 * i2) / denom, (i1 * r2 - r1 * i2) / denom, RETANGULAR);
    return res.converterPara(formatoAtual);
    
    return Complexo();
}

/**
 * @brief Adicao Complexo + Escalar Real: z + r.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Afeta exclusivamente o eixo real: (a + bi) + r = (a + r) + bi.
 */
Complexo Complexo::operator+(double r) const {
    // TODO: Implementar z + r
    Complexo res(real() + r, imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Subtracao Complexo - Escalar Real: z - r.
 *
 * FUNDAMENTACAO MATEMATICA:
 * (a + bi) - r = (a - r) + bi.
 */
Complexo Complexo::operator-(double r) const {
    // TODO: Implementar z - r
    Complexo res(real() - r, imag(), RETANGULAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Multiplicacao por Escalar Real: z * r.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Escala linearmente ambas as componentes ou a magnitude:
 *   Cartesiano: (a*r) + (b*r)i
 *   Polar:      (r1 * r) < theta
 */
Complexo Complexo::operator*(double r) const {
    // TODO: Implementar z * r
    if (formatoAtual == POLAR){
        if (r >= 0.0) {
            return Complexo(pol.modulo * r, pol.arg, POLAR);
        } else {
            return Complexo(pol.modulo *(-r), normalizarAngulo(pol.arg + M_PI), POLAR);
        }
    }
    return Complexo(rec.real * r, rec.imag * r, RETANGULAR);
}

/**
 * @brief Divisao por Escalar Real: z / r.
 *
 * FUNDAMENTACAO MATEMATICA:
 * (a/r) + (b/r)i = (r1 / r) < theta.
 */
Complexo Complexo::operator/(double r) const {
    // TODO: Implementar z / r
    if (formatoAtual == POLAR){
        if (r >= 0.0) {
            return Complexo(pol.modulo / r, pol.arg, POLAR);
        } else {
            return Complexo(pol.modulo /(-r), normalizarAngulo(pol.arg + M_PI), POLAR);
        }
    }
    return Complexo(rec.real / r, rec.imag / r, RETANGULAR);
}

/**
 * @brief Adicao Comutativa: r + z.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Pela comutatividade da adicao em C: r + z = z + r.
 */
Complexo operator+(double r, const Complexo& c) {
    // TODO: Implementar comutatividade r + c
    Complexo res(r + c.real(), c.imag(), RETANGULAR);
    return res.converterPara(c.formato());
}

/**
 * @brief Subtracao: Escalar Real no Minuendo: r - z.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Inverte o sinal da componente imaginaria e subtrai a parte real:
 *                     r - (a + bi) = (r - a) - bi
 */
Complexo operator-(double r, const Complexo& c) {
    // TODO: Implementar r - c
    Complexo res(r - c.real(), -c.imag(), RETANGULAR);
    return res.converterPara(c.formato());
    return Complexo();
}

/**
 * @brief Multiplicacao Comutativa: r * z.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Pela comutatividade do produto em C: r * z = z * r.
 */
Complexo operator*(double r, const Complexo& c) {
    // TODO: Implementar comutatividade r * c
    return c * r;
}

/**
 * @brief Divisao de Escalar por Complexo: r / z.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Equivale a escalar o inverso multiplicativo de z:
 *       r / (a + bi) = [(r * a) - (r * b)*i] / (a^2 + b^2)
 */
Complexo operator/(double r, const Complexo& c) {
    // TODO: Implementar quociente r / c
    Complexo num(r, 0.0, RETANGULAR);
    Complexo res = num / c;
    return res.converterPara(c.formato());
}

// =============================================================================
// 6. OPERADORES DE ATRIBUICAO COMPOSTA
// =============================================================================

Complexo& Complexo::operator+=(const Complexo& b) {
    // TODO: Atualizar *this com (*this + b) e retornar *this
    *this = *this + b;
    return *this;
}

Complexo& Complexo::operator-=(const Complexo& b) {
    // TODO: Atualizar *this com (*this - b) e retornar *this
    *this = *this - b;
    return *this;
}

Complexo& Complexo::operator*=(const Complexo& b) {
    // TODO: Atualizar *this com (*this * b) e retornar *this
    *this = *this * b;
    return *this;
}

Complexo& Complexo::operator/=(const Complexo& b) {
    // TODO: Atualizar *this com (*this / b) e retornar *this
    *this = *this / b;
    return *this;
}

Complexo& Complexo::operator+=(double r) {
    // TODO: Somar escalar r a *this e retornar *this
    *this = *this + r;
    return *this;
}

Complexo& Complexo::operator-=(double r) {
    // TODO: Subtrair escalar r de *this e retornar *this
    *this = *this - r;
    return *this;
}

Complexo& Complexo::operator*=(double r) {
    // TODO: Multiplicar *this por escalar r e retornar *this
    *this = *this * r;
    return *this;
}

Complexo& Complexo::operator/=(double r) {
    // TODO: Dividir *this por escalar r e retornar *this
    *this = *this / r;
    return *this;
}

Complexo& Complexo::operator^=(double expoente) {
    // TODO: Atualizar *this com (*this ^ expoente) e retornar *this
    *this = *this ^ expoente;
    return *this;
}

Complexo& Complexo::operator^=(const Complexo& expoente) {
    // TODO: Atualizar *this com (*this ^ expoente) e retornar *this
    *this = *this ^ expoente;
    return *this;
}

// =============================================================================
// 7. OPERADORES UNARIOS E INCREMENTOS
// =============================================================================

/**
 * @brief Negacao Unaria (Inversao Simetrica): -z.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Equivale geometricamente a uma reflexao atraves da origem (rotacao de 180 graus ou PI radianos):
 *   Cartesiano: -(a + bi) = (-a) + (-b)i
 *   Polar:      - (r < theta) = r < (theta + PI)
 */
Complexo Complexo::operator-() const {
    // TODO: Implementar inversao de sinal conforme o formatoAtual
    if (formatoAtual == RETANGULAR) {
        return Complexo(-rec.real, -rec.imag, RETANGULAR);
    } else {
        return Complexo(pol.modulo, normalizarAngulo(pol.arg + M_PI), POLAR);
    }
}

/**
 * @brief Pre-Incremento Unitario Real: ++z.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Translada o numero complexo em +1 unidade sobre o eixo real: z' = (a + 1) + bi.
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Atualize o objeto diretamente e retorne a referencia da propria instancia (*this).
 */
Complexo& Complexo::operator++() {
    // TODO: Incrementar parte real em 1.0 e retornar *this
    if (formatoAtual == RETANGULAR) {
        rec.real += 1.0;
    }else {
        *this = Complexo(real() + 1.0, imag(), RETANGULAR).converterPara(POLAR);
    }
    return *this;
}

/**
 * @brief Pos-Incremento Unitario Real: z++.
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Salve o estado previo do objeto em uma variavel temporaria: Complexo temp(*this).
 * - Aplique o pre-incremento em *this (++(*this)).
 * - Retorne o estado previo salvo em 'temp' por valor.
 */
Complexo Complexo::operator++(int) {
    // TODO: Salvar copia, incrementar *this e retornar copia
    Complexo copia(*this);
    ++(*this);
    return copia;
}

/**
 * @brief Pre-Decremento Unitario Real: --z.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Translada o numero complexo em -1 unidade sobre o eixo real: z' = (a - 1) + bi.
 */
Complexo& Complexo::operator--() {
    // TODO: Decrementar parte real em 1.0 e retornar *this
    if (formatoAtual == RETANGULAR) {
        rec.real -= 1.0;
    } else {
        *this = Complexo(real() - 1.0, imag(), RETANGULAR).converterPara(POLAR);
    }
    return *this;
}

/**
 * @brief Pos-Decremento Unitario Real: z--.
 */
Complexo Complexo::operator--(int) {
    // TODO: Salvar copia, decrementar *this e retornar copia
    Complexo copia(*this);
    --(*this);
    return copia;
}

// =============================================================================
// 8. OPERADORES DE COMPARACAO COM TOLERANCIA EPSILON
// =============================================================================

/**
 * @brief Comparacao de Igualdade entre Complexos: z1 == z2.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Dois complexos z1 e z2 sao equivalentes se suas componentes ortogonais
 * coincidirem simultaneamente dentro da vizinhanca de incerteza EPSILON:
 *               |Re(z1) - Re(z2)| < EPSILON e |Im(z1) - Im(z2)| < EPSILON
 */
bool Complexo::operator==(const Complexo& outro) const {
    // TODO: Comparar partes reais e imaginarias utilizando quaseIgual
    return quaseIgual(real(), outro.real()) && quaseIgual(imag(), outro.imag());
}

bool Complexo::operator!=(const Complexo& outro) const {
    // TODO: Retornar negacao de operator==
    return !(*this == outro);
}

/**
 * @brief Comparacao de Igualdade com Escalar: z == r.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Um complexo equivale a um escalar real se sua projecao imaginaria for desprezivel:
 *                   |Re(z) - r| < EPSILON e |Im(z)| < EPSILON
 */
bool Complexo::operator==(double r) const {
    // TODO: Comparar real() com r e imag() com 0.0 usando quaseIgual
    return quaseIgual(real(), r) && quaseIgual(imag(), 0.0);
}

bool Complexo::operator!=(double r) const {
    // TODO: Retornar negacao de operator==(double)
    return !(*this == r);
}

bool operator==(double r, const Complexo& c) {
    // TODO: Avaliar comutatividade delegando para c == r
    return c == r;;
}

bool operator!=(double r, const Complexo& c) {
    // TODO: Retornar negacao de operator==(r, c)
    return c != r;
}

// =============================================================================
// 9. OPERADORES DE POTENCIACAO
// =============================================================================

/**
 * @brief Potencia com Expoente Real: z^n.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Delega o calculo para a Primeira Formula de De Moivre implementada em potencia(n).
 */
Complexo Complexo::operator^(double expoente) const {
    // TODO: Delegar para metodo membro potencia(expoente)
    return potencia(expoente);
}

Complexo Complexo::operator^(int expoente) const {
    // TODO: Promover inteiro para double e calcular potencia
    return potencia(static_cast<double>(expoente));
}

/**
 * @brief Potenciacao Complexa Generalizada: z1 ^ z2.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Atraves do logaritmo complexo e da funcao exponencial analitica, generaliza-se:
 *                      z1^(z2) = exp(z2 * ln(z1))
 *
 * Onde:
 *   ln(z1) = ln(|z1|) + i*Arg(z1)
 *
 * PONTO CRITICO DE SINGULARIDADE:
 * Se a base for nula (|z1| < EPSILON), ln(0) diverge para o infinito negativo.
 * Para qualquer expoente com parte real estritamente positiva, defina o limite matematico:
 *                             0^(z2) = 0 + 0i
 * Retorne Complexo(0.0, 0.0, formatoAtual).
 */
Complexo Complexo::operator^(const Complexo& expoente) const {
    // TODO: Tratar base zero; caso contrario, calcular exp(expoente * ln(this))
    if (modulo() < EPSILON) {
        return Complexo(0.0, 0.0, formatoAtual);
    }
    Complexo log_base = this->log();
    Complexo produto = expoente * log_base;
    Complexo res = produto.exponencial();
    return res.converterPara(formatoAtual);
}

/**
 * @brief Potencia de Base Real Positiva com Expoente Complexo: b ^ z.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Para uma constante b real, b > 0:
 *                         b^z = exp(z * ln(b))
 *
 * Onde ln(b) representa o logaritmo neperiano real padrao (std::log).
 * Se b <= 0.0, a operacao esta fora do dominio analitico continuo: retorne (0.0, 0.0).
 */
Complexo operator^(double base, const Complexo& expoente) {
    // TODO: Tratar base <= 0; caso contrario, calcular exp(expoente * std::log(base))
    if (base <= 0.0) {
        return Complexo(0.0, 0.0, expoente.formato());
    }
    Complexo produto = expoente * std::log(base);
    Complexo res = produto.exponencial();
    return res.converterPara(expoente.formato());
}

// =============================================================================
// 10. FUNCOES MATEMATICAS AVANCADAS
// =============================================================================

/**
 * @brief Conjugacao Complexa: z*.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Representa a reflexao geometrica em relacao ao eixo horizontal real:
 *   Forma Retangular: (a + bi)* = a - bi
 *   Forma Polar:      (r < theta)* = r < (-theta)
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - O resultado deve preservar estritamente o 'formatoAtual' da instancia.
 */
Complexo Complexo::conjugado() const {
    // TODO: Inverter o sinal da componente imaginaria ou da fase angular
    if (formatoAtual == RETANGULAR) {
        return Complexo(rec.real, -rec.imag, RETANGULAR);
    } else {
        return Complexo(pol.modulo, normalizarAngulo(-pol.arg), POLAR);
    }
}

/**
 * @brief Primeira Formula de De Moivre: z^n.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Para qualquer n real, expressando z na forma trigonometrica r * e^(i*theta):
 *               z^n = [r * e^(i*theta)]^n = (r^n) * e^(i * n * theta)
 *
 * Modulo resultante:      r_novo = r^n
 * Fase angular resultante: theta_novo = n * theta
 */
Complexo Complexo::potencia(double n) const {
    // TODO: Calcular novo modulo e argumento angular aplicando De Moivre
    if (modulo() < EPSILON) {
        return Complexo(0.0, 0.0, formatoAtual);
    }
    double r_novo = std::pow(modulo(), n);
    double theta_novo = normalizarAngulo(arg() * n);
    Complexo res(r_novo, theta_novo, POLAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Exponencial Analitica Complexa: exp(z) = e^z.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Aplicando a Identidade de Euler (e^(i*y) = cos(y) + i*sin(y)) para z = x + iy:
 *              e^(x + iy) = e^x * e^(iy) = e^x * (cos(y) + i*sin(y))
 *
 * Em notacao polar fasorial:
 *   Magnitude:  r = e^x = std::exp(real())
 *   Fase:       theta = y = imag()
 */
Complexo Complexo::exponencial() const {
    // TODO: Computar e^real() < imag() e converter para formatoAtual
    double r = std::exp(real());
    double theta = normalizarAngulo(imag());
    Complexo res(r, theta, POLAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Logaritmo Natural Complexo do Ramo Principal: log(z) = ln(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 * A funcao inversa da exponencial complexa no ramo principal (k = 0) e dada por:
 *                    ln(z) = ln(|z|) + i * Arg(z)
 *
 * Parte Real:       Re(ln(z)) = ln(r) = std::log(modulo())
 * Parte Imaginaria: Im(ln(z)) = Arg(z) em (-PI, PI]
 *
 * TRATAMENTO DE SINGULARIDADE:
 * Se |z| < EPSILON, ln(0) e indefinido (-infinito). Nesses casos, retorne um numero com parte real
 * extremamente negativa (ex.: -1e9) e parte imaginaria nula em formato RETANGULAR.
 */
Complexo Complexo::log() const {
    // TODO: Tratar singularidade de modulo nulo; caso contrario, retornar ln(r) + i*theta
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

/**
 * @brief Segunda Formula de De Moivre: Raizes Enezimas (raiz n de z).
 *
 * FUNDAMENTACAO MATEMATICA:
 * A equacao w^n = z admite exatamente 'n' solucoes complexas distintas no plano.
 * Para z = r < theta, as 'n' raizes w_k distribuem-se sobre uma circunferencia de raio
 * R = (r)^(1/n) com espacamento angular uniforme de 2*PI/n radianos:
 *
 *        w_k = [ r^(1/n) ] < [ (theta + 2*k*PI) / n ], para k = 0, 1, 2, ..., n-1
 *
 * DIRETRIZ DE IMPLEMENTACAO:
 * - Valide se n > 0.
 * - Calcule o raio fundamental R = std::pow(modulo(), 1.0 / n).
 * - Itere k de 0 ate n - 1, calculando cada fase angular theta_k = (arg() + 2*PI*k) / n.
 * - Armazene as instancias sequencialmente no vetor 'resultados[k]', convertendo-as
 *   para o 'formatoAtual' da classe original.
 */
void Complexo::raizes(int n, Complexo resultados[]) const {
    // TODO: Calcular e armazenar as n raizes fasoriais no array resultados
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
// 11. FUNCOES TRIGONOMETRICAS COMPLEXAS
// =============================================================================

/**
 * @brief Seno Complexo: sin(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Pela definicao das funcoes circulares via exponenciais de Euler:
 *                      sin(z) = (e^(iz) - e^(-iz)) / (2i)
 *
 * Expandindo analiticamente para z = x + iy:
 *              sin(x + iy) = sin(x)*cosh(y) + i * cos(x)*sinh(y)
 *
 * Onde cosh e sinh representam o cosseno e seno hiperbolicos reais.
 */
Complexo Complexo::sin() const {
    // TODO: Calcular sin(x)*cosh(y) + i*cos(x)*sinh(y) e converter para formatoAtual
    double x = real();
    double y = imag();
    Complexo res(std::sin(x) * std::cosh(y), std::cos(x) * std::sinh(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Cosseno Complexo: cos(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 *                      cos(z) = (e^(iz) + e^(-iz)) / 2
 *
 * Expandindo analiticamente para z = x + iy:
 *              cos(x + iy) = cos(x)*cosh(y) - i * sin(x)*sinh(y)
 */
Complexo Complexo::cos() const {
    // TODO: Calcular cos(x)*cosh(y) - i*sin(x)*sinh(y) e converter para formatoAtual
    double x = real();
    double y = imag();
    Complexo res(std::cos(x) * std::cosh(y), -std::sin(x) * std::sinh(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Tangente Complexa: tan(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Relaciona o seno e o cosseno complexos:
 *                            tan(z) = sin(z) / cos(z)
 */
Complexo Complexo::tan() const {
    // TODO: Calcular sin() / cos()
    return this->sin() / this->cos();
}

Complexo sin(const Complexo& z) {
    // TODO: Delegar para z.sin()
    return z.sin();
}

Complexo cos(const Complexo& z) {
    // TODO: Delegar para z.cos()
    return z.cos();
}

Complexo tan(const Complexo& z) {
    // TODO: Delegar para z.tan()
    return z.tan();
}

// =============================================================================
// 12. FUNCOES HIPERBOLICAS COMPLEXAS
// =============================================================================

/**
 * @brief Seno Hiperbolico Complexo: sinh(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Definicao:
 *                      sinh(z) = (e^z - e^(-z)) / 2
 *
 * Expandindo para z = x + iy com identidades de rotacao:
 *              sinh(x + iy) = sinh(x)*cos(y) + i * cosh(x)*sin(y)
 */
Complexo Complexo::sinh() const {
    // TODO: Calcular sinh(x)*cos(y) + i*cosh(x)*sin(y) e converter para formatoAtual
    double x = real();
    double y = imag();
    Complexo res(std::sinh(x) * std::cos(y), std::cosh(x) * std::sin(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Cosseno Hiperbolico Complexo: cosh(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 * Definicao:
 *                      cosh(z) = (e^z + e^(-z)) / 2
 *
 * Expandindo para z = x + iy:
 *              cosh(x + iy) = cosh(x)*cos(y) + i * sinh(x)*sin(y)
 */
Complexo Complexo::cosh() const {
    // TODO: Calcular cosh(x)*cos(y) + i*sinh(x)*sin(y) e converter para formatoAtual
    double x = real();
    double y = imag();
    Complexo res(std::cosh(x) * std::cos(y), std::sinh(x) * std::sin(y), RETANGULAR);
    return res.converterPara(formatoAtual);
}

/**
 * @brief Tangente Hiperbolica Complexa: tanh(z).
 *
 * FUNDAMENTACAO MATEMATICA:
 *                            tanh(z) = sinh(z) / cosh(z)
 */
Complexo Complexo::tanh() const {
    // TODO: Calcular sinh() / cosh()
    return this->sinh() / this->cosh();
}

Complexo sinh(const Complexo& z) {
    // TODO: Delegar para z.sinh()
    return z.sinh();
}

Complexo cosh(const Complexo& z) {
    // TODO: Delegar para z.cosh()
    return z.cosh();
}

Complexo tanh(const Complexo& z) {
    // TODO: Delegar para z.tanh()
    return z.tanh();
}

// =============================================================================
// 13. FUNCOES AMIGAS AUXILIARES (PADRAO STL / ADL)
// Provêm compatibilidade de sobrecarga para Argument-Dependent Lookup (ADL),
// permitindo utilizar a mesma sintaxe da biblioteca padrao <complex>.
// =============================================================================

double real(const Complexo& c) {
    // TODO: Retornar c.real()
    return c.real();
}

double imag(const Complexo& c) {
    // TODO: Retornar c.imag()
    return c.imag();
}

double abs(const Complexo& c) {
    // TODO: Retornar c.modulo()
    return c.modulo();
}

double arg(const Complexo& c) {
    // TODO: Retornar c.arg()
    return c.arg();;
}

Complexo exp(const Complexo& z) {
    // TODO: Retornar z.exponencial()
    return z.exponencial();
}

Complexo log(const Complexo& z) {
    // TODO: Retornar z.log()
    return z.log();
}

// =============================================================================
// 14. OPERADORES DE FLUXO (I/O STREAMS)
// =============================================================================

/**
 * @brief Insercao em Fluxo de Saida (Impressao Padronizada).
 *
 * ESPECIFICACAO DE FORMATACAO:
 * - A saida deve ser fixada com precisao de 2 casas decimais (std::fixed, std::setprecision(2)).
 * - Valores menores que EPSILON devem ser convertidos para +0.00 absoluto, impedindo
 *   que o sinal de menos apareca em zeros flutuantes (ex.: "-0.00").
 *
 * CASO 1: Formato RETANGULAR
 *   Padrao: "a + bi"  ou  "a - bi"
 *   Exemplos:
 *     Se a = 3.0, b = 4.0   --> Imprime "3.00 + 4.00i"
 *     Se a = 2.0, b = -5.0  --> Imprime "2.00 - 5.00i"
 *     Note o espacamento obrigatorio em torno do operador de sinal (" + " ou " - ").
 *
 * CASO 2: Formato POLAR
 *   Padrao: "r < theta rad"
 *   Exemplo:
 *     Se r = 5.0, theta = 0.93  --> Imprime "5.00 < 0.93 rad"
 */
std::ostream& operator<<(std::ostream& os, const Complexo& c) {
    // TODO: Implementar impressao formatada com 2 casas decimais e correcao de -0.00
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
        
        os << m << " < " << a << " rad ";
    }
    os.flags(flags_anteriores);
    os.precision(precisao_anterior);
    return os;
}

/**
 * @brief Extracao a partir de Fluxo de Entrada (Parsing de Dados).
 *
 * PROTOCOLO DE LEITURA:
 * - Realize a leitura sequencial de dois numeros em ponto flutuante a partir do fluxo: is >> r >> i.
 * - Instancie e atribua a variavel de destino 'c' como Complexo(r, i, RETANGULAR).
 */
std::istream& operator>>(std::istream& is, Complexo& c) {
    // TODO: Ler dois doubles e atribuir como complexo retangular a 'c'
    double r = 0.0, i = 0.0;
    if (is >> r >> i) {
        c = Complexo(r, i, RETANGULAR);
    }
    return is;
}

// =============================================================================
// 15. LITERAIS DEFINIDOS PELO USUARIO (USER-DEFINED LITERALS - UDL)
//
// FUNDAMENTACAO PEDAGOGICA:
// Os literais customizados (introduzidos no padrao C++11) viabilizam a representacao
// sintatica direta de grandezas complexas e angulares na propria base de codigo,
// tornando as expressoes matematicas identicas aos modelos analiticos teoricos:
//
//   Exemplos:
//     Complexo z1 = 4.0 + 3.0_i;        // Notacao matematica tradicional (i)
//     Complexo z2 = 2.5 - 1.2_j;        // Notacao da engenharia eletrica (j)
//     double ang  = 90.0_deg;           // Converte automaticamente graus para PI/2 rad
//     double rad  = 3.14159_rad;        // Unidade angular dimensional explicita
// =============================================================================

/**
 * @brief Literal Imaginario Ponto Flutuante 'i': z = 0 + imag*i.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Constroi um numero imaginario puro: z = 0.0 + (long double)i.
 * Assinatura exigida pelo compilador para sufixos literais com ponto flutuante: long double.
 */
Complexo operator""_i(long double imag) {
    // TODO: Retornar Complexo(0.0, static_cast<double>(imag), RETANGULAR)
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

/**
 * @brief Literal Imaginario Ponto Flutuante 'j' (Convencao da Engenharia): z = 0 + imag*j.
 *
 * FUNDAMENTACAO MATEMATICA:
 * Na engenharia e teoria de circuitos, a letra 'j' substitui 'i' para evitar ambiguidade
 * com a variavel de corrente eletrica instantanea i(t). O comportamento algebrico e identico: j^2 = -1.
 */
Complexo operator""_j(long double imag) {
    // TODO: Retornar Complexo(0.0, static_cast<double>(imag), RETANGULAR)
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

/**
 * @brief Literal Imaginario Inteiro 'i': z = 0 + imag*i.
 *
 * DIRETRIZ PEDAGOGICA:
 * Permite sintaxe natural com inteiros (ex.: 5_i).
 * A assinatura exigida pelo padrao C++ para literais inteiros e: unsigned long long int.
 */
Complexo operator""_i(unsigned long long int imag) {
    // TODO: Converter para double e retornar Complexo imaginario puro
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

/**
 * @brief Literal Imaginario Inteiro 'j': z = 0 + imag*j.
 */
Complexo operator""_j(unsigned long long int imag) {
    // TODO: Converter para double e retornar Complexo imaginario puro
    return Complexo(0.0, static_cast<double>(imag), RETANGULAR);
}

/**
 * @brief Conversao Dimensional de Graus para Radianos: theta_rad = theta_graus * (PI / 180).
 *
 * FUNDAMENTACAO MATEMATICA:
 * O argumento das funcoes trigonometricas e transcendentais da biblioteca padrao (<cmath>)
 * assume angulos estritamente expressos na unidade do Sistema Internacional (radianos).
 * O fator de conversao exato decorre da relacao de arco: 180 graus = PI rad.
 */
double operator""_deg(long double graus) {
    // TODO: Retornar static_cast<double>(graus) * (M_PI / 180.0)
    return static_cast<double>(graus) * (M_PI / 180.0);
}

/**
 * @brief Conversao Dimensional Inteira de Graus para Radianos: theta_rad = theta_graus * (PI / 180).
 *
 * Permite expressar rotacoes fixas como 45_deg, 90_deg, 180_deg.
 */
double operator""_deg(unsigned long long int graus) {
    // TODO: Retornar static_cast<double>(graus) * (M_PI / 180.0)
    return static_cast<double>(graus) * (M_PI / 180.0);
}

/**
 * @brief Sufixo Literal de Radianos para Ponto Flutuante: rad.
 *
 * FUNDAMENTACAO PEDAGOGICA:
 * Atua como marcador semantico de auto-documentacao no codigo-fonte, garantindo que
 * o valor fornecido ja se encontra na escala correta em radianos.
 */
double operator""_rad(long double rad) {
    // TODO: Retornar static_cast<double>(rad)
    return static_cast<double>(rad);
}

/**
 * @brief Sufixo Literal de Radianos para Inteiros: rad.
 */
double operator""_rad(unsigned long long int rad) {
    // TODO: Retornar static_cast<double>(rad)
    return static_cast<double>(rad);
}
