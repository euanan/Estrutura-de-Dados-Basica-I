/* deque_dupla.c - TAD Deque em LISTA DUPLA COM SENTINELA (questao 4).
 *
 * sent->prox e o primeiro e sent->ant e o ultimo. Duas funcoes auxiliares
 * (ligar um no antes de outro e desligar um no) bastam para as quatro
 * pontas: a lista e circular, entao inserir no inicio e ligar antes do
 * primeiro, e inserir no fim e ligar antes da propria sentinela.
 * Confira com: make q4 DEQUE=dupla
 *
 * Regras do contrato (deque.h):
 *   - entra e sai pelas duas pontas; as quatro operacoes de pontas e as
 *     duas consultas custam O(1) (amortizado, no vetor);
 *   - remover, deque_primeiro e deque_ultimo devolvem 0 com o deque vazio;
 *   - deque_destruir libera toda a memoria e aceita NULL.
 */

#include <stdlib.h>
#include "deque.h"

typedef struct No No;
struct No {
    Voo item;
    No *ant;
    No *prox;
};

struct Deque {
    No *sent; /* sent->prox e o primeiro; sent->ant, o ultimo */
    int n;
};

/* Liga o no novo imediatamente ANTES do no pos. */
static void ligar(No *pos, No *novo) {
    novo->ant = pos->ant;
    novo->prox = pos;
    pos->ant->prox = novo;
    pos->ant = novo;
}

/* Tira o no da lista (sem liberar). */
static void desligar(No *no) {
    no->ant->prox = no->prox;
    no->prox->ant = no->ant;
}

Deque *deque_criar(void) {
    Deque *d = malloc(sizeof *d);
    if (d == NULL)
        return NULL;
    d->sent = malloc(sizeof(No));
    if (d->sent == NULL) {
        free(d);
        return NULL;
    }
    d->sent->ant = d->sent;
    d->sent->prox = d->sent;
    d->n = 0;
    return d;
}

void deque_destruir(Deque *d) {
    No *p;
    if (d == NULL)
        return;
    p = d->sent->prox;
    while (p != d->sent) {
        No *prox = p->prox;
        free(p);
        p = prox;
    }
    free(d->sent);
    free(d);
}

int deque_tamanho(const Deque *d) {
    return d->n;
}

int deque_vazio(const Deque *d) {
    return d->n == 0;
}

int deque_inserir_inicio(Deque *d, Voo x) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
        return 0;
    novo->item = x;
    ligar(d->sent->prox, novo);
    d->n++;
    return 1;
}

int deque_inserir_fim(Deque *d, Voo x) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
        return 0;
    novo->item = x;
    ligar(d->sent, novo);
    d->n++;
    return 1;
}

int deque_remover_inicio(Deque *d, Voo *x) {
    No *alvo;
    if (d->n == 0)
        return 0;
    alvo = d->sent->prox;
    if (x != NULL)
        *x = alvo->item;
    desligar(alvo);
    free(alvo);
    d->n--;
    return 1;
}

int deque_remover_fim(Deque *d, Voo *x) {
    No *alvo;
    if (d->n == 0)
        return 0;
    alvo = d->sent->ant;
    if (x != NULL)
        *x = alvo->item;
    desligar(alvo);
    free(alvo);
    d->n--;
    return 1;
}

int deque_primeiro(const Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    if (x != NULL)
        *x = d->sent->prox->item;
    return 1;
}

int deque_ultimo(const Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    if (x != NULL)
        *x = d->sent->ant->item;
    return 1;
}
