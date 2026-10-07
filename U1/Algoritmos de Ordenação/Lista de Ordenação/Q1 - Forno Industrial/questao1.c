#include <stdio.h>
#include <stdbool.h>

void insertion_sort(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;

        // Desloca os elementos maiores que a chave para a direita
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

// Função auxiliar para imprimir o vetor
void imprimir_vetor(const int v[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", v[i], (i < n - 1) ? ", " : "");
    }
    printf("]\n");
}

// Função de verificação por código
bool esta_ordenado(const int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int temperaturas[] = {150, 162, 175, 168, 190, 201, 195};
    int n = sizeof(temperaturas) / sizeof(temperaturas[0]);

    printf("QUESTÃO 1: INSERTION SORT\n");
    printf("Vetor original: ");
    imprimir_vetor(temperaturas, n);

    insertion_sort(temperaturas, n);

    printf("Vetor ordenado: ");
    imprimir_vetor(temperaturas, n);

    if (esta_ordenado(temperaturas, n)) {
        printf("Conferência por código: SUCESSO (Vetor em ordem crescente)\n");
    } else {
        printf("Conferência por código: FALHA (Vetor NÃO está ordenado)\n");
    }

    return 0;
}