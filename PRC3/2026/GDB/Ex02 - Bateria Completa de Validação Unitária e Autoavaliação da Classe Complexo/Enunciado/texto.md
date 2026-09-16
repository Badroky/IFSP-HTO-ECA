# Ex02 - Bateria Completa de Validação Unitária e Autoavaliação da Classe Complexo

Este exercício tem como objetivo validar formalmente a integridade matemática, estrutural e sintática de todos os recursos implementados na sua classe Complexo em C++.

---

O arquivo `main.cpp` já vem completamente implementado e atua como uma suíte de testes unitários automatizada com feedback visual colorido no terminal. Você deve implementar estritamente os métodos no arquivo `Complexo.cpp` respeitando o contrato (definição da classe) de `Complexo.hpp`.

*O programa não recebe entradas pela console* e avalia 12 baterias de testes com tolerância numérica de precisão:

    1. *Construtores, Atribuição Escalar, Casts e Getters*
    2. *Operações Aritméticas Básicas (Complexo × Complexo)*
    3. *Aritmética com Escalar Real e Comutatividade*
    4. *Operadores de Atribuição Composta (`+=`, `-=`, `*=`, `/=`, `^=`)*
    5. *Operadores Unários e Incrementos/Decrementos*
    6. *Comparadores com Tolerância Epsilon (`==`, `!=`)*
    7. *Operadores de Potenciação (`operator^`)*
    8. *Conjugado, Potência, Exponencial e Logaritmo*
    9. *Raízes Enézimas (Fórmula de De Moivre)*
    10. *Funções Trigonométricas Complexas (`sin`, `cos`, `tan`)*
    11. *Funções Hiperbólicas Complexas (`sinh`, `cosh`, `tanh`)*
    12. *Funções Livres (ADL), Fluxos I/O (`<<`, `>>`) e Literais de Usuário*

Acesse o link: [arquivos comentados](https://onlinegdb.com/cnlwWX26vv)

## Saída Esperada
---
``
[TESTE 01] Construtores e Conversao de Formato: APROVADO
[TESTE 02] Operacoes Aritmeticas Basicas: APROVADO
[TESTE 03] Aritmetica com Escalar e Comutatividade: APROVADO
[TESTE 04] Atribuicao Composta: APROVADO
[TESTE 05] Operadores Unarios e Incrementos: APROVADO
[TESTE 06] Comparadores e Igualdade com Epsilon: APROVADO
[TESTE 07] Potenciacao Real e Complexa: APROVADO
[TESTE 08] Conjugado, Exponencial e Logaritmo: APROVADO
[TESTE 09] Raizes Enezimas: APROVADO
[TESTE 10] Funcoes Trigonometricas: APROVADO
[TESTE 11] Funcoes Hiperbolicas: APROVADO
[TESTE 12] Funcoes Livres e Literais de Usuario: APROVADO
RESULTADO GLOBAL: TODOS OS RECURSOS FORAM VALIDADOS COM SUCESSO
``