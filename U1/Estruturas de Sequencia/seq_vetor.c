#include <stdlib.h>
#include "sequencia.h"

// Três campos: o bloco, quantos itens estão em uso e quantos cabem
struct Sequencia {
    int *itens; // bloco na heap
    int  n; // itens em uso
    int  cap; // itens que cabem
};

// Função auxiliar interna para garantir espaço (dobrar quando lota)
static int reservar(Sequencia *s) {
    if (s->n == s->cap) {
        int nova_cap = s->cap * 2;
        int *novo_bloco = (int *)realloc(s->itens, nova_cap * sizeof(int));
        if (novo_bloco == NULL) {
            return 0; // Falha na alocação
        }
        s->itens = novo_bloco;
        s->cap = nova_cap;
    }
    return 1;
}

Sequencia *seq_criar(void) {
    Sequencia *s = (Sequencia *)malloc(sizeof(Sequencia));
    if (s != NULL) {
        s->cap = 8; // O bloco nasce com 8 posições
        s->n = 0;
        s->itens = (int *)malloc(s->cap * sizeof(int));
        if (s->itens == NULL) {
            free(s);
            return NULL;
        }
    }
    return s;
}

void seq_destruir(Sequencia *s) {
    if (s != NULL) {
        free(s->itens);
        free(s);
    }
}

// Inserir no fim: O(1) amortizado 
int seq_inserir_fim(Sequencia *s, int x) {
    if (!reservar(s)) {
        return 0;
    }
    s->itens[s->n] = x;   /* uma escrita */
    s->n++;
    return 1;
}

// Inserir no início: Abre espaço movendo todos os itens
int seq_inserir_inicio(Sequencia *s, int x) {
    if (!reservar(s)) {
        return 0;
    }
    // Todos os que sobram andam uma casa
    for (int j = s->n; j > 0; j--) {
        s->itens[j] = s->itens[j - 1];
    }
    s->itens[0] = x;
    s->n++;
    return 1;
}

// Remover do fim: O(1)
int seq_remover_fim(Sequencia *s, int *x) {
    if (s == NULL || s->n == 0) return 0;
    
    s->n--;
    *x = s->itens[s->n];
    return 1;
}

// Remover do início: Movimenta todos os itens para preencher o vazio
int seq_remover_inicio(Sequencia *s, int *x) {
    if (s == NULL || s->n == 0) return 0;
    
    *x = s->itens[0];
    
    // Move os elementos para trás, fechando o buraco no índice 0
    for (int j = 0; j < s->n - 1; j++) {
        s->itens[j] = s->itens[j + 1];
    }
    s->n--;
    return 1;
}