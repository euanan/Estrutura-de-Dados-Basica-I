/* lista_simples.c - TAD Lista em LISTA SIMPLESMENTE ENCADEADA (questao 1).
 *
 * No-cabeca (um no sem item antes do primeiro) e ponteiro para o ultimo
 * no: inserir no fim usa a cauda e nao percorre a lista, e remover o
 * ultimo atualiza a cauda.
 * Confira com: make q1 LISTA=simples
 *
 * Regras do contrato (lista.h):
 *   - indices de 0 a n - 1; lista_inserir aceita i de 0 a n;
 *   - funcoes que podem falhar devolvem 1 (sucesso) ou 0 (falha);
 *   - lista_buscar compara o codigo com strcmp e devolve o indice, ou -1;
 *   - lista_destruir libera toda a memoria e aceita NULL.
 */

#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef struct No No;
struct No {
    Voo item;
    No *prox;
};

struct Lista {
    No *cab;   /* no-cabeca, sem item */
    No *cauda; /* o ultimo no (cab se vazia) */
    int n;
};

Lista *lista_criar(void) {
    Lista *l = malloc(sizeof *l);
    if (l == NULL)
        return NULL;
    l->cab = malloc(sizeof(No));
    if (l->cab == NULL) {
        free(l);
        return NULL;
    }
    l->cab->prox = NULL;
    l->cauda = l->cab;
    l->n = 0;
    return l;
}

void lista_destruir(Lista *l) {
    No *p;
    if (l == NULL)
        return;
    p = l->cab;
    while (p != NULL) {
        No *prox = p->prox;
        free(p);
        p = prox;
    }
    free(l);
}

int lista_tamanho(const Lista *l) {
    return l->n;
}

int lista_vazia(const Lista *l) {
    return l->n == 0;
}

int lista_obter(const Lista *l, int i, Voo *x) {
    No *p;
    if (i < 0 || i >= l->n)
        return 0;
    p = l->cab->prox;
    for (int k = 0; k < i; k++)
        p = p->prox;
    if (x != NULL)
        *x = p->item;
    return 1;
}

/* Acha o no ANTERIOR a posicao i (a cabeca, se i == 0); no fim, usa a
 * cauda em vez de percorrer. */
int lista_inserir(Lista *l, int i, Voo x) {
    No *ant, *novo;
    if (i < 0 || i > l->n)
        return 0;
    novo = malloc(sizeof(No));
    if (novo == NULL)
        return 0;
    novo->item = x;
    if (i == l->n) {
        ant = l->cauda;
    } else {
        ant = l->cab;
        for (int k = 0; k < i; k++)
            ant = ant->prox;
    }
    novo->prox = ant->prox;
    ant->prox = novo;
    if (ant == l->cauda)
        l->cauda = novo;
    l->n++;
    return 1;
}

int lista_remover(Lista *l, int i, Voo *x) {
    No *ant, *alvo;
    if (i < 0 || i >= l->n)
        return 0;
    ant = l->cab;
    for (int k = 0; k < i; k++)
        ant = ant->prox;
    alvo = ant->prox;
    if (x != NULL)
        *x = alvo->item;
    ant->prox = alvo->prox;
    if (alvo == l->cauda)
        l->cauda = ant;
    free(alvo);
    l->n--;
    return 1;
}

int lista_buscar(const Lista *l, const char *codigo) {
    int i = 0;
    for (No *p = l->cab->prox; p != NULL; p = p->prox, i++)
        if (strcmp(p->item.codigo, codigo) == 0)
            return i;
    return -1;
}
