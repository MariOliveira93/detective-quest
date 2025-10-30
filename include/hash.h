#ifndef HASH_H
#define HASH_H

#include "pista.h"

#define TAMANHO_HASH 50

// Estrutura para entrada da tabela hash
typedef struct EntradaHash {
    char *pista;                  // Chave: pista
    char *suspeito;               // Valor: suspeito associado
    struct EntradaHash *proximo;  // Encadeamento para colisões
} EntradaHash;

// Estrutura da tabela hash
typedef struct TabelaHash {
    EntradaHash *entradas[TAMANHO_HASH];
} TabelaHash;

/**
 * Cria e inicializa uma tabela hash
 * @return Ponteiro para a nova tabela hash
 */
TabelaHash* criarTabelaHash();

/**
 * Função hash simples que converte uma string em índice
 * @param pista String a ser convertida
 * @return Índice da tabela hash
 */
unsigned int funcaoHash(const char *pista);

/**
 * Insere uma associação pista-suspeito na tabela hash
 * @param tabela Tabela hash
 * @param pista Chave (pista)
 * @param suspeito Valor (suspeito)
 */
void inserirNaHash(TabelaHash *tabela, const char *pista, const char *suspeito);

/**
 * Busca o suspeito associado a uma pista
 * @param tabela Tabela hash
 * @param pista Pista a ser buscada
 * @return Nome do suspeito ou NULL se não encontrado
 */
char* encontrarSuspeito(TabelaHash *tabela, const char *pista);

/**
 * Libera toda a memória da tabela hash
 * @param tabela Tabela hash a ser liberada
 */
void liberarHash(TabelaHash *tabela);

#endif