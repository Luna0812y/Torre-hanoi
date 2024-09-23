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
    
    if(origem = 'R'){
        torreOrigem = torreR;
    }else if(origem = 'B'){
        torreOrigem = torreB;
    }else if(origem = 'G'){
        torreOrigem = torreG;
    }else{
        printf("Opcao invalida");
    }

    if(destino = 'R'){
        torreDestino = torreR;
    }else if(origem = 'B'){
        torreDestino = torreB;
    }else if(origem = 'G'){
        torreDestino = torreG;
    }else{
        printf("Opcao invalida");
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
        return 1;
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
    srand(time(NULL));

    char itens[] = {'R', 'G', 'B'}; 
    int num_itens = sizeof(itens) / sizeof(itens[0]); 

    for (int i = 0; i < total; i++) {
        if (torre_cheia(torreR) && torre_cheia(torreG) && torre_cheia(torreB)) {
            printf("Todas as torres estão cheias!\n");
            break;
        }

        int tipo = rand() % num_itens; 
        char item = itens[tipo];
        
        Torres *torreAleatoria = NULL;
        int torreEscolhida = rand() % 3; 

        if(torreEscolhida = 0){
            torreAleatoria = torreR;
        }else if(torreEscolhida = 1){
            torreAleatoria = torreG;
        }else if(torreEscolhida = 2){
            torreAleatoria = torreB;
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

    const char *corR = "\033[31m"; // Vermelho para 'R'
    const char *corG = "\033[32m"; // Verde para 'G'
    const char *corB = "\033[34m"; // Azul para 'B'
    const char *reset = "\033[0m"; // Reseta cor
    
    printf("\n");
    for (int i = max_linhas - 1; i >= 0; i--) {
        // Torre 1
        if (i <= torre1->topo) {
            printf("  %s%c%s       ", torre1->ponto[i] == 'R' ? corR : (torre1->ponto[i] == 'G' ? corG : corB), torre1->ponto[i], reset);
        } else {
            printf("          ");  
        }

        // Torre 2
        if (i <= torre2->topo) {
            printf("  %s%c%s       ", torre2->ponto[i] == 'R' ? corR : (torre2->ponto[i] == 'G' ? corG : corB), torre2->ponto[i], reset);
        } else {
            printf("          ");
        }

        // Torre 3
        if (i <= torre3->topo) {
            printf("  %s%c%s   ", torre3->ponto[i] == 'R' ? corR : (torre3->ponto[i] == 'G' ? corG : corB), torre3->ponto[i], reset);
        } else {
            printf("          ");
        }

        printf("\n");
    }

    printf(" T%c        T%c        T%c\n", cor1, cor2, cor3);
}

void imprimir_estado(Torres *torreR, Torres *torreG, Torres *torreB) {
    imprimir_torres(torreR, 'R', torreG, 'G', torreB, 'B');
    printf("\n");
}