/* fila_encadeada.c - TAD Fila em LISTA ENCADEADA (questao 2).
 *
 * Um ponteiro para o inicio (sai daqui) e outro para o fim (entra depois
 * dele), para que enfileirar e desenfileirar custem O(1). Quando a fila
 * fica vazia, o fim tambem volta a NULL.
 * Confira com: make q2 FILA=encadeada
 *
 * Regras do contrato (fila.h):
 *   - fila_enfileirar poe no fim; fila_desenfileirar tira da frente;
 *   - fila_desenfileirar e fila_frente devolvem 0 com a fila vazia;
 *   - fila_destruir libera toda a memoria e aceita NULL.
 */

#include <stdlib.h>
#include "fila.h"

typedef struct No No;
struct No {
    Voo item;
    No *prox;
};

struct Fila {
    No *inicio; /* a frente: sai daqui */
    No *fim;    /* o ultimo: entra depois dele */
    int n;
};

Fila *fila_criar(void) {
    Fila *f = malloc(sizeof *f);
    if (f == NULL)
        return NULL;
    f->inicio = NULL;
    f->fim = NULL;
    f->n = 0;
    return f;
}

void fila_destruir(Fila *f) {
    No *p;
    if (f == NULL)
        return;
    p = f->inicio;
    while (p != NULL) {
        No *prox = p->prox;
        free(p);
        p = prox;
    }
    free(f);
}

int fila_tamanho(const Fila *f) {
    return f->n;
}

int fila_vazia(const Fila *f) {
    return f->n == 0;
}

int fila_enfileirar(Fila *f, Voo x) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
        return 0;
    novo->item = x;
    novo->prox = NULL;
    if (f->fim == NULL)
        f->inicio = novo; /* fila vazia: o novo e tambem a frente */
    else
        f->fim->prox = novo;
    f->fim = novo;
    f->n++;
    return 1;
}

int fila_desenfileirar(Fila *f, Voo *x) {
    No *alvo;
    if (f->inicio == NULL)
        return 0;
    alvo = f->inicio;
    if (x != NULL)
        *x = alvo->item;
    f->inicio = alvo->prox;
    if (f->inicio == NULL)
        f->fim = NULL; /* esvaziou: o fim tambem volta a NULL */
    free(alvo);
    f->n--;
    return 1;
}

int fila_frente(const Fila *f, Voo *x) {
    if (f->inicio == NULL)
        return 0;
    if (x != NULL)
        *x = f->inicio->item;
    return 1;
}
