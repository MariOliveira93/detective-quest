#ifndef JOGO_H
#define JOGO_H

#include "sala.h"
#include "pista.h"
#include "hash.h"

/**
 * Obtém a pista associada a um cômodo específico
 * @param nomeSala Nome do cômodo
 * @return Pista associada ou NULL se não houver
 */
char* obterPistaDaSala(const char *nomeSala);

/**
 * Controla a exploração interativa da mansão
 * Permite ao jogador navegar pelos cômodos, coletar pistas
 * @param salaAtual Sala inicial da exploração
 * @param pistasColetadas Árvore BST de pistas coletadas
 * @param tabelaSuspeitos Tabela hash com associações pista-suspeito
 * @return Raiz atualizada da árvore de pistas
 */
PistaNode* explorarSalas(Sala *salaAtual, PistaNode *pistasColetadas, TabelaHash *tabelaSuspeitos);

/**
 * Conta quantas pistas apontam para um suspeito específico
 * @param raiz Raiz da árvore de pistas coletadas
 * @param tabelaSuspeitos Tabela hash com associações
 * @param nomeSuspeito Nome do suspeito a ser verificado
 * @return Número de pistas que apontam para o suspeito
 */
int contarPistasPorSuspeito(PistaNode *raiz, TabelaHash *tabelaSuspeitos, const char *nomeSuspeito);

/**
 * Realiza o julgamento final do jogador
 * Verifica se há pistas suficientes para acusar o suspeito
 * @param pistasColetadas Árvore de pistas coletadas
 * @param tabelaSuspeitos Tabela hash com associações
 */
void verificarSuspeitoFinal(PistaNode *pistasColetadas, TabelaHash *tabelaSuspeitos);

/**
 * Constrói o mapa completo da mansão
 * @return Raiz da árvore (Hall de Entrada)
 */
Sala* construirMapa();

/**
 * Inicializa a tabela hash com todas as associações pista-suspeito
 * @param tabela Tabela hash a ser preenchida
 */
void inicializarSuspeitos(TabelaHash *tabela);

#endif