/* Estruturas de dados - Pilha (TAD) 
 * 
 * Programa teste em exemplo.c 
 * 
 * Funcoes inicializaPilha, empilha e desalocaPilha retornam 0 caso
 * nenhum erro ocorra e 1 caso algum erro ocorra. A funcao desempilha
 * retorna 1 caso ocorra algum erro, mostraTopo retorna INDEF caso a
 * pilha esteja vazia ou seja invalida. */

#ifndef PILHAS_H
#define PILHAS_H

#include <stdbool.h>
#define INDEF -1

typedef struct
{
  int *valores;
  int tamanho;
  int topo;
} Pilha;

/* Inicializa a pilha P com N posicoes. */
extern int inicializaPilha(Pilha *P, int N);

/* Empilha 'valor' na pilha P. */
extern int empilha(Pilha *P, int valor);

/* Desempilha e retorna o valor no topo da pilha P. */
extern int desempilha(Pilha *P);

/* Retorna TRUE se a pilha estiver cheia e FALSE caso contrario. */
extern bool pilhaCheia(Pilha *P);

/* Retorna TRUE se a pilha estiver vazia e FALSE caso contrario. */
extern bool pilhaVazia(Pilha *P);

/* Retorna o valor no topo da pilha P. */
extern int mostraTopo(Pilha *P);

/* Mostra toda a pilha P, indicando o topo. */
extern void mostraPilha(Pilha *P);

/* Desaloca uma pilha P. */
extern int desalocaPilha(Pilha *P);

#endif /* pilhas.h */
