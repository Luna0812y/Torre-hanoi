#include <stdio.h>
#include <stdlib.h>
#include "torre.h"

int main() {
    int capacidade_torre = 7;
    int total_disco = 12;

    Torres *torre_R = criar_torre(capacidade_torre);
    Torres *torre_G = criar_torre(capacidade_torre);
    Torres *torre_B = criar_torre(capacidade_torre);

    distribuir_itens_aleatorios(torre_R, torre_G, torre_B, total_disco);

    int jogadas = 0;
    int opcao;
    char origem, destino;

    imprimir_estado(torre_R, torre_G, torre_B);

    while (1) {
        printf("Digite a origem e destino (R, G, B): ");
        scanf(" %c %c", &origem, &destino);

        if ((origem == 'R' || origem == 'G' || origem == 'B') &&
            (destino == 'R' || destino == 'G' || destino == 'B') &&
            origem != destino) {

            if (mover_item(origem, destino, torre_R, torre_G, torre_B)) {
                jogadas++;
                imprimir_estado(torre_R, torre_G, torre_B);
                
                if (verificar_vitoria(torre_R, torre_G, torre_B)) {
                    printf("Parabens, voce ganhou em %d jogadas.\n", jogadas);
                    return 0;
                }
            } else {
                printf("Movimento invalido.\n");
            }
        } else {
            printf("Opcoes invalidas. Tente novamente.\n");
        }
    }

    encerrar(torre_R);
    encerrar(torre_G);
    encerrar(torre_B);

    return 0;
}