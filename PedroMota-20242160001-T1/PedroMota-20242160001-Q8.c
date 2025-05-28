#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 3

void mostrarTabuleiro(char grade[TAMANHO][TAMANHO]) {
  printf("\n   1   2   3\n");
  for (int linha = 0; linha < TAMANHO; linha++) {
    printf("%c ", 'A' + linha);
    for (int coluna = 0; coluna < TAMANHO; coluna++) {
      printf(" %c ", grade[linha][coluna]);
      if (coluna < TAMANHO - 1)
        printf("|");
    }
    printf("\n");
    if (linha < TAMANHO - 1)
      printf("  ---+---+---\n");
  }
  printf("\n");
}

void inicializarTabuleiro(char grade[TAMANHO][TAMANHO]) {
  for (int i = 0; i < TAMANHO; i++)
    for (int j = 0; j < TAMANHO; j++)
      grade[i][j] = ' ';
}

int posicaoValida(char entrada[3]) {
  return (toupper(entrada[0]) >= 'A' && toupper(entrada[0]) <= 'C' &&
          entrada[1] >= '1' && entrada[1] <= '3');
}

int verificarEspacoLivre(char grade[TAMANHO][TAMANHO], int linha, int coluna) {
  return (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO &&
          grade[linha][coluna] == ' ');
}

int venceu(char grade[TAMANHO][TAMANHO], char simbolo) {
  for (int i = 0; i < TAMANHO; i++) {
    if ((grade[i][0] == simbolo && grade[i][1] == simbolo &&
         grade[i][2] == simbolo) ||
        (grade[0][i] == simbolo && grade[1][i] == simbolo &&
         grade[2][i] == simbolo))
      return 1;
  }
  if ((grade[0][0] == simbolo && grade[1][1] == simbolo &&
       grade[2][2] == simbolo) ||
      (grade[0][2] == simbolo && grade[1][1] == simbolo &&
       grade[2][0] == simbolo))
    return 1;

  return 0;
}

int estaCompleto(char grade[TAMANHO][TAMANHO]) {
  for (int i = 0; i < TAMANHO; i++)
    for (int j = 0; j < TAMANHO; j++)
      if (grade[i][j] == ' ')
        return 0;
  return 1;
}

void jogadaUsuario(char grade[TAMANHO][TAMANHO], char simbolo) {
  char entrada[3];
  int linha, coluna;

  while (1) {
    printf("Informe sua jogada (ex: A1): ");
    scanf("%2s", entrada);

    if (!posicaoValida(entrada)) {
      printf("Entrada inválida! Use de A1 a C3.\n");
      continue;
    }

    linha = toupper(entrada[0]) - 'A';
    coluna = entrada[1] - '1';

    if (!verificarEspacoLivre(grade, linha, coluna)) {
      printf("Posição ocupada. Tente outra.\n");
      continue;
    }

    grade[linha][coluna] = simbolo;
    break;
  }
}

void jogadaAleatoriaIA(char grade[TAMANHO][TAMANHO], char simbolo) {
  int l, c;
  do {
    l = rand() % 3;
    c = rand() % 3;
  } while (grade[l][c] != ' ');
  grade[l][c] = simbolo;
}

int main() {
  char tabuleiro[TAMANHO][TAMANHO];
  int modoDeJogo, rodada, vez = 1;
  char simboloAtual;
  char continuar;
  int placarJogador1 = 0, placarJogador2 = 0;

  srand(time(NULL));

  printf("=== JOGO DA VELHA ===\n");
  printf("1 - Jogador vs Jogador\n");
  printf("2 - Jogador vs Computador\n");
  printf("Escolha o modo: ");
  scanf("%d", &modoDeJogo);

  do {
    inicializarTabuleiro(tabuleiro);
    vez = 1;

    while (1) {
      mostrarTabuleiro(tabuleiro);
      simboloAtual = (vez == 1) ? 'X' : 'O';

      if (modoDeJogo == 2 && vez == 2) {
        printf("Computador está pensando...\n");
        jogadaAleatoriaIA(tabuleiro, simboloAtual);
      } else {
        printf("Jogador %d (%c)\n", vez, simboloAtual);
        jogadaUsuario(tabuleiro, simboloAtual);
      }

      if (venceu(tabuleiro, simboloAtual)) {
        mostrarTabuleiro(tabuleiro);
        if (modoDeJogo == 2 && vez == 2) {
          printf("O Computador venceu!\n");
          placarJogador2++;
        } else {
          printf("Jogador %d venceu!\n", vez);
          (vez == 1) ? placarJogador1++ : placarJogador2++;
        }
        break;
      }

      if (estaCompleto(tabuleiro)) {
        mostrarTabuleiro(tabuleiro);
        printf("Empate!\n");
        break;
      }

      vez = (vez == 1) ? 2 : 1;
    }

    printf("Placar: Jogador 1 = %d | %s = %d\n", placarJogador1,
           (modoDeJogo == 2) ? "Computador" : "Jogador 2", placarJogador2);

    printf("Jogar novamente? (S/N): ");
    scanf(" %c", &continuar);
    continuar = toupper(continuar);

  } while (continuar == 'S');

  printf("Obrigado por jogar!\n");
  return 0;
}