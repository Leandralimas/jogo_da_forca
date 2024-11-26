/*
 * Jogo da Velha com os seguintes requisitos:
 * 
 * a) O jogo deve ser implementado em um tabuleiro 3x3 (ou 5x5, dependendo da escolha).
 * b) Caso o segundo jogador não esteja presente, o computador assume o papel de oponente.
 * c) O ranking dos jogadores será salvo em um arquivo de forma persistente.
 * d) O jogo deve incluir um menu com as opções: Jogar, Ver Ranking, Créditos e Sair.
 * e) A estrutura de dados do tabuleiro deve ser implementada utilizando uma matriz alocada dinamicamente.
 * f) Deve ser utilizado uma struct para armazenar os dados dos jogadores e do estado do jogo, com a possibilidade de transferir essas informações para um arquivo.
 * g) O controle das jogadas será feito através da entrada de dados via teclado, onde o jogador deve informar a posição desejada para realizar sua jogada (por exemplo: "A1", "B2", etc.).
 * 
 * O objetivo é criar um jogo interativo com persistência de dados, controle dinâmico do estado do tabuleiro, e uma experiência amigável ao usuário.
 */


#include <iostream>
#include <fstream>
#include <cstdlib>  // Para usar rand()
using namespace std;

// Estrutura para armazenar o estado do jogo (placar e resultado)
struct DadosDoJogo {
    int placarJogador1;  // Placar do Jogador 1
    int placarJogador2;  // Placar do Jogador 2
    int resultado;       // Resultado: 1 para vitória do Jogador 1, -1 para vitória do Jogador 2, 0 para empate
};

// Função para criar um tabuleiro de forma dinâmica (matriz 3x3)
int** criarTabuleiro() {
    int** tabuleiro = new int*[3];  // Cria um vetor de ponteiros para as 3 linhas do tabuleiro
    for (int i = 0; i < 3; i++) {
        tabuleiro[i] = new int[3];  // Cria um vetor de 3 inteiros para cada linha do tabuleiro
    }
    return tabuleiro;  // Retorna o tabuleiro recém-criado
}

// Função para inicializar o tabuleiro, colocando 0 em todas as casas (tabuleiro vazio)
void inicializar(int** tabuleiro) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = 0;  // Inicializa as casas com 0 (vazio)
        }
    }
}

// Função para liberar a memória alocada dinamicamente para o tabuleiro
void liberarTabuleiro(int** tabuleiro) {
    for (int i = 0; i < 3; i++) {
        delete[] tabuleiro[i];  // Libera cada linha do tabuleiro
    }
    delete[] tabuleiro;  // Libera o vetor de ponteiros
}

// Função para retornar o caractere correspondente ao valor do bloco (0, 1 ou -1)
char imprimirBloco(int bloco) {
    if (bloco == 0)          // Se a casa está vazia, retorna espaço em branco
        return ' ';
    else if (bloco == 1)     // Se o bloco for 1, é o 'X' do Jogador 1
        return 'X';
    else                     // Se o bloco for -1, é o 'O' do Jogador 2
        return 'O';
}