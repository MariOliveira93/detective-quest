#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hash.h"

// Cria e inicializa uma tabela hash
TabelaHash* criarTabelaHash() {
    TabelaHash *tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (tabela == NULL) {
        fprintf(stderr, "Erro ao alocar memória para tabela hash.\n");
        exit(1);
    }

    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabela->entradas[i] = NULL;
    }

    return tabela;
}

// Função hash simples que converte uma string em índice
unsigned int funcaoHash(const char *pista) {
    unsigned int hash = 0;
    while (*pista) {
        hash = (hash * 31) + (*pista);
        pista++;
    }
    return hash % TAMANHO_HASH;
}

// Insere uma associação pista-suspeito na tabela hash
void inserirNaHash(TabelaHash *tabela, const char *pista, const char *suspeito) {
    unsigned int indice = funcaoHash(pista);

    // Cria nova entrada
    EntradaHash *novaEntrada = (EntradaHash*)malloc(sizeof(EntradaHash));
    if (novaEntrada == NULL) {
        fprintf(stderr, "Erro ao alocar memória para entrada hash.\n");
        exit(1);
    }

    novaEntrada->pista = (char*)malloc(strlen(pista) + 1);
    novaEntrada->suspeito = (char*)malloc(strlen(suspeito) + 1);

    if (novaEntrada->pista == NULL || novaEntrada->suspeito == NULL) {
        fprintf(stderr, "Erro ao alocar memória para strings da hash.\n");
        exit(1);
    }

    strcpy(novaEntrada->pista, pista);
    strcpy(novaEntrada->suspeito, suspeito);

    // Insere no início da lista encadeada (tratamento de colisões)
    novaEntrada->proximo = tabela->entradas[indice];
    tabela->entradas[indice] = novaEntrada;
}

// Busca o suspeito associado a uma pista
char* encontrarSuspeito(TabelaHash *tabela, const char *pista) {
    unsigned int indice = funcaoHash(pista);
    EntradaHash *entrada = tabela->entradas[indice];

    // Percorre a lista encadeada buscando a pista
    while (entrada != NULL) {
        if (strcmp(entrada->pista, pista) == 0) {
            return entrada->suspeito;
        }
        entrada = entrada->proximo;
    }

    return NULL;
}

// Libera toda a memória da tabela hash
void liberarHash(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        EntradaHash *entrada = tabela->entradas[i];
        while (entrada != NULL) {
            EntradaHash *temp = entrada;
            entrada = entrada->proximo;
            free(temp->pista);
            free(temp->suspeito);
            free(temp);
        }
    }
    free(tabela);
}