/* deque_circular.c - TAD Deque em VETOR CIRCULAR (questao 4).
 *
 * ini e a celula do primeiro e anda para os dois lados; o ultimo fica em
 * (ini + n - 1) % cap. Inserir no inicio recua ini somando cap antes do
 * resto da divisao. Comeca com cap = 4 e DOBRA quando lota.
 * Confira com: make q4 DEQUE=circular
 *
 * Regras do contrato (deque.h):
 *   - entra e sai pelas duas pontas; as quatro operacoes de pontas e as
 *     duas consultas custam O(1) (amortizado, no vetor);
 *   - remover, deque_primeiro e deque_ultimo devolvem 0 com o deque vazio;
 *   - deque_destruir libera toda a memoria e aceita NULL.
 */

#include <stdlib.h>
#include "deque.h"

#define CAP_INICIAL 4

struct Deque {
    Voo *itens;
    int ini; /* a celula do primeiro */
    int n;   /* quantos ha */
    int cap;
};

Deque *deque_criar(void) {
    Deque *d = malloc(sizeof *d);
    if (d == NULL)
        return NULL;
    d->itens = malloc(CAP_INICIAL * sizeof(Voo));
    if (d->itens == NULL) {
        free(d);
        return NULL;
    }
    d->ini = 0;
    d->n = 0;
    d->cap = CAP_INICIAL;
    return d;
}

void deque_destruir(Deque *d) {
    if (d == NULL)
        return;
    free(d->itens);
    free(d);
}

int deque_tamanho(const Deque *d) {
    return d->n;
}

int deque_vazio(const Deque *d) {
    return d->n == 0;
}

/* Dobra o bloco: os itens vao para o bloco novo na ORDEM DO DEQUE (do
 * primeiro para o ultimo), nao na ordem das celulas, e ini volta a 0.
 * Sem isso, depois de inserir no inicio o vetor estaria "emendado" no
 * meio e a copia simples quebraria a ordem. */
static int dobrar(Deque *d) {
    Voo *novo = malloc(2 * (size_t)d->cap * sizeof(Voo));
    if (novo == NULL)
        return 0;
    for (int k = 0; k < d->n; k++)
        novo[k] = d->itens[(d->ini + k) % d->cap];
    free(d->itens);
    d->itens = novo;
    d->ini = 0;
    d->cap *= 2;
    return 1;
}

int deque_inserir_inicio(Deque *d, Voo x) {
    if (d->n == d->cap && !dobrar(d))
        return 0;
    d->ini = (d->ini - 1 + d->cap) % d->cap; /* soma cap antes do resto */
    d->itens[d->ini] = x;
    d->n++;
    return 1;
}

int deque_inserir_fim(Deque *d, Voo x) {
    if (d->n == d->cap && !dobrar(d))
        return 0;
    d->itens[(d->ini + d->n) % d->cap] = x;
    d->n++;
    return 1;
}

int deque_remover_inicio(Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    if (x != NULL)
        *x = d->itens[d->ini];
    d->ini = (d->ini + 1) % d->cap;
    d->n--;
    return 1;
}

int deque_remover_fim(Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    if (x != NULL)
        *x = d->itens[(d->ini + d->n - 1) % d->cap];
    d->n--;
    return 1;
}

int deque_primeiro(const Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    if (x != NULL)
        *x = d->itens[d->ini];
    return 1;
}

int deque_ultimo(const Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    if (x != NULL)
        *x = d->itens[(d->ini + d->n - 1) % d->cap];
    return 1;
}
