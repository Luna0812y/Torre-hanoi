#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "torre.h"

Torres* criar_torre(int capacidade){
    Torres *torre = (Torres *)malloc(sizeof(Torres));
    torre->ponto = (char *)malloc(capacidade * sizeof(char));
    torre->topo = - 1;
    torre->capacidade = capacidade;
    return torre;
}

int torre_vazia(Torres *torre){
    return torre->topo == - 1;
}

int torre_cheia(Torres *torre){
    return torre->topo == torre->capacidade - 1;
}

void empilhar(Torres *torre, char valor) {
    if (torre_cheia(torre)) {
        printf("Erro: Torre cheia!\n");
        return;
    }

    torre->ponto[++torre->topo] = valor;
}

char desempilhar(Torres *torre) {
    if (torre_vazia(torre)) {
        printf("Erro: Torre vazia!\n");
        return 0; 
    }
    return torre->ponto[torre->topo--]; 
}

void encerrar(Torres *torre){
    free(torre->ponto);
    free(torre);
}

int mover_item(char origem, char destino, Torres *torreR, Torres *torreG, Torres *torreB) {
    Torres *torreOrigem = NULL;
    Torres *torreDestino = NULL;
    
    switch (origem) {
        case 'R': torreOrigem = torreR; break;
        case 'G': torreOrigem = torreG; break;
        case 'B': torreOrigem = torreB; break;
        default: printf("Origem inválida\n"); return 0;
    }
    
    switch (destino) {
        case 'R': torreDestino = torreR; break;
        case 'G': torreDestino = torreG; break;
        case 'B': torreDestino = torreB; break;
        default: printf("Destino inválido\n"); return 0;
    }
    
    if (torre_vazia(torreOrigem)) {
        printf("Erro: Torre de origem vazia!\n");
        return 0;
    }
    
    char item = desempilhar(torreOrigem);
    
    if (torre_cheia(torreDestino)) {
        printf("Erro: Torre de destino cheia!\n");
        empilhar(torreOrigem, item);
        return 0;
    }
    
    empilhar(torreDestino, item);
    
    return 1;
}


int verificar_vitoria(Torres *torreR, Torres *torreG, Torres *torreB) {
    if (torre_contem_unico_tipo(torreR, 'R') && torre_contem_unico_tipo(torreG, 'G') && torre_contem_unico_tipo(torreB, 'B')) {
        return 0;
    }

    int vitoriaR = torre_vazia(torreG) && torre_vazia(torreB) && torre_contem_unico_tipo(torreR, 'R');
    int vitoriaG = torre_vazia(torreR) && torre_vazia(torreB) && torre_contem_unico_tipo(torreG, 'G');
    int vitoriaB = torre_vazia(torreR) && torre_vazia(torreG) && torre_contem_unico_tipo(torreB, 'B');

    return vitoriaR || vitoriaG || vitoriaB;
}

int torre_contem_unico_tipo(Torres *torre, char tipo) {
    for (int i = 0; i <= torre->topo; i++) {
        if (torre->ponto[i] != tipo) {
            return 0;
        }
    }
    return 1;
}


void distribuir_itens_aleatorios(Torres *torreR, Torres *torreG, Torres *torreB, int total) {
    char itens[] = {'R', 'G', 'B'};
    int num_itens = sizeof(itens) / sizeof(itens[0]);

    for (int i = 0; i < total; i++) {
        int tipo = rand() % num_itens;
        char item = itens[tipo];
        
        Torres *torreAleatoria = NULL;
        int torreEscolhida = rand() % 3;

        switch (torreEscolhida) {
            case 0: torreAleatoria = torreR; break;
            case 1: torreAleatoria = torreG; break;
            case 2: torreAleatoria = torreB; break;
        }

        if (!torre_cheia(torreAleatoria)) {
            empilhar(torreAleatoria, item);
        } else {
            i--; 
        }
    }
}


void imprimir_torres(Torres *torre1, char cor1, Torres *torre2, char cor2, Torres *torre3, char cor3) {

    int max_linhas = (torre1->topo + 1 > torre2->topo + 1) ? torre1->topo + 1 : torre2->topo + 1;
    max_linhas = (max_linhas > torre3->topo + 1) ? max_linhas : torre3->topo + 1;

    for (int i = 0; i < max_linhas; i++) {
        // Torre 1
        if (i <= torre1->topo) {
            printf("%c         ", torre1->ponto[i]);
        } else {
            printf("         ");  
        }

        // Torre 2
        if (i <= torre2->topo) {
            printf("%c        ", torre2->ponto[i]);
        } else {
            printf("         ");
        }

        // Torre 3
        if (i <= torre3->topo) {
            printf("%c   ", torre3->ponto[i]);
        } else {
            printf("         ");
        }

        printf("\n");
    }
    
    printf("\n");
    printf("T%c       T%c       T%c\n", cor1, cor2, cor3);
}

void imprimir_estado(Torres *torreR, Torres *torreG, Torres *torreB) {
    imprimir_torres(torreR, 'R', torreG, 'G', torreB, 'B');
    printf("\n");
}


void menu_torre() {
    printf("\n>>>  Bem-vindo(a) a Torre de Hanoi  <<<\n1 - Inciar o jogo\n0 - Sair\n\n>>> ");
}

void sair(){
    printf("\n>>> Tchau >>> ");
}