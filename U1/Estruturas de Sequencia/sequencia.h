#ifndef SEQUENCIA_H
#define SEQUENCIA_H

// Declara o tipo sem dizer o que existe dentro: o tipo opaco
typedef struct Sequencia Sequencia;

Sequencia *seq_criar(void);
void seq_destruir(Sequencia *s);

// Operações nas pontas
int seq_inserir_inicio(Sequencia *s, int x);
int seq_inserir_fim(Sequencia *s, int x);
int seq_remover_inicio(Sequencia *s, int *x);
int seq_remover_fim(Sequencia *s, int *x);

#endif