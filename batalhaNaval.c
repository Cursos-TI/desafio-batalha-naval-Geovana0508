#include <stdio.h>

// Define o tamanho do tabuleiro (10x10)
#define TAMANHO_TABULEIRO 10

// Define o tamanho fixo dos navios (3 posições)
#define TAMANHO_NAVIO 3

// Valor que representa a parte de um navio no tabuleiro
#define NAVIO 3

// Valor que representa água no tabuleiro
#define AGUA 0

// Função que inicializa o tabuleiro com valor 0 (representando água)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função que verifica se é possível posicionar um navio nas coordenadas informadas
// Garante que o navio fique dentro do tabuleiro e não sobreponha outro
int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                         int linha, int coluna, char orientacao) {
    if (orientacao == 'H') { // Horizontal
        // Verifica se o navio cabe horizontalmente
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

        // Verifica se há sobreposição com outro navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != AGUA) return 0;
        }

    } else if (orientacao == 'V') { // Vertical
        // Verifica se o navio cabe verticalmente
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

        // Verifica se há sobreposição com outro navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != AGUA) return 0;
        }
    }

    // Se passou por todos os testes, pode posicionar o navio
    return 1;
}

// Função que posiciona o navio na matriz do tabuleiro com valor 3 (NAVIO)
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 'H') {
            tabuleiro[linha][coluna + i] = NAVIO;  // Marca as células horizontalmente
        } else if (orientacao == 'V') {
            tabuleiro[linha + i][coluna] = NAVIO;  // Marca as células verticalmente
        }
    }
}

// Função que exibe o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Cabeçalho das colunas com letras
    printf("   "); // Espaço para alinhar com as letras das linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf(" %c", 'A' + i);
    }
    printf("\n");

    // Laço para imprimir cada linha do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf(" %c ", 'A' + i); // Letra da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]); // Imprime o valor da célula (0 ou 3)
        }
        printf("\n");
    }
}

// Função principal do programa
int main() {
    // Declaração da matriz que representa o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições com água
    inicializarTabuleiro(tabuleiro);

    // Coordenadas de início para os dois navios (pré-definidas)
    int linha1 = 2, coluna1 = 4; // Navio 1 na horizontal a partir da posição C5
    int linha2 = 5, coluna2 = 7; // Navio 2 na vertical a partir da posição F8

    // Verifica se é possível posicionar o navio horizontal e posiciona
    if (podePosicionarNavio(tabuleiro, linha1, coluna1, 'H')) {
        posicionarNavio(tabuleiro, linha1, coluna1, 'H');
    } else {
        printf("Erro ao posicionar navio horizontal!\n");
    }

    // Verifica se é possível posicionar o navio vertical e posiciona
    if (podePosicionarNavio(tabuleiro, linha2, coluna2, 'V')) {
        posicionarNavio(tabuleiro, linha2, coluna2, 'V');
    } else {
        printf("Erro ao posicionar navio vertical!\n");
    }

    // Exibe o título e o tabuleiro final com os navios posicionados
    printf("\n   T A B U L E I R O   C O M   N A V I O S\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
