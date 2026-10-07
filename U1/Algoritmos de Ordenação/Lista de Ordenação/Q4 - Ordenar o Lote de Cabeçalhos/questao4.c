#include <stdio.h>
#include <stdbool.h>

// Função de intercalação interna (auxiliar)
static void intercalar(int v[], int ini, int meio, int fim, int aux[]) {
    int i = ini;
    int j = meio + 1;
    int k = ini;

    while (i <= meio && j <= fim) {
        // O operador <= garante a estabilidade: em caso de empate,
        // o elemento da metade esquerda sai primeiro.
        if (v[i] <= v[j]) {
            aux[k++] = v[i++];
        } else {
            aux[k++] = v[j++];
        }
    }

    // Copia os elementos restantes da metade esquerda, se houver
    while (i <= meio) {
        aux[k++] = v[i++];
    }

    // Copia os elementos restantes da metade direita, se houver
    while (j <= fim) {
        aux[k++] = v[j++];
    }

    // Copia de volta do vetor auxiliar para o vetor original
    for (i = ini; i <= fim; i++) {
        v[i] = aux[i];
    }
}

void merge_sort(int v[], int ini, int fim, int aux[]) {
    if (ini >= fim) {
        return; // Caso base
    }

    int meio = (ini + fim) / 2;

    merge_sort(v, ini, meio, aux);
    merge_sort(v, meio + 1, fim, aux);
    intercalar(v, ini, meio, fim, aux);
}

void imprimir_vetor(const int v[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", v[i], (i < n - 1) ? ", " : "");
    }
    printf("]\n");
}

bool esta_ordenado(const int v[], int ini, int fim) {
    for (int i = ini; i < fim; i++) {
        if (v[i] > v[i + 1]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    // Teste 1: Ordenação completa
    int cabecalhos[] = {230, 45, 178, 92, 310, 15, 267, 134};
    int n1 = sizeof(cabecalhos) / sizeof(cabecalhos[0]);
    int aux1[8];

    printf("QUESTÃO 4: MERGE SORT\n");
    printf("\n[Teste 1: Ordenação do lote completo (0 a 7)]\n");
    printf("Antes:  ");
    imprimir_vetor(cabecalhos, n1);

    merge_sort(cabecalhos, 0, n1 - 1, aux1);

    printf("Depois: ");
    imprimir_vetor(cabecalhos, n1);
    printf("Conferência: %s\n", esta_ordenado(cabecalhos, 0, n1 - 1) ? "SUCESSO" : "FALHA");

    // Teste 2: Ordenação parcial (apenas um trecho no meio do vetor)
    int v_parcial[] = {999, 50, 20, 40, 10, 888};
    int n2 = sizeof(v_parcial) / sizeof(v_parcial[0]);
    int aux2[6];

    printf("\n[Teste 2: Ordenação apenas do trecho central (índices 1 a 4)]\n");
    printf("Antes:  ");
    imprimir_vetor(v_parcial, n2);

    merge_sort(v_parcial, 1, 4, aux2);

    printf("Depois: ");
    imprimir_vetor(v_parcial, n2);

    // Verifica se fora do intervalo [1, 4] os elementos continuam intactos
    if (v_parcial[0] == 999 && v_parcial[5] == 888 && esta_ordenado(v_parcial, 1, 4)) {
        printf("Conferência: SUCESSO (Trecho [1..4] ordenado e elementos externos intocados)\n");
    } else {
        printf("Conferência: FALHA\n");
    }

    return 0;
}