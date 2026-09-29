#include <stdio.h>
#include "sequencia.h"

int main(void) {
    // O cliente só conhece o contrato e os ponteiros opacos
    Sequencia *s = seq_criar();
    int x, i;
    
    // Cinco inserir_fim 
    for (i = 1; i <= 5; i++) {
        seq_inserir_fim(s, i * 10);
    }
    
    // Um inserir_inicio
    seq_inserir_inicio(s, 5);
    
    // Removendo e testando as pontas
    if (seq_remover_inicio(s, &x)) {
        printf("Removido do inicio: %d\n", x);
    }
    
    if (seq_remover_fim(s, &x)) {
        printf("Removido do fim: %d\n", x);
    }
    
    seq_destruir(s);
    return 0;
}