#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        
        for (int j = 0; j < n - 1 - i; j++) {
            // Só troca se estritamente maior para garantir estabilidade
            if (v[j] > v[j + 1]) {
                int aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
                trocou = true;
            }
        }
        
        // Se nenhuma troca ocorreu na passagem, o vetor já está ordenado
        if (!trocou) {
            break;
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
    // Teste 1: Vetor desordenado
    int v1[] = {34, 12, 45, 8, 27, 19, 41};
    int n1 = sizeof(v1) / sizeof(v1[0]);

    // Teste 2: Vetor já ordenado (para testar a otimização da flag)
    int v2[] = {5, 10, 15, 20, 25};
    int n2 = sizeof(v2) / sizeof(v2[0]);

    printf("QUESTÃO 3: BUBBLE SORT\n");
    
    printf("\n[Caso 1: Vetor Desordenado]\n");
    printf("Antes:  ");
    imprimir_vetor(v1, n1);
    bubble_sort(v1, n1);
    printf("Depois: ");
    imprimir_vetor(v1, n1);
    printf("Conferência: %s\n", esta_ordenado(v1, n1) ? "SUCESSO" : "FALHA");

    printf("\n[Caso 2: Vetor Já Ordenado]\n");
    printf("Antes:  ");
    imprimir_vetor(v2, n2);
    bubble_sort(v2, n2);
    printf("Depois: ");
    imprimir_vetor(v2, n2);
    printf("Conferência: %s\n", esta_ordenado(v2, n2) ? "SUCESSO" : "FALHA");

    return 0;
}