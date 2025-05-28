#include "PedroMota-20242160001-T1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]) {
  DataQuebrada dq;
  char sDia[3], sMes[3], sAno[5];
  int i, j;

  for (i = 0; data[i] != '/'; i++) {
    sDia[i] = data[i];
  }
  sDia[i] = '\0';
  if (i != 1 && i != 2) {
    dq.valido = 0;
    return dq;
  }

  j = i + 1;
  for (i = 0; data[j] != '/'; j++, i++) {
    sMes[i] = data[j];
  }
  sMes[i] = '\0';
  if (i != 1 && i != 2) {
    dq.valido = 0;
    return dq;
  }

  j = j + 1;
  for (i = 0; data[j] != '\0'; j++, i++) {
    sAno[i] = data[j];
  }
  sAno[i] = '\0';
  if (i != 2 && i != 4) {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);
  dq.valido = 1;

  return dq;
}

int somar(int x, int y) {
  int soma;
  soma = x + y;
  return soma;
}

int fatorial(int x) {
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a) {
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}

int q1(char data[]) {
  DataQuebrada dq = quebraData(data);

  if (dq.valido == 0)
    return 0;

  int dia = dq.iDia;
  int mes = dq.iMes;
  int ano = dq.iAno;

  if (ano < 100) {
    if (ano >= 0 && ano <= 49)
      ano += 2000;
    else
      ano += 1900;
  }

  if (mes < 1 || mes > 12)
    return 0;

  if (dia < 1)
    return 0;

  int diasMes;

  switch (mes) {
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    diasMes = 31;
    break;
  case 4:
  case 6:
  case 9:
  case 11:
    diasMes = 30;
    break;
  case 2:
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
      diasMes = 29;
    else
      diasMes = 28;
    break;
  default:
    return 0;
  }

  if (dia > diasMes)
    return 0;

  return 1;
}

DiasMesesAnos q2(char datainicial[], char datafinal[]) {
  DiasMesesAnos dma;
  dma.qtdDias = 0;
  dma.qtdMeses = 0;
  dma.qtdAnos = 0;

  if (q1(datainicial) == 0) {
    dma.retorno = 2;
    return dma;
  }

  if (q1(datafinal) == 0) {
    dma.retorno = 3;
    return dma;
  }

  DataQuebrada ini = quebraData(datainicial);
  DataQuebrada fim = quebraData(datafinal);

  if (ini.iAno < 100)
    ini.iAno += (ini.iAno <= 49) ? 2000 : 1900;

  if (fim.iAno < 100)
    fim.iAno += (fim.iAno <= 49) ? 2000 : 1900;

  if (fim.iAno < ini.iAno || (fim.iAno == ini.iAno && fim.iMes < ini.iMes) ||
      (fim.iAno == ini.iAno && fim.iMes == ini.iMes && fim.iDia < ini.iDia)) {
    dma.retorno = 4;
    return dma;
  }

  int dia1 = ini.iDia;
  int mes1 = ini.iMes;
  int ano1 = ini.iAno;
  int dia2 = fim.iDia;
  int mes2 = fim.iMes;
  int ano2 = fim.iAno;

  dma.qtdAnos = ano2 - ano1;
  dma.qtdMeses = mes2 - mes1;
  dma.qtdDias = dia2 - dia1;

  if (dma.qtdDias < 0) {
    dma.qtdMeses--;
    int diasNoMesAnterior;
    int m = mes2 - 1;
    int a = ano2;

    if (m == 0) {
      m = 12;
      a--;
    }

    switch (m) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      diasNoMesAnterior = 31;
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      diasNoMesAnterior = 30;
      break;
    case 2:
      diasNoMesAnterior =
          ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) ? 29 : 28;
      break;
    default:
      diasNoMesAnterior = 30;
    }

    dma.qtdDias += diasNoMesAnterior;
  }

  if (dma.qtdMeses < 0) {
    dma.qtdAnos--;
    dma.qtdMeses += 12;
  }

  dma.retorno = 1;
  return dma;
}

int q3(char *texto, char c, int isCaseSensitive) {
  int qtdOcorrencias = 0;

  if (isCaseSensitive != 1) {
    if (c >= 'A' && c <= 'Z') {
      c = c + 32;
    }
  }

  for (int i = 0; texto[i] != '\0'; i++) {
    char atual = texto[i];

    if (isCaseSensitive != 1) {
      if (atual >= 'A' && atual <= 'Z') {
        atual = atual + 32;
      }
    }

    if (atual == c) {
      qtdOcorrencias++;
    }
  }

  return qtdOcorrencias;
}

