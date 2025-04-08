#include <stdio.h>

// Define o tamanho do tabuleiro (10x10)
#define TAMANHO_TABULEIRO 10

// Define o tamanho fixo dos navios (3 posições)
#define TAMANHO_NAVIO 3

// Valor que representa a parte de um navio no tabuleiro
#define NAVIO 3

// Valor que representa água no tabuleiro
#define AGUA 0

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Verifica se o navio pode ser posicionado sem sair do limite e sem sobreposição
int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                         int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'A') { l -= i; c += i; }

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0; // Fora do limite

        if (tabuleiro[l][c] != AGUA)
            return 0; // Sobreposição
    }
    return 1;
}

// Marca as posições do navio na matriz
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'A') { l -= i; c += i; }

        tabuleiro[l][c] = NAVIO;
    }
}

// Exibe o tabuleiro com cabeçalhos
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf(" %c", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf(" %c ", 'A' + i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Navio horizontal: C5 (linha 2, coluna 4)
    if (podePosicionarNavio(tabuleiro, 2, 4, 'H'))
        posicionarNavio(tabuleiro, 2, 4, 'H');

    // Navio vertical: E8 (linha 4, coluna 7)
    if (podePosicionarNavio(tabuleiro, 4, 7, 'V'))
        posicionarNavio(tabuleiro, 4, 7, 'V');

    // Diagonal ↘: A1 → C3 (linha 0, coluna 0)
    if (podePosicionarNavio(tabuleiro, 0, 0, 'D'))
        posicionarNavio(tabuleiro, 0, 0, 'D');

    // Diagonal ↗: E3 → C5 (linha 4, coluna 2)
    if (podePosicionarNavio(tabuleiro, 4, 2, 'A'))
        posicionarNavio(tabuleiro, 4, 2, 'A');

    printf("\n   T A B U L E I R O   C O M   N A V I O S\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
