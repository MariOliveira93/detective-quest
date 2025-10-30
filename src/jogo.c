#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/jogo.h"

// Obtém a pista associada a um cômodo específico
char* obterPistaDaSala(const char *nomeSala) {
    // Mapeamento estático de salas para pistas
    if (strcmp(nomeSala, "Biblioteca") == 0) {
        return "Livro com página rasgada";
    } else if (strcmp(nomeSala, "Sala de Estar") == 0) {
        return "Copo de vinho quebrado";
    } else if (strcmp(nomeSala, "Cozinha") == 0) {
        return "Faca manchada";
    } else if (strcmp(nomeSala, "Quarto Principal") == 0) {
        return "Carta anônima";
    } else if (strcmp(nomeSala, "Escritório") == 0) {
        return "Documento financeiro";
    } else if (strcmp(nomeSala, "Jardim") == 0) {
        return "Pegadas na lama";
    } else if (strcmp(nomeSala, "Porão") == 0) {
        return "Corda cortada";
    }

    return NULL;
}

// Controla a exploração interativa da mansão
PistaNode* explorarSalas(Sala *salaAtual, PistaNode *pistasColetadas, TabelaHash *tabelaSuspeitos) {
    if (salaAtual == NULL) {
        return pistasColetadas;
    }

    printf("\n========================================\n");
    printf("Você está em: %s\n", salaAtual->nome);

    // Verifica se há pista nesta sala
    char *pista = obterPistaDaSala(salaAtual->nome);
    if (pista != NULL) {
        // Verifica se a pista já foi coletada
        if (!pistaExiste(pistasColetadas, pista)) {
            printf("🔍 Pista encontrada: %s\n", pista);
            pistasColetadas = inserirPista(pistasColetadas, pista);

            // Mostra o suspeito associado
            char *suspeito = encontrarSuspeito(tabelaSuspeitos, pista);
            if (suspeito != NULL) {
                printf("   (Relacionada ao suspeito: %s)\n", suspeito);
            }
        } else {
            printf("Você já coletou a pista desta sala.\n");
        }
    } else {
        printf("Nenhuma pista encontrada nesta sala.\n");
    }

    // Mostra opções de navegação
    printf("\n");
    if (salaAtual->esquerda != NULL) {
        printf("  [E] Ir para a esquerda (%s)\n", salaAtual->esquerda->nome);
    }
    if (salaAtual->direita != NULL) {
        printf("  [D] Ir para a direita (%s)\n", salaAtual->direita->nome);
    }
    printf("  [S] Sair e fazer acusação\n");
    printf("\nEscolha uma opção: ");

    char opcao;
    scanf(" %c", &opcao);
    opcao = tolower(opcao);

    if (opcao == 'e' && salaAtual->esquerda != NULL) {
        return explorarSalas(salaAtual->esquerda, pistasColetadas, tabelaSuspeitos);
    } else if (opcao == 'd' && salaAtual->direita != NULL) {
        return explorarSalas(salaAtual->direita, pistasColetadas, tabelaSuspeitos);
    } else if (opcao == 's') {
        return pistasColetadas;
    } else {
        printf("\nOpção inválida! Tente novamente.\n");
        return explorarSalas(salaAtual, pistasColetadas, tabelaSuspeitos);
    }
}

// Conta quantas pistas apontam para um suspeito específico
int contarPistasPorSuspeito(PistaNode *raiz, TabelaHash *tabelaSuspeitos, const char *nomeSuspeito) {
    if (raiz == NULL) {
        return 0;
    }

    int contador = 0;

    // Verifica se a pista atual aponta para o suspeito
    char *suspeito = encontrarSuspeito(tabelaSuspeitos, raiz->pista);
    if (suspeito != NULL && strcmp(suspeito, nomeSuspeito) == 0) {
        contador = 1;
    }

    // Conta recursivamente nas subárvores
    contador += contarPistasPorSuspeito(raiz->esquerda, tabelaSuspeitos, nomeSuspeito);
    contador += contarPistasPorSuspeito(raiz->direita, tabelaSuspeitos, nomeSuspeito);

    return contador;
}

// Realiza o julgamento final do jogador
void verificarSuspeitoFinal(PistaNode *pistasColetadas, TabelaHash *tabelaSuspeitos) {
    printf("\n========================================\n");
    printf("FASE DE ACUSAÇÃO\n");
    printf("========================================\n");

    if (pistasColetadas == NULL) {
        printf("Você não coletou nenhuma pista!\n");
        printf("Não é possível fazer uma acusação.\n");
        return;
    }

    printf("\nPistas coletadas:\n");
    exibirPistas(pistasColetadas);

    printf("\nSuspeitos disponíveis:\n");
    printf("  - Sr. Black\n");
    printf("  - Sra. White\n");
    printf("  - Prof. Green\n");

    printf("\nQuem você acusa? ");
    char suspeito[100];
    scanf(" %[^\n]", suspeito);

    // Conta quantas pistas apontam para o suspeito acusado
    int numPistas = contarPistasPorSuspeito(pistasColetadas, tabelaSuspeitos, suspeito);

    printf("\n========================================\n");
    printf("VEREDICTO\n");
    printf("========================================\n");
    printf("Pistas que apontam para %s: %d\n\n", suspeito, numPistas);

    if (numPistas >= 2) {
        printf("✅ CASO RESOLVIDO!\n");
        printf("Você encontrou evidências suficientes!\n");
        printf("%s é o culpado!\n", suspeito);
    } else {
        printf("❌ EVIDÊNCIAS INSUFICIENTES!\n");
        printf("Você não coletou pistas suficientes para\n");
        printf("sustentar a acusação contra %s.\n", suspeito);
        printf("O culpado escapou...\n");
    }
}

// Constrói o mapa completo da mansão
Sala* construirMapa() {
    // Criando os cômodos
    Sala *hall = criarSala("Hall de Entrada");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *quarto = criarSala("Quarto Principal");
    Sala *escritorio = criarSala("Escritório");
    Sala *jardim = criarSala("Jardim");
    Sala *porao = criarSala("Porão");

    // Montando a estrutura da árvore
    //           Hall
    //          /    \
    //    Biblioteca  Sala de Estar
    //      /    \       /       \
    //  Cozinha Quarto Escritório Jardim
    //                              /
    //                           Porão

    hall->esquerda = biblioteca;
    hall->direita = salaEstar;

    biblioteca->esquerda = cozinha;
    biblioteca->direita = quarto;

    salaEstar->esquerda = escritorio;
    salaEstar->direita = jardim;

    jardim->esquerda = porao;

    return hall;
}

// Inicializa a tabela hash com todas as associações pista-suspeito
void inicializarSuspeitos(TabelaHash *tabela) {
    // Associando pistas a suspeitos
    inserirNaHash(tabela, "Livro com página rasgada", "Prof. Green");
    inserirNaHash(tabela, "Copo de vinho quebrado", "Sra. White");
    inserirNaHash(tabela, "Faca manchada", "Sr. Black");
    inserirNaHash(tabela, "Carta anônima", "Prof. Green");
    inserirNaHash(tabela, "Documento financeiro", "Sr. Black");
    inserirNaHash(tabela, "Pegadas na lama", "Sra. White");
    inserirNaHash(tabela, "Corda cortada", "Sr. Black");
}