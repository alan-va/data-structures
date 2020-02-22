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

/* Inicializa a pilha P com N posicoes. */
extern void inicializaPilha(Pilha *P, int N);

/* Empilha 'valor' na pilha P. */
extern void empilha(Pilha *P, int valor);

/* Desempilha e retorna o valor no topo da pilha P. */
extern int desempilha(Pilha *P);

/* Retorna o valor no topo da pilha P. */
extern int mostraTopo(Pilha *P);

/* Mostra toda a pilha P, indicando o topo. */
extern void mostraPilha(Pilha *P);

/* Desaloca uma pilha P. */
extern void desalocaPilha(Pilha *P);

#endif /* pilhas.h */
