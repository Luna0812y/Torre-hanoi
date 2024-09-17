#include <stdio.h>

int main() {
    int n, i;

    // Tamanho da torre (coluna)
    printf("Digite o número de linhas: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        // Imprime um asterisco por linha
        printf("*\n");
    }

    return 0;
}
