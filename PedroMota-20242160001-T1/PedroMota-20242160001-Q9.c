#include <stdio.h>

#define GRID 10
#define MAX_EMBARCACOES 5

typedef struct {
  int comprimento;
  int hp;
} Embarcacao;

typedef struct {
  char campo[GRID][GRID];
  Embarcacao frota[MAX_EMBARCACOES];
  int qtd_embarcacoes;
} JogadorBN;

const int QUANT_EMBARCACOES = 6;
const int TAMANHOS_PADROES[MAX_EMBARCACOES] = {4, 3, 1, 1, 1, 2};

void preparar_campo(JogadorBN *j) {
  j->qtd_embarcacoes = QUANT_EMBARCACOES;
  for (int i = 0; i < GRID; i++)
    for (int k = 0; k < GRID; k++)
      j->campo[i][k] = ' ';
  for (int n = 0; n < QUANT_EMBARCACOES; n++) {
    j->frota[n].comprimento = TAMANHOS_PADROES[n];
    j->frota[n].hp = TAMANHOS_PADROES[n];
  }
}

void exibir_campo(JogadorBN *j, int revelar) {
  printf("    ");
  for (int c = 0; c < GRID; c++)
    printf("%2d ", c);
  printf("\n");
  for (int l = 0; l < GRID; l++) {
    printf("%2d ", l);
    for (int c = 0; c < GRID; c++) {
      char celula = j->campo[l][c];
      if (!revelar && celula == 'N')
        celula = ' ';
      printf("[%c]", celula);
    }
    printf("\n");
  }
}

int alocar_navio(JogadorBN *j, int indice, int lin, int col, char orientacao) {
  int tamanho = j->frota[indice].comprimento;
  for (int i = 0; i < tamanho; i++) {
    int nl = lin + (orientacao == 'V' ? i : 0);
    int nc = col + (orientacao == 'H' ? i : 0);
    if (nl >= GRID || nc >= GRID || j->campo[nl][nc] != ' ')
      return 0;
  }
  for (int i = 0; i < tamanho; i++) {
    int nl = lin + (orientacao == 'V' ? i : 0);
    int nc = col + (orientacao == 'H' ? i : 0);
    j->campo[nl][nc] = 'N';
  }
  return 1;
}

int disparar(JogadorBN *defensor, int l, int c) {
  if (l < 0 || l >= GRID || c < 0 || c >= GRID)
    return -1;

  char *celula = &defensor->campo[l][c];
  if (*celula == 'N') {
    *celula = '0';
    for (int i = 0; i < defensor->qtd_embarcacoes; i++) {
      if (defensor->frota[i].hp > 0) {
        defensor->frota[i].hp--;
        break;
      }
    }
    return 1;
  } else if (*celula == ' ') {
    *celula = 'X';
    return 0;
  }
  return -1;
}

int contar_ativos(JogadorBN *j) {
  int ativos = 0;
  for (int i = 0; i < j->qtd_embarcacoes; i++)
    if (j->frota[i].hp > 0)
      ativos++;
  return ativos;
}

void distribuir_frota(JogadorBN *j, int jogador_id) {
  printf("\n=== POSICIONAMENTO DO JOGADOR %d ===\n", jogador_id);
  for (int i = 0; i < j->qtd_embarcacoes; i++) {
    int linha, coluna;
    char direcao;
    exibir_campo(j, 1);
    printf("Navio %d (tamanho %d):\n", i + 1, j->frota[i].comprimento);
    do {
      printf("Informe linha, coluna e orientação (H/V): ");
      scanf("%d %d %c", &linha, &coluna, &direcao);
    } while (!alocar_navio(j, i, linha, coluna, direcao));
  }
}

void iniciar_batalha(JogadorBN *p1, JogadorBN *p2) {
  int vez = 0;
  while (contar_ativos(p1) > 0 && contar_ativos(p2) > 0) {
    JogadorBN *atual = (vez % 2 == 0) ? p1 : p2;
    JogadorBN *inimigo = (vez % 2 == 0) ? p2 : p1;
    int jogador_num = (vez % 2 == 0) ? 1 : 2;
    int escolha, jogada_ok = 0;

    printf("\n=== TURNO DO JOGADOR %d ===\n", jogador_num);
    while (!jogada_ok) {
      printf("\nOpções:\n");
      printf("1 - Ver meu campo\n");
      printf("2 - Ver campo inimigo\n");
      printf("3 - Atacar\n");
      printf("4 - Sair\n");
      printf("Escolha: ");
      scanf("%d", &escolha);

      if (escolha == 1) {
        printf("\n-- Seu campo --\n");
        exibir_campo(atual, 1);
      } else if (escolha == 2) {
        printf("\n-- Campo do Inimigo --\n");
        exibir_campo(inimigo, 0);
      } else if (escolha == 3) {
        int x, y, resultado;
        printf("Informe coordenadas para atacar (linha coluna): ");
        scanf("%d %d", &x, &y);
        resultado = disparar(inimigo, x, y);
        if (resultado == 1)
          printf(">> ACERTOU!\n");
        else if (resultado == 0)
          printf(">> ERROU o tiro.\n");
        else
          printf(">> Jogada inválida ou repetida. Tente de novo.\n");
        if (resultado != -1)
          jogada_ok = 1;
      } else if (escolha == 4) {
        printf("Saindo do jogo.\n");
        return;
      } else {
        printf("Opção inválida!\n");
      }
    }
    vez++;
  }

  if (contar_ativos(p1) == 0)
    printf("\nJOGADOR 2 venceu!\n");
  else
    printf("\nJOGADOR 1 venceu!\n");
}

int main() {
  JogadorBN jogador1, jogador2;
  preparar_campo(&jogador1);
  preparar_campo(&jogador2);
  distribuir_frota(&jogador1, 1);
  distribuir_frota(&jogador2, 2);
  iniciar_batalha(&jogador1, &jogador2);
  return 0;
}