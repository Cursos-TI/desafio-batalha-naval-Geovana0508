
#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5
#define TAMANHO_HABILIDADE 5

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
            if (tabuleiro[i][j] == AGUA)
                printf(" ~");
            else if (tabuleiro[i][j] == NAVIO)
                printf(" N");
            else if (tabuleiro[i][j] == HABILIDADE)
                printf(" *");
            else
                printf(" ?");
        }
        printf("\n");
    }
}

// Cria matriz de habilidade em forma de cone (expandindo para baixo)
void criarMatrizCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Ativa posições entre (meio - i) e (meio + i)
            if (j >= TAMANHO_HABILIDADE / 2 - i && j <= TAMANHO_HABILIDADE / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade em forma de cruz
void criarMatrizCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade em forma de octaedro (losango)
void criarMatrizOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Losango: |linha - meio| + |coluna - meio| <= raio
            if (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica uma matriz de habilidade ao tabuleiro centralizada na posição (linha, coluna)
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int linhaCentro, int colunaCentro) {
    int offset = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int l = linhaCentro - offset + i;
            int c = colunaCentro - offset + j;

            if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
                if (matriz[i][j] == 1 && tabuleiro[l][c] == AGUA)
                    tabuleiro[l][c] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posiciona alguns navios
    if (podePosicionarNavio(tabuleiro, 2, 4, 'H'))
        posicionarNavio(tabuleiro, 2, 4, 'H');

    if (podePosicionarNavio(tabuleiro, 4, 7, 'V'))
        posicionarNavio(tabuleiro, 4, 7, 'V');

    if (podePosicionarNavio(tabuleiro, 0, 0, 'D'))
        posicionarNavio(tabuleiro, 0, 0, 'D');

    if (podePosicionarNavio(tabuleiro, 4, 2, 'A'))
        posicionarNavio(tabuleiro, 4, 2, 'A');

    // Matrizes das habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplica habilidades em posições definidas
    aplicarHabilidade(tabuleiro, cone, 6, 2);       // Cone no ponto G3
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz no ponto F6
    aplicarHabilidade(tabuleiro, octaedro, 2, 8);   // Octaedro no ponto C9

    printf("\n   T A B U L E I R O   C O M   N A V I O S\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
