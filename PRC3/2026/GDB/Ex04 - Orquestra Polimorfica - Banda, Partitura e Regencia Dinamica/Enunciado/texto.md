# Ex04 - Orquestra Polimorfica: Banda, Partitura e Regencia Dinamica

Em uma orquestra, diferentes músicos tocam instrumentos variados divididos em famílias (cordas, sopro e percussão). Cada instrumento possui a sua própria maneira de emitir som ao interpretar uma nota musical. O maestro é o responsável por conduzir a apresentação: consulta a partitura nota por nota e comanda a banda. Contudo, nem todos os instrumentos tocam em todos os compassos: cada nota na partitura define um filtro indicando quais famílias de instrumentos estão ativas naquele momento. Se uma família não estiver habilitada, os seus músicos permanecem em silêncio.

Seu objetivo é implementar o sistema respeitando:
- Encapsulamento estrito (sem expor ponteiros internos ou nós das estruturas encadeadas);
- Composição via listas encadeadas manuais (sem containers da STL como vector ou list);
- Polimorfismo em tempo de execução com classes derivadas e métodos virtuais.

## Formato de Entrada

Todos os argumentos são separados por espaços ou quebras de linha:
- `nomeBanda` (string), `nomeMaestro` (string), `nomeMusica` (string), `qtdMusicos` (int)
- Para cada um dos `qtdMusicos`:
  - `tipo` (char: 'C' para Cordas, 'S' para Sopro, 'P' para Percussão)
  - `nome` (string)
  - `instrumento` (string)
- `qtdNotas` (int)
- Para cada uma das `qtdNotas`:
  - `tom` (string)
  - `duracao` (int)
  - `filtroMusicos` (string: ex. CSP, CS, P)

## Formato de Saída

### Início da regência:
```text
Maestro inicia a regencia de "" com a banda !
```

### Para cada compasso K (iniciando em 1):
```text
-- Compasso : Nota (t) [Filtro: ] --
```

Seguido da execução de cada músico da banda cujo tipo esteja presente no filtro (na ordem de cadastro):
- **Cordas:** `[Cordas] dedilhou no(a) por tempos.`
- **Sopro:** `[Sopro] soprou no(a) por tempos.`
- **Percussão:** `[Percussao] bateu no(a) mantendo o ritmo de ( tempos).`

### Fim da regência:
```text
Fim da apresentacao de "".
```

## Exemplo de instância de entrada:

```text
OrquestraIFSP VillaLobos TrenzinhoCaipira
3
C Ana Violoncelo
S Beto Flauta
P Caio Triangulo
3
SOL 2 CS
MI 1 CSP
TUM 4 P
```

## Saída correspondente:

```text
Maestro VillaLobos inicia a regencia de "TrenzinhoCaipira" com a banda OrquestraIFSP!
-- Compasso 1: Nota SOL (2t) [Filtro: CS] --
[Cordas] Ana dedilhou SOL no(a) Violoncelo por 2 tempos.
[Sopro] Beto soprou SOL no(a) Flauta por 2 tempos.
-- Compasso 2: Nota MI (1t) [Filtro: CSP] --
[Cordas] Ana dedilhou MI no(a) Violoncelo por 1 tempos.
[Sopro] Beto soprou MI no(a) Flauta por 1 tempos.
[Percussao] Caio bateu no(a) Triangulo mantendo o ritmo de MI (1 tempos).
-- Compasso 3: Nota TUM (4t) [Filtro: P] --
[Percussao] Caio bateu no(a) Triangulo mantendo o ritmo de TUM (4 tempos).
Fim da apresentacao de "TrenzinhoCaipira".
```