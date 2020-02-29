#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <error.h>
#include "pilhas.h"

#if (!defined EXIT_FAILURE) || (!defined EXIT_SUCCESS)
  #define EXIT_FAILURE 1
  #define EXIT_SUCCESS 0
#endif

#if (!defined INDEF)
  #define INDEF -1
#endif

/* Realoca a pilha P com N nodos a mais ou a menos. */
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

int inicializaPilha(Pilha *P, int N)
{
  int i; 
  
  if (N < 1)
  {
    error(0, 0, "inicializaPilha: quantidade invalida.");
    return EXIT_FAILURE;
  }
  else
  {
    P->topo = 0; P->tamanho = N;
    P->valores = (int *) calloc(N, sizeof(int));
    
    if (P->valores == NULL)
    { 
      error(0, 0, "inicializaPilha: erro ao alocar pilha.");
      return EXIT_FAILURE;
    }
    else
    {
      for (i = 0; i <= N-1; i++) P->valores[i] = INDEF;
      return EXIT_SUCCESS;
    }
  }
} // fim - inicializaPilha

bool pilhaCheia(Pilha *P)
{
  if (P != NULL)
    return (P->topo == P->tamanho) ? true : false;
  else
    error(0, 0, "pilhaCheia: pilha invalida.");
} // fim - pilhaCheia

bool pilhaVazia(Pilha *P)
{
  if (P != NULL)
    return (P->topo == 0) ? true : false;
  else
    error(0, 0, "pilhaVazia: pilha invalida.");
} // fim - pilhaVazia

int empilha(Pilha *P, int valor)
{
  /* Para que a pilha seja realocada e nunca fique
   * cheia, mantenha a linha abaixo ativa. */
  if (pilhaCheia(P)) realocaPilha(P, 1);

  if (P->topo < P->tamanho)
  {
    P->valores[P->topo] = valor; P->topo++;
    fprintf(stdout, "\nEmpilhado com sucesso.\n");
    return EXIT_SUCCESS;
  }
  else
  {
    error(0, 0, "empilha: pilha cheia.");
    return EXIT_FAILURE;
  }
} // fim - empilha

int desempilha(Pilha *P)
{
  int noTopo;
  if (pilhaVazia(P) || P->valores == NULL)
  {
    error(0, 0, "desempilha: pilha vazia ou invalida.");
    return EXIT_FAILURE;
  }
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
  if (P != NULL)
    return (pilhaVazia(P)) ? INDEF : P->valores[P->topo-1];
  else
    error(0, 0, "mostraTopo: fila invalida.");
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

int desalocaPilha(Pilha *P)
{
  if (P->valores != NULL)
  {
    P->topo = INDEF; P->tamanho = INDEF;
    free(P->valores); P->valores == NULL;
    return EXIT_SUCCESS;
  }
  else
  {
    error(0, 0, "desalocaPilha: pilha invalida");
    return EXIT_FAILURE;
  }
} // fim - desalocaPilha
