/* lista_dupla.c - TAD Lista em LISTA DUPLAMENTE ENCADEADA (questao 1).
 *
 * Lista dupla circular com sentinela (um no sem item antes do primeiro e
 * depois do ultimo): para chegar a posicao i, anda pelo lado mais perto
 * (no maximo n/2 passos).
 * Confira com: make q1 LISTA=dupla
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
    No *ant;
    No *prox;
};

struct Lista {
    No *sent; /* sentinela: vazia, aponta para si mesmo */
    int n;
};

/* O no da posicao i (0 <= i <= n); a posicao n e a propria sentinela.
 * Anda pelo lado mais perto: do inicio ate a metade, do fim depois dela. */
static No *no_em(const Lista *l, int i) {
    No *p;
    if (i == l->n)
        return l->sent;
    if (i <= l->n / 2) {
        p = l->sent->prox;
        for (int k = 0; k < i; k++)
            p = p->prox;
    } else {
        p = l->sent->ant;
        for (int k = l->n - 1; k > i; k--)
            p = p->ant;
    }
    return p;
}

Lista *lista_criar(void) {
    Lista *l = malloc(sizeof *l);
    if (l == NULL)
        return NULL;
    l->sent = malloc(sizeof(No));
    if (l->sent == NULL) {
        free(l);
        return NULL;
    }
    l->sent->ant = l->sent;
    l->sent->prox = l->sent;
    l->n = 0;
    return l;
}

void lista_destruir(Lista *l) {
    No *p;
    if (l == NULL)
        return;
    p = l->sent->prox;
    while (p != l->sent) {
        No *prox = p->prox;
        free(p);
        p = prox;
    }
    free(l->sent);
    free(l);
}

int lista_tamanho(const Lista *l) {
    return l->n;
}

int lista_vazia(const Lista *l) {
    return l->n == 0;
}

int lista_obter(const Lista *l, int i, Voo *x) {
    if (i < 0 || i >= l->n)
        return 0;
    if (x != NULL)
        *x = no_em(l, i)->item;
    return 1;
}

/* O novo no entra ANTES do no que esta na posicao i (a sentinela, se
 * i == n, o que o poe no fim). */
int lista_inserir(Lista *l, int i, Voo x) {
    No *depois, *novo;
    if (i < 0 || i > l->n)
        return 0;
    novo = malloc(sizeof(No));
    if (novo == NULL)
        return 0;
    novo->item = x;
    depois = no_em(l, i);
    novo->ant = depois->ant;
    novo->prox = depois;
    depois->ant->prox = novo;
    depois->ant = novo;
    l->n++;
    return 1;
}

int lista_remover(Lista *l, int i, Voo *x) {
    No *alvo;
    if (i < 0 || i >= l->n)
        return 0;
    alvo = no_em(l, i);
    if (x != NULL)
        *x = alvo->item;
    alvo->ant->prox = alvo->prox;
    alvo->prox->ant = alvo->ant;
    free(alvo);
    l->n--;
    return 1;
}

int lista_buscar(const Lista *l, const char *codigo) {
    int i = 0;
    for (No *p = l->sent->prox; p != l->sent; p = p->prox, i++)
        if (strcmp(p->item.codigo, codigo) == 0)
            return i;
    return -1;
}
