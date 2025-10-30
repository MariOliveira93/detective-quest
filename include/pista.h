#ifndef PISTA_H
#define PISTA_H

// Estrutura de nó da árvore BST de pistas
typedef struct PistaNode {
    char *pista;                  // Conteúdo da pista
    struct PistaNode *esquerda;   // Subárvore esquerda
    struct PistaNode *direita;    // Subárvore direita
} PistaNode;

/**
 * Insere uma pista na árvore BST de forma ordenada
 * @param raiz Raiz da árvore de pistas
 * @param pista Pista a ser inserida
 * @return Nova raiz da árvore
 */
PistaNode* inserirPista(PistaNode *raiz, const char *pista);

/**
 * Exibe todas as pistas em ordem alfabética (percurso em ordem)
 * @param raiz Raiz da árvore de pistas
 */
void exibirPistas(PistaNode *raiz);

/**
 * Libera toda a memória da árvore de pistas
 * @param raiz Raiz da árvore de pistas
 */
void liberarPistas(PistaNode *raiz);

/**
 * Verifica se uma pista já existe na árvore BST
 * @param raiz Raiz da árvore de pistas
 * @param pista Pista a ser procurada
 * @return 1 se existe, 0 caso contrário
 */
int pistaExiste(PistaNode *raiz, const char *pista);

#endif