/* Estruturas de dados - Pilha (TAD) */

#ifndef PILHAS_H
#define PILHAS_H

typedef struct
{
  int *valores;
  int tamanho;
  int topo;
} Pilha;

/* funcoes para manipular pilhas */

void inicializaPilha(Pilha *P, int N);
void realocaPilha(Pilha *P, int N);
void empilha(Pilha *P, int valor);
int desempilha(Pilha *P);
int mostraTopo(Pilha *P);
void mostraPilha(Pilha *P);
void desalocaPilha(Pilha *P);

#endif
