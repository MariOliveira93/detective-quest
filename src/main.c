#include <stdio.h>
#include <stdlib.h>
#include "../include/sala.h"
#include "../include/pista.h"
#include "../include/hash.h"
#include "../include/jogo.h"

/**
 * Função principal que inicia o jogo Detective Quest
 * Monta o mapa inicial e dá início à exploração
 */
int main() {
    printf("========================================\n");
    printf("     DETECTIVE QUEST - VERSÃO MESTRE\n");
    printf("========================================\n");
    printf("\nBem-vindo à Mansão do Mistério!\n");
    printf("Sua missão: explorar os cômodos, coletar\n");
    printf("pistas e descobrir o culpado.\n");
    printf("\nVocê precisa de pelo menos 2 pistas que\n");
    printf("apontem para o mesmo suspeito.\n");
    
    // Construir o mapa da mansão (árvore binária)
    Sala *mansao = construirMapa();
    
    // Criar árvore BST para armazenar pistas coletadas
    PistaNode *pistasColetadas = NULL;
    
    // Criar tabela hash para associar pistas a suspeitos
    TabelaHash *tabelaSuspeitos = criarTabelaHash();
    inicializarSuspeitos(tabelaSuspeitos);
    
    // Iniciar exploração
    pistasColetadas = explorarSalas(mansao, pistasColetadas, tabelaSuspeitos);
    
    // Fazer acusação final
    verificarSuspeitoFinal(pistasColetadas, tabelaSuspeitos);
    
    // Liberar memória
    liberarSalas(mansao);
    liberarPistas(pistasColetadas);
    liberarHash(tabelaSuspeitos);
    
    printf("\n========================================\n");
    printf("Obrigado por jogar Detective Quest!\n");
    printf("========================================\n");
    
    return 0;
}