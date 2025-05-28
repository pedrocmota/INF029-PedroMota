#ifndef TRABALHO1_H
#define TRABALHO1_H

typedef struct DQ {
  int iDia;
  int iMes;
  int iAno;
  int valido;

} DataQuebrada;

typedef struct Qtd {
  int qtdDias;
  int qtdMeses;
  int qtdAnos;
  int retorno;

} DiasMesesAnos;

int somar(int x, int y);
int fatorial(int x);
int q1(char data[]);
DiasMesesAnos q2(char datainicial[], char datafinal[]);
int q3(char *texto, char c, int isCaseSensitive);
int q4(char *strTexto, char *strBusca, int posicoes[30]);
int q5(int num);
int q6(int numerobase, int numerobusca);
int q7(char matriz[8][10], char palavra[5]);
DataQuebrada quebraData(char data[]);

#endif
