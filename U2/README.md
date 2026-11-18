# U2 · A torre de controle: lista, fila, pilha e deque

IMD0029 · Estrutura de Dados Básicas I · Turma 2 · 2026.2 · UFRN

Resolução da Lista da Unidade 2. Cada questão implementa um TAD em todas as
representações vistas em aula, para a torre de controle do aeroporto de São
Gonçalo do Amarante.

## Organização

| Pasta | Questão | TAD | Arquivos |
| --- | --- | --- | --- |
| `q1_lista/` | 1 · grade de partidas | Lista | `lista_vetor.c`, `lista_simples.c`, `lista_dupla.c` |
| `q2_fila/` | 2 · cabeceira da pista | Fila | `fila_circular.c`, `fila_encadeada.c` |
| `q3_pilha/` | 3 · hangar de manutenção | Pilha | `pilha_vetor.c`, `pilha_encadeada.c` |
| `q4_deque/` | 4 · espera para pouso | Deque | `deque_circular.c`, `deque_dupla.c` |

Os nomes dos arquivos são os mesmos dos esqueletos do professor, porque o
`Makefile` procura exatamente por eles.

## Representações

- **Lista:** vetor (capacidade 8, dobra ao lotar), lista simples com nó-cabeça
  e ponteiro para o último nó, e lista dupla circular com sentinela.
- **Fila:** vetor circular (capacidade 4, dobra ao lotar) e lista encadeada com
  ponteiros para o início e o fim.
- **Pilha:** vetor (capacidade 8, dobra ao lotar) e lista encadeada com o topo
  no primeiro nó.
- **Deque:** vetor circular (capacidade 4, dobra ao lotar) e lista dupla
  circular com sentinela.

## Este repositório não roda sozinho

Aqui estão só os nove arquivos dos TADs. Os contratos (`voo.h`, `lista.h`,
`fila.h`, `pilha.h`, `deque.h`), a torre (`main.c`, `torre.c`, `grade.c`,
`pista.c`, `hangar.c`, `aproximacao.c`), o `Makefile`, as entradas e as saídas
esperadas são material do professor e ficam na casca:
<https://github.com/varellalexandre/tads_sequencia>.

## Como conferir

1. Baixe a casca (pasta `casca_u2`).
2. Copie os nove `.c` destas pastas para a pasta da casca, ao lado do
   `Makefile`, substituindo os esqueletos.
3. Rode:

```
make q1 LISTA=vetor      # também simples e dupla
make q2 FILA=circular    # também encadeada
make q3 PILHA=vetor      # também encadeada
make q4 DEQUE=circular   # também dupla
make todas               # as nove combinações de uma vez
make todas SAN=1         # as nove combinações com o sanitizer
```

Cada questão está resolvida quando imprime `OK` em todas as representações.

As questões dependem umas das outras: a questão 2 e a questão 3 precisam da
lista (questão 1), e a questão 4 usa os quatro TADs.
