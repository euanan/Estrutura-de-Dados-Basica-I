/* fila_circular.c - TAD Fila em VETOR CIRCULAR (questao 2).
 *
 *   - itens: o bloco; ini: a celula da frente; n: quantos estao na fila;
 *   - o fim fica em (ini + n) % cap, e ninguem se move ao desenfileirar;
 *   - comeca com cap = 4 e DOBRA quando lota, copiando os itens para o
 *     bloco novo na ordem da fila (da frente para o fim).
 * Confira com: make q2 FILA=circular
 *
 * Regras do contrato (fila.h):
 *   - fila_enfileirar poe no fim; fila_desenfileirar tira da frente;
 *   - fila_desenfileirar e fila_frente devolvem 0 com a fila vazia;
 *   - fila_destruir libera toda a memoria e aceita NULL.
 */

#include <stdlib.h>
#include "fila.h"

#define CAP_INICIAL 4

struct Fila {
    Voo *itens;
    int ini; /* a celula da frente */
    int n;   /* quantos estao na fila */
    int cap; /* tamanho do bloco */
};

Fila *fila_criar(void) {
    Fila *f = malloc(sizeof *f);
    if (f == NULL)
        return NULL;
    f->itens = malloc(CAP_INICIAL * sizeof(Voo));
    if (f->itens == NULL) {
        free(f);
        return NULL;
    }
    f->ini = 0;
    f->n = 0;
    f->cap = CAP_INICIAL;
    return f;
}

void fila_destruir(Fila *f) {
    if (f == NULL)
        return;
    free(f->itens);
    free(f);
}

int fila_tamanho(const Fila *f) {
    return f->n;
}

int fila_vazia(const Fila *f) {
    return f->n == 0;
}

/* Dobra o bloco: os itens vao para o bloco novo na ORDEM DA FILA (da
 * frente para o fim), nao na ordem das celulas, e a frente volta a 0. */
static int dobrar(Fila *f) {
    Voo *novo = malloc(2 * (size_t)f->cap * sizeof(Voo));
    if (novo == NULL)
        return 0;
    for (int k = 0; k < f->n; k++)
        novo[k] = f->itens[(f->ini + k) % f->cap];
    free(f->itens);
    f->itens = novo;
    f->ini = 0;
    f->cap *= 2;
    return 1;
}

int fila_enfileirar(Fila *f, Voo x) {
    if (f->n == f->cap && !dobrar(f))
        return 0;
    f->itens[(f->ini + f->n) % f->cap] = x;
    f->n++;
    return 1;
}

int fila_desenfileirar(Fila *f, Voo *x) {
    if (f->n == 0)
        return 0;
    if (x != NULL)
        *x = f->itens[f->ini];
    f->ini = (f->ini + 1) % f->cap;
    f->n--;
    return 1;
}

int fila_frente(const Fila *f, Voo *x) {
    if (f->n == 0)
        return 0;
    if (x != NULL)
        *x = f->itens[f->ini];
    return 1;
}
