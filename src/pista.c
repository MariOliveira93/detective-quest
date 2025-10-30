#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pista.h"

// Insere uma pista na árvore BST de forma ordenada
PistaNode* inserirPista(PistaNode *raiz, const char *pista) {
    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*)malloc(sizeof(PistaNode));
        if (novo == NULL) {
            fprintf(stderr, "Erro ao alocar memória para pista.\n");
            exit(1);
        }
        
        novo->pista = (char*)malloc(strlen(pista) + 1);
        if (novo->pista == NULL) {
            fprintf(stderr, "Erro ao alocar memória para string da pista.\n");
            free(novo);
            exit(1);
        }
        
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    
    int comparacao = strcmp(pista, raiz->pista);
    
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    // Se comparacao == 0, a pista já existe, não inserimos duplicatas
    
    return raiz;
}

// Exibe todas as pistas em ordem alfabética (percurso em ordem)
void exibirPistas(PistaNode *raiz) {
    if (raiz == NULL) {
        return;
    }
    
    exibirPistas(raiz->esquerda);
    printf("  - %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

// Libera toda a memória da árvore de pistas
void liberarPistas(PistaNode *raiz) {
    if (raiz == NULL) {
        return;
    }
    
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz->pista);
    free(raiz);
}

// Verifica se uma pista já existe na árvore BST
int pistaExiste(PistaNode *raiz, const char *pista) {
    if (raiz == NULL) {
        return 0;
    }
    
    int comparacao = strcmp(pista, raiz->pista);
    
    if (comparacao == 0) {
        return 1;
    } else if (comparacao < 0) {
        return pistaExiste(raiz->esquerda, pista);
    } else {
        return pistaExiste(raiz->direita, pista);
    }
}