/* lista_vetor.c - TAD Lista em VETOR (questao 1).
 *
 * Voos guardados num vetor alocado com malloc: comeca com cap = 8 e DOBRA
 * (realloc) quando lota; inserir e remover deslocam os vizinhos.
 * Confira com: make q1 LISTA=vetor
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

#define CAP_INICIAL 8

struct Lista {
    Voo *itens; /* bloco contiguo */
    int n;      /* itens em uso */
    int cap;    /* posicoes reservadas */
};

Lista *lista_criar(void) {
    Lista *l = malloc(sizeof *l);
    if (l == NULL)
        return NULL;
    l->itens = malloc(CAP_INICIAL * sizeof(Voo));
    if (l->itens == NULL) {
        free(l);
        return NULL;
    }
    l->n = 0;
    l->cap = CAP_INICIAL;
    return l;
}

void lista_destruir(Lista *l) {
    if (l == NULL)
        return;
    free(l->itens);
    free(l);
}

int lista_tamanho(const Lista *l) {
    return l->n;
}

int lista_vazia(const Lista *l) {
    return l->n == 0;
}

/* O(1): acesso direto pelo indice. */
int lista_obter(const Lista *l, int i, Voo *x) {
    if (i < 0 || i >= l->n)
        return 0;
    if (x != NULL)
        *x = l->itens[i];
    return 1;
}

/* Dobra o bloco quando lota; depois abre espaco deslocando para a direita. */
int lista_inserir(Lista *l, int i, Voo x) {
    if (i < 0 || i > l->n)
        return 0;
    if (l->n == l->cap) {
        Voo *novo = realloc(l->itens, 2 * (size_t)l->cap * sizeof(Voo));
        if (novo == NULL)
            return 0;
        l->itens = novo;
        l->cap *= 2;
    }
    for (int j = l->n; j > i; j--)
        l->itens[j] = l->itens[j - 1];
    l->itens[i] = x;
    l->n++;
    return 1;
}

/* Fecha o buraco deslocando para a esquerda. */
int lista_remover(Lista *l, int i, Voo *x) {
    if (i < 0 || i >= l->n)
        return 0;
    if (x != NULL)
        *x = l->itens[i];
    for (int j = i; j < l->n - 1; j++)
        l->itens[j] = l->itens[j + 1];
    l->n--;
    return 1;
}

int lista_buscar(const Lista *l, const char *codigo) {
    for (int i = 0; i < l->n; i++)
        if (strcmp(l->itens[i].codigo, codigo) == 0)
            return i;
    return -1;
}
