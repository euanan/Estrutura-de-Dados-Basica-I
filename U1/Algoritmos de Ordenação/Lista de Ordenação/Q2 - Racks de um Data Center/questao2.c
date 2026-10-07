#include <stdio.h>
#include <stdbool.h>

void selection_sort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        // Busca o menor elemento no restante do vetor
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        // Troca o elemento da fronteira com o menor encontrado
        if (min != i) {
            int aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
}

void imprimir_vetor(const int v[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", v[i], (i < n - 1) ? ", " : "");
    }
    printf("]\n");
}

bool esta_ordenado(const int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int consumos[] = {310, 185, 275, 140, 220, 165, 245};
    int n = sizeof(consumos) / sizeof(consumos[0]);

    printf("QUESTÃO 2: SELECTION SORT\n");
    printf("Vetor original: ");
    imprimir_vetor(consumos, n);

    selection_sort(consumos, n);

    printf("Vetor ordenado: ");
    imprimir_vetor(consumos, n);

    if (esta_ordenado(consumos, n)) {
        printf("Conferência por código: SUCESSO (Vetor em ordem crescente)\n");
    } else {
        printf("Conferência por código: FALHA (Vetor NÃO está ordenado)\n");
    }

    return 0;
}