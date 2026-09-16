# Ex01 - TAD Números Complexos - Bateria Completa com Formato de Saída

O conceito de *Tipo de Dado Abstrato (TDA)* encapsula a representação interna dos dados e expõe um conjunto consistente de operações. Em linguagem C, a união discriminada (tagged union) utilizando `enum`, `struct` e `union` permite suportar representações equivalentes de uma mesma entidade matemática (coordenadas *Retangulares* `z = a + bi` e *Polares* `z = r ∠ θ`) com eficiência de memória.

Implemente o TDA de Números Complexos e complete a rotina principal para executar uma bateria de testes com conversão unificada de formato de saída.

O terminal recebe os seguintes parâmetros em sequência na entrada padrão:

1. *N* (`int` ≥ 1): ordem para o cálculo das raízes enézimas.
2. *R (`double`)*: escalar para operações aritméticas e expoente de potenciação.
3. *F_OUT* (`char`: `R` ou `P`): formato de saída uniforme para todos os resultados complexos impressos.
4. *Complexo A*: caractere de formato (`R` ou `P`) seguido de seus dois valores numéricos.
5. *Complexo B*: caractere de formato (`R` ou `P`) seguido de seus dois valores numéricos.

## Regras de Saída & Formatação Numérica:

- Todas as saídas complexas devem ser exibidas convertidas para o formato `F_OUT` com 2 casas decimais.
- Formato Retangular: `a.dd + b.ddi` ou `a.dd - b.ddi`
- Formato Polar: `r.dd < t.dd rad` (com a fase θ normalizada no intervalo `(-π, π]`).
A rotina deve imprimir: `A`, `B`, propriedades de `A`, propriedades de `B`, conjugados, operações fundamentais (`+`, `-`, `*`, `/`), operações mistas com o escalar R (`R + A`, `R - A`, `A - R`, `R * A`, `A / R`, `R / A`), potenciação `A^R`, exponencial `e^A` e as `N` raízes enézimas de `A`.

## ⚠️ Dica de Implementação (Zero Negativo e Ponto Flutuante):

Em operações de ponto flutuante padrão IEEE 754, valores infinitesimais negativos ou operações nulas podem resultar em `-0.00`. Como o juiz automático compara strings estritas, você deve sanitizar qualquer valor próximo de zero utilizando a função `fabs()` antes da impressão:
`` if (fabs(val) < 1e-2) val = 0.0; ``