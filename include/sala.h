#ifndef SALA_H
#define SALA_H

// Estrutura que representa um cômodo da mansão
typedef struct Sala {
    char *nome;               // Nome do cômodo
    struct Sala *esquerda;    // Ponteiro para o cômodo à esquerda
    struct Sala *direita;     // Ponteiro para o cômodo à direita
} Sala;

/**
 * Cria dinamicamente uma sala com nome
 * @param nome Nome do cômodo
 * @return Ponteiro para a nova sala criada
 */
Sala* criarSala(const char *nome);

/**
 * Libera recursivamente toda a memória de uma árvore de salas
 * @param sala Raiz da árvore de salas
 */
void liberarSalas(Sala *sala);

#endif