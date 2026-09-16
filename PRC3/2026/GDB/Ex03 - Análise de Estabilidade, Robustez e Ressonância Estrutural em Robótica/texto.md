# Ex03 - Análise de Estabilidade, Robustez e Ressonância Estrutural em Robótica

No projeto de manipuladores robóticos de alta precisão, o controle de juntas no domínio da frequência contínua (`s = jω`) exige a avaliação de atrasos digitais de transporte, acoplamento de impedância mecânica flexível e modos estruturais ressonantes.

Utilize a classe `Complexo` em C++ (com representação interna em união discriminada retangular/polar) para implementar a análise diagnóstica completa do atuador robótico.

O terminal recebe os seguintes parâmetros em sequência em uma única linha na entrada padrão:

1. **K** (`double` > 0): Ganho estático da malha direta do atuador.
2. **tau** (`double` > 0): Constante de tempo do motor eletromecânico (em segundos).
3. **omega** (`double` > 0): Frequência angular de ensaio senoidal (em rad/s).
4. **Td** (`double` ≥ 0): Atraso puro de transporte e comunicação digital (em segundos).
5. **alpha** (`double` ≥ 0): Coeficiente de amortecimento viscoelástico do elo.
6. **beta** (`double` > 0): Coeficiente de propagação modal da estrutura.
7. **d** (`double` > 0): Comprimento normalizado do elo robótico.

## **Modelagem Matemática:**

- Planta com atraso: `G(jω) = [K / (jω · (tau · jω + 1))] · e^(-jω · Td)`
- Sensibilidade da malha: `S(jω) = (1 + G(jω))^(-1)`
- Sensibilidade complementar (Malha Fechada): `T(jω) = G(jω) / (1 + G(jω))`
- Impedância mecânica de entrada normalizada: `Z_in = tanh(gamma · d)`, onde `gamma = alpha + j·beta`
- Energia de ruído no atuador: `E_ruido = Re(G(jω) · G*(jω))`
- Magnitude e Fase: `Magnitude G = 20 · log10(|G(jω)|) dB`, `Fase G = Arg(G(jω)) em graus`
- Polos estruturais de ressonância: 4 raízes complexas da equação `s^4 = -K` (ou seja, as 4 raízes de `-K`).

## **Regras de Diagnóstico Automatizado:**

**Robustez:** Se `|S(jω)| ≤ 1.5: ROBUSTEZ: MARGEM ADEQUADA`; senão: `ROBUSTEZ: ALERTA DE PICOS DE RESSONANCIA.`
**Atuador:** Se `E_ruido ≤ 25.0: ATUADOR: RUIDO TOLERAVEL`; senão: `ATUADOR: ALERTA: SATURACAO DO ATUADOR.`
**Estabilidade:** Se `Fase G > -180.0°: ESTABILIDADE: MALHA FECHADA ESTAVEL`; senão: `ESTABILIDADE: ALERTA: CRITERIO DE NYQUIST VIOLADO.`
**Acoplamento:** Se `Re(Z_in) ≥ 0.5: ACOPLAMENTO: IMPEDANCIA COMPATIVEL`; senão: `ACOPLAMENTO: ALERTA DE REFLEXAO MECANICA.`

**⚠️ Dica de Ponto Flutuante:** Para evitar `-0.00` nas saídas, valores infinitesimais com `std::abs(val) < 1e-9` devem ser tratados como `0.0`, antes da impressão.

**Acesse o link:** [Arquivos comentados](https://onlinegdb.com/cnlwWX26vv)

## Exemplo de Entrada e Saída

| Entrada | Saída Esperada |
| :--- | :--- |
| `10.0 0.5 2.0 0.05 0.2 1.5 1.0` | <pre>G(jw) = -2.74 - 2.24i<br>S(jw) = -0.22 + 0.28i<br>T(jw) = 1.22 - 0.28i<br>Z_in = 4.51 + 1.55i<br>Magnitude G: 10.97 dB<br>Fase G: -140.73 deg<br>&#124;S(jw)&#124;: 0.35<br>E_ruido: 12.50<br>Polos de Ressonancia:<br>P0 = 1.26 + 1.26i<br>P1 = -1.26 + 1.26i<br>P2 = -1.26 - 1.26i<br>P3 = 1.26 - 1.26i<br>ROBUSTEZ: MARGEM ADEQUADA<br>ATUADOR: RUIDO TOLERAVEL<br>ESTABILIDADE: MALHA FECHADA ESTAVEL<br>ACOPLAMENTO: IMPEDANCIA COMPATIVEL</pre> |