# Ex01 - TAD Números Complexos - Bateria Completa com Formato de Saída

O conceito de **Tipo de Dado Abstrato (TDA)** encapsula a representação interna dos dados e expõe um conjunto consistente de operações. Em linguagem C, a união discriminada (tagged union) utilizando `enum`, `struct` e `union` permite suportar representações equivalentes de uma mesma entidade matemática (coordenadas **Retangulares** `z = a + bi` e **Polares** `z = r ∠ θ`) com eficiência de memória.

Implemente o TDA de Números Complexos e complete a rotina principal para executar uma bateria de testes com conversão unificada de formato de saída.

O terminal recebe os seguintes parâmetros em sequência na entrada padrão:

1. **N** (`int` ≥ 1): ordem para o cálculo das raízes enézimas.
2. **R (`double`)**: escalar para operações aritméticas e expoente de potenciação.
3. **F_OUT** (`char`: `R` ou `P`): formato de saída uniforme para todos os resultados complexos impressos.
4. **Complexo A**: caractere de formato (`R` ou `P`) seguido de seus dois valores numéricos.
5. **Complexo B**: caractere de formato (`R` ou `P`) seguido de seus dois valores numéricos.

## **Regras de Saída & Formatação Numérica:**

- Todas as saídas complexas devem ser exibidas convertidas para o formato `F_OUT` com 2 casas decimais.
- Formato Retangular: `a.dd + b.ddi` ou `a.dd - b.ddi`
- Formato Polar: `r.dd < t.dd rad` (com a fase θ normalizada no intervalo `(-π, π]`).
A rotina deve imprimir: `A`, `B`, propriedades de `A`, propriedades de `B`, conjugados, operações fundamentais (`+`, `-`, `*`, `/`), operações mistas com o escalar R (`R + A`, `R - A`, `A - R`, `R * A`, `A / R`, `R / A`), potenciação `A^R`, exponencial `e^A` e as `N` raízes enézimas de `A`.

## **⚠️ Dica de Implementação (Zero Negativo e Ponto Flutuante):**

Em operações de ponto flutuante padrão IEEE 754, valores infinitesimais negativos ou operações nulas podem resultar em `-0.00`. Como o juiz automático compara strings estritas, você deve sanitizar qualquer valor próximo de zero utilizando a função `fabs()` antes da impressão:
`` if (fabs(val) < 1e-2) val = 0.0; ``

## Exemplos de Entrada e Saída

| **Cenário** | **Entrada** | **Saída Esperada** |
| :--- | :--- | :--- |
| **Exemplo 1**<br>(Saída Retangular) | <pre>2 2.0 R<br>R 3.0 4.0<br>R 1.0 -2.0</pre> | <pre>A = 3.00 + 4.00i<br>B = 1.00 - 2.00i<br>PARTS A: MOD=5.00 ARG=0.93 RE=3.00 IMG=4.00<br>PARTS B: MOD=2.24 ARG=-1.11 RE=1.00 IMG=-2.00<br>CONJ(A) = 3.00 - 4.00i<br>CONJ(B) = 1.00 + 2.00i<br>A + B = 4.00 + 2.00i<br>A - B = 2.00 + 6.00i<br>A * B = 11.00 - 2.00i<br>A / B = -1.00 + 2.00i<br>R + A = 5.00 + 4.00i<br>R - A = -1.00 - 4.00i<br>A - R = 1.00 + 4.00i<br>R * A = 6.00 + 8.00i<br>A / R = 1.50 + 2.00i<br>R / A = 0.24 - 0.32i<br>A ^ R = -7.00 + 24.00i<br>exp(A) = -13.13 - 15.20i<br>RAIZES DE A (ordem 2):<br>Raiz 0: 2.00 + 1.00i<br>Raiz 1: -2.00 - 1.00i</pre> |
| **Exemplo 2**<br>(Saída Polar) | <pre>3 2.0 P<br>P 8.0 1.570796<br>P 2.0 0.523599</pre> | <pre>A = 8.00 &lt; 1.57 rad<br>B = 2.00 &lt; 0.52 rad<br>PARTS A: MOD=8.00 ARG=1.57 RE=0.00 IMG=8.00<br>PARTS B: MOD=2.00 ARG=0.52 RE=1.73 IMG=1.00<br>CONJ(A) = 8.00 &lt; -1.57 rad<br>CONJ(B) = 2.00 &lt; -0.52 rad<br>A + B = 9.17 &lt; 1.38 rad<br>A - B = 7.21 &lt; 1.81 rad<br>A * B = 16.00 &lt; 2.09 rad<br>A / B = 4.00 &lt; 1.05 rad<br>R + A = 8.25 &lt; 1.33 rad<br>R - A = 8.25 &lt; -1.33 rad<br>A - R = 8.25 &lt; 1.82 rad<br>R * A = 16.00 &lt; 1.57 rad<br>A / R = 4.00 &lt; 1.57 rad<br>R / A = 0.25 &lt; -1.57 rad<br>A ^ R = 64.00 &lt; 3.14 rad<br>exp(A) = 1.00 &lt; 1.72 rad<br>RAIZES DE A (ordem 3):<br>Raiz 0: 2.00 &lt; 0.52 rad<br>Raiz 1: 2.00 &lt; 2.62 rad<br>Raiz 2: 2.00 &lt; -1.57 rad</pre> |
