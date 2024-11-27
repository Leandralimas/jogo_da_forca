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

// Função para exibir o tabuleiro de forma formatada
void exibir(int** tabuleiro) {
    cout << endl;
    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            cout << " " << imprimirBloco(tabuleiro[linha][coluna]) << " ";  // Exibe o conteúdo da casa
            if (coluna < 2) cout << "|";  // Adiciona o separador de colunas, se não for a última coluna
        }
        cout << endl;
        if (linha < 2) cout << "---+---+---" << endl;  // Adiciona linha separadora entre as linhas do tabuleiro
    }
    cout << endl;
}

// Função para realizar uma jogada (para jogador ou computador)
void jogarJogada(int** tabuleiro, int jogador, bool computador = false) {
    int linha, coluna, verificar;

    if (computador) {  // Se for a vez do computador
        // O computador faz uma jogada aleatória em uma casa vazia
        do {
            linha = rand() % 3;          // Gera uma linha aleatória entre 0 e 2
            coluna = rand() % 3;         // Gera uma coluna aleatória entre 0 e 2
            verificar = tabuleiro[linha][coluna];  // Verifica se a casa está vazia
        } while (verificar != 0);  // Repete até encontrar uma casa vazia

        cout << "Computador jogando na linha " << linha + 1 << ", coluna " << coluna + 1 << endl;
    } else {  // Se for a vez de um jogador humano
        // Solicita ao jogador a linha e coluna para a jogada
        do {
            cout << "Linha: ";
            cin >> linha;
            cout << "Coluna: ";
            cin >> coluna;
            linha--; coluna--;  // Ajuste para índice de 0 a 2 (tabuleiro é indexado de 0 a 2)

            // Verifica se a casa está vazia e se está dentro dos limites válidos
            verificar = tabuleiro[linha][coluna] || linha < 0 || linha > 2 || coluna < 0 || coluna > 2;
            if (verificar)
                cout << "Essa casa não está vazia ou fora do intervalo 3x3" << endl;
        } while (verificar);  // Repete até uma jogada válida ser feita
    }

    // Marca a posição escolhida no tabuleiro
    if (jogador == 0)
        tabuleiro[linha][coluna] = 1;  // Jogador 1 (X)
    else
        tabuleiro[linha][coluna] = -1; // Jogador 2 (O)
}

// Função para verificar se ainda há casas vazias no tabuleiro
int verificarContinuar(int** tabuleiro) {
    for (int i = 0; i < 3; i++)  // Percorre todas as linhas
        for (int j = 0; j < 3; j++)  // Percorre todas as colunas
            if (tabuleiro[i][j] == 0)  // Se encontrar uma casa vazia
                return 1;  // Retorna 1, indicando que ainda há casas vazias
    return 0;  // Retorna 0, indicando que não há mais casas vazias
}

// Função para verificar se algum jogador venceu
int verificarVitoria(int** tabuleiro) {
    int linha, coluna, soma;

    // Verificar as linhas para vitória
    for (linha = 0; linha < 3; linha++) {
        soma = 0;
        for (coluna = 0; coluna < 3; coluna++)
            soma += tabuleiro[linha][coluna];

        if (soma == 3)
            return 1;  // Jogador 1 venceu
        if (soma == -3)
            return -1; // Jogador 2 venceu
    }

    // Verificar as colunas para vitória
    for (coluna = 0; coluna < 3; coluna++) {
        soma = 0;
        for (linha = 0; linha < 3; linha++)
            soma += tabuleiro[linha][coluna];

        if (soma == 3)
            return 1;  // Jogador 1 venceu
        if (soma == -3)
            return -1; // Jogador 2 venceu
    }
