/* pilha_vetor.c - TAD Pilha em VETOR (questao 3).
 *
 * A base e itens[0] e o topo e itens[n - 1]; comeca com cap = 8 e DOBRA
 * (realloc) quando lota.
 * Confira com: make q3 PILHA=vetor
 *
 * Regras do contrato (pilha.h):
 *   - pilha_empilhar poe no topo; pilha_desempilhar tira do topo;
 *   - pilha_desempilhar e pilha_topo devolvem 0 com a pilha vazia;
 *   - pilha_destruir libera toda a memoria e aceita NULL.
 */

#include <stdlib.h>
#include "pilha.h"

#define CAP_INICIAL 8

struct Pilha {
    Voo *itens; /* a base e itens[0] */
    int n;      /* o topo e itens[n - 1] */
    int cap;
};

Pilha *pilha_criar(void) {
    Pilha *p = malloc(sizeof *p);
    if (p == NULL)
        return NULL;
    p->itens = malloc(CAP_INICIAL * sizeof(Voo));
    if (p->itens == NULL) {
        free(p);
        return NULL;
    }
    p->n = 0;
    p->cap = CAP_INICIAL;
    return p;
}

void pilha_destruir(Pilha *p) {
    if (p == NULL)
        return;
    free(p->itens);
    free(p);
}

int pilha_tamanho(const Pilha *p) {
    return p->n;
}

int pilha_vazia(const Pilha *p) {
    return p->n == 0;
}

int pilha_empilhar(Pilha *p, Voo x) {
    if (p->n == p->cap) {
        Voo *novo = realloc(p->itens, 2 * (size_t)p->cap * sizeof(Voo));
        if (novo == NULL)
            return 0;
        p->itens = novo;
        p->cap *= 2;
    }
    p->itens[p->n++] = x;
    return 1;
}

int pilha_desempilhar(Pilha *p, Voo *x) {
    if (p->n == 0)
        return 0;
    p->n--;
    if (x != NULL)
        *x = p->itens[p->n];
    return 1;
}

int pilha_topo(const Pilha *p, Voo *x) {
    if (p->n == 0)
        return 0;
    if (x != NULL)
        *x = p->itens[p->n - 1];
    return 1;
}
