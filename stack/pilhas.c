#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include "pilhas.h"

#if (!defined INDEF) || (!defined pilhaVazia)
  #define INDEF -1
  #define pilhaVazia -2
#endif

void inicializaPilha(Pilha *P, int N)
{
  int i; 
  
  if (N < 1)
    error(0, 0, "inicializaPilha: quantidade invalida.");
  else
  {
    P->topo = 0; P->tamanho = N;
    P->valores = (int *) calloc(N, sizeof(int));
    
    if (P->valores == NULL) 
      error(0, 0, "inicializaPilha: erro ao alocar pilha.");
    else
      for (i = 0; i <= N-1; i++) P->valores[i] = INDEF;
  }
} // fim - inicializaPilha

static void realocaPilha(Pilha *P, int N)
{
  int *valoresMod, newSize = P->tamanho + N;
  if (P->valores != NULL)
  {
    valoresMod = (int *) realloc(P->valores, newSize*sizeof(int));
    if (valoresMod != NULL)
    {
      P->valores = valoresMod; 
      P->tamanho += N; return;
    }
    else
      error(0, 0, "realocaPilha: erro ao realocar a pilha.");
  }
  else
    error(0, 0, "realocaPilha: pilha nao alocada.");
} // fim - realocaPilha

void empilha(Pilha *P, int valor)
{
  /* para que a pilha seja realocada e nunca fique
   * cheia, mantenha a linha abaixo ativa. */
  if (P->topo == P->tamanho)
    realocaPilha(P, 1);
  if (P->topo < P->tamanho)
  {
    P->valores[P->topo] = valor; P->topo++;
    fprintf(stdout, "\nEmpilhado com sucesso.\n");
  }
  else
    error(0, 0, "empilha: pilha cheia.");
} // fim - empilha

int desempilha(Pilha *P)
{
  int noTopo;
  if (P->topo == 0 || P->valores == NULL)
    error(0, 0, "desempilha: pilha vazia ou invalida.");
  else
  {
    noTopo = P->valores[P->topo-1];
    P->valores[P->topo-1] = INDEF; // desativa topo
    /* para que a pilha seja realocada com um nodo a menos
     * a cada remoção, mantenha a linha abaixo ativa.*/
    if (P->tamanho > 1) realocaPilha(P, -1);
    P->topo--; return noTopo;
  }
} // fim - desempilha

int mostraTopo(Pilha *P)
{
  return (P->topo == 0) ? pilhaVazia : P->valores[P->topo-1];
} // fim - mostraTopo

void mostraPilha(Pilha *P)
{
  int i;
  if (P->topo == 0 || P->valores == NULL)
    error(0, 0, "mostraPilha: pilha vazia ou invalida.");
  else
  {
    for (i = 1; i <= P->topo; i++) 
    { 
      if (i == 1) 
      { 
        printf("\n%.2d <- Topo\n", P->valores[P->topo-i]);
        continue; 
      }
      printf("%.2d\n", P->valores[P->topo-i]); 
    }
  }
} // fim - mostraPilha

void desalocaPilha(Pilha *P)
{
  if (P->valores != NULL)
  {
    P->topo = -1; P->tamanho = -1;
    free(P->valores); P->valores == NULL;
  }
  else
    error(0, 0, "desalocaPilha: pilha invalida");
} // fim - desalocaPilha
