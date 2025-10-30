#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sala.h"

// Cria dinamicamente uma sala com nome
Sala* criarSala(const char *nome) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        fprintf(stderr, "Erro ao alocar memória para sala.\n");
        exit(1);
    }
    
    novaSala->nome = (char*)malloc(strlen(nome) + 1);
    if (novaSala->nome == NULL) {
        fprintf(stderr, "Erro ao alocar memória para nome da sala.\n");
        free(novaSala);
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// Libera recursivamente toda a memória de uma árvore de salas
void liberarSalas(Sala *sala) {
    if (sala == NULL) {
        return;
    }
    
    liberarSalas(sala->esquerda);
    liberarSalas(sala->direita);
    free(sala->nome);
    free(sala);
}