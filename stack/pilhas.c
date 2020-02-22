#include <stdlib.h>
#include <stdio.h>
#include "pilhas.h"

#if (!defined INDEF) || (!defined pilhaVazia)
  #define INDEF -1
  #define pilhaVazia -2
#endif

void inicializaPilha(Pilha *P, int N)
{
  int i; if (N < 1) { return; }

  P->valores = (int *) calloc(N, sizeof(int));

  if (P->valores == NULL) 
  { 
    printf("Erro de alocação. (1)"); 
    return;
  }

  for (i = 0; i <= N-1; i++) P->valores[i] = INDEF;
  P->topo = 0; P->tamanho = N;
} // fim - inicializaPilha

void realocaPilha(Pilha *P, int N)
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
    else { printf("Erro na realocação. (2)"); return; }
  }
  else { printf("Pilha não alocada. (2)"); return; }
} // fim - realocaPilha

void empilha(Pilha *P, int valor)
{
  /* para que a pilha seja realocada e nunca fique
   * cheia, mantenha a linha abaixo ativa. */
  if (P->topo == P->tamanho) { realocaPilha(P, 1); }
  if (P->topo < P->tamanho)
  {
    P->valores[P->topo] = valor; P->topo++;
    printf("\nEmpilhado com sucesso.\n");
  } else { printf("\nFila cheia. (3)\n"); return; }
} // fim - empilha

int desempilha(Pilha *P)
{
  int noTopo;
  if (P->topo == 0 || P->valores == NULL) { return INDEF; }
  noTopo = P->valores[P->topo-1];
  P->valores[P->topo-1] = INDEF; // desativa topo
  /* para que a pilha seja realocada com um nodo a menos
   * a cada remoção, mantenha a linha abaixo ativa.*/
  if (P->tamanho > 1) { realocaPilha(P, -1); }
  P->topo--; return P->valores[P->topo];
} // fim - desempilha

int mostraTopo(Pilha *P)
{
  return (P->topo == 0) ? pilhaVazia : P->valores[P->topo-1];
} // fim - mostraTopo

void mostraPilha(Pilha *P)
{
  int i;
  if (P->topo == 0 || 
      P->valores == NULL) { printf("\nPilha vazia!\n"); return; }
  for (i = 1; i <= P->topo; i++) 
  { 
    if (i == 1) 
    { 
      printf("\n%.2d <- Topo\n", P->valores[P->topo-i]);
      continue; 
    }
    printf("%.2d\n", P->valores[P->topo-i]); 
  }
} // fim - mostraPilha

void desalocaPilha(Pilha *P)
{
  P->topo = -1; P->tamanho = -1;
  free(P->valores); P->valores == NULL;
} // fim - desalocaPilha