void noSpecials(char *text) {
  int i, j = 0;

  const char *comAcentos[] = {"Ä", "Å", "Á", "Â", "À", "Ã", "ä", "á", "â", "à",
                              "ã", "É", "Ê", "Ë", "È", "é", "ê", "ë", "è", "Í",
                              "Î", "Ï", "Ì", "í", "î", "ï", "ì", "Ö", "Ó", "Ô",
                              "Ò", "Õ", "ö", "ó", "ô", "ò", "õ", "Ü", "Ú", "Û",
                              "ü", "ú", "û", "ù", "Ç", "ç"};

  const char *semAcentos[] = {"A", "A", "A", "A", "A", "A", "a", "a", "a", "a",
                              "a", "E", "E", "E", "E", "e", "e", "e", "e", "I",
                              "I", "I", "I", "i", "i", "i", "i", "O", "O", "O",
                              "O", "O", "o", "o", "o", "o", "o", "U", "U", "U",
                              "u", "u", "u", "u", "C", "c"};

  char buffer[256];
  buffer[0] = '\0';

  for (int i = 0; i < strlen(text);) {
    int found = 0;
    for (int j = 0; j < sizeof(comAcentos) / sizeof(comAcentos[0]); j++) {
      int len = strlen(comAcentos[j]);

      if (strncmp(&text[i], comAcentos[j], len) == 0) {
        strcat(buffer, semAcentos[j]);
        i += len;
        found = 1;
        break;
      }
    }
    if (!found) {
      strncat(buffer, &text[i], 1);
      i++;
    }
  }
  strcpy(text, buffer);
}

int q4(char *strTexto, char *strBusca, int posicoes[30]) {
  int qtdOcorrencias = 0;
  int posicao = 0;
  int len = strlen(strBusca);
  noSpecials(strTexto);
  noSpecials(strBusca);

  for (int i = 0; i < strlen(strTexto);) {
    int achou = 0;
    if (strTexto[i] == strBusca[0]) {
      achou = 1;
      for (int j = i, k = 0; k < len; j++, k++) {
        if (strBusca[k] != strTexto[j])
          achou = 0;
      }
      if (achou) {
        qtdOcorrencias++;
        posicoes[posicao] = i + 1;
        posicao++;
        posicoes[posicao] = i + len;
        posicao++;

        i += len;
      } else {
        i++;
      }
    }
    if (!achou)
      i++;
  }

  return qtdOcorrencias;
}

int q5(int num) {
  int invertido = 0;

  while (num > 0) {
    invertido = invertido * 10 + (num % 10);
    num /= 10;
  }

  return invertido;
}

int q6(int numerobase, int numerobusca) {
  int qtdOcorrencias = 0;
  char baseStr[50], buscaStr[50];

  sprintf(baseStr, "%d", numerobase);
  sprintf(buscaStr, "%d", numerobusca);

  int tamBusca = strlen(buscaStr);
  int tamBase = strlen(baseStr);

  for (int i = 0; i <= tamBase - tamBusca; i++) {
    int encontrou = 1;
    for (int j = 0; j < tamBusca; j++) {
      if (baseStr[i + j] != buscaStr[j]) {
        encontrou = 0;
        break;
      }
    }
    if (encontrou)
      qtdOcorrencias++;
  }

  return qtdOcorrencias;
}

int q7(char matriz[8][10], char palavra[5]) {
  int linhas = 8, colunas = 10;
  int tamPalavra = strlen(palavra);

  int direcoes[8][2] = {{0, 1},  {1, 0},  {1, 1},   {1, -1},
                        {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}};

  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      for (int d = 0; d < 8; d++) {
        int dirX = direcoes[d][0], dirY = direcoes[d][1];
        int k, x = i, y = j;
        int encontrado = 1;

        for (k = 0; k < tamPalavra; k++) {
          if (x < 0 || x >= linhas || y < 0 || y >= colunas ||
              matriz[x][y] != palavra[k]) {
            encontrado = 0;
            break;
          }
          x += dirX;
          y += dirY;
        }

        if (encontrado) {
          return 1;
        }
      }
    }
  }

  return 0;
}