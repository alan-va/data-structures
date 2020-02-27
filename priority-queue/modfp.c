/* 
  Implementacoes das funcoes de modfp.h. As
  descricoes das funcoes estao no cabecalho. 
*/

#include <stdlib.h> /* NULL, calloc(), realloc() */
#include <error.h> /* error() */
#include <stdio.h> /* fprintf() */
#include "modfp.h" /* NodoFp, Fp, <stdbool.h> */

#if (!defined EXIT_FAILURE) || (!defined EXIT_SUCCESS)
  #define EXIT_FAILURE 1 && EXIT_SUCCESS 0
#endif

#ifndef INDEF
  #define INDEF -1
#endif

/* Funcoes de comparacao (publicas). */
bool crescente(int x, int y) { return (x > y) ? true : false; }
bool decrescente(int x, int y) { return (x < y) ? true : false; }

/* Funcoes de criacao de uma fila (publicas). */
Fp criaFila(void) { return (Fp){NULL, NULL, INDEF, INDEF}; }
Fp* criaFilaPtr(void) { return &(Fp){NULL, NULL, INDEF, INDEF}; }

/*---------------------------------------------------------------*/
/* Funcoes auxiliares (privadas) da manipulacao de uma fila:     */
/*---------------------------------------------------------------*/

static int pai(int i) { return (int)((i-1)/2); }
static int dir(int i) { return (2*i + 2); }
static int esq(int i) { return (2*i + 1); }

/* Aumenta ou diminui o tamanho de uma fila ja alocada em __qtdNodos. */
static int realocaFila(Fp *Fila, const int __qtdNodos)
{
  size_t nT = (size_t)(Fila->qtdMax + __qtdNodos); /* Novo tamanho. */
  int *indNodoMod = NULL; /* Pointeiros auxiliares apontanto */
  NodoFp *nodoMod = NULL; /* para nulo inicialmente. */

  if (Fila->nodo != NULL && Fila->indNodo != NULL)
  {
    nodoMod = (NodoFp *) realloc(Fila->nodo, nT*sizeof(NodoFp));
    indNodoMod = (int *) realloc(Fila->indNodo, nT*sizeof(int));
    if (nodoMod != NULL && indNodoMod != NULL)
    {
      Fila->nodo = nodoMod; Fila->indNodo = indNodoMod;
      Fila->qtdMax += (int)(__qtdNodos); return 0;
    }
    else
    {
      error(0, 0, "realocaFila: erro na realocacao da fila.");
      return EXIT_FAILURE;
    }
  }
  else
  {
    error(0, 0, "realocaFila: fila mal alocada previamente.");
    return EXIT_FAILURE;
  }
} /* fim - realocaFila (funcao interna) */

/* Troca dois nodos na fila Fila atraves de seus indices. */
static void trocaNodos(Fp * const Fila, const int _ind1, const int _ind2)
{
  /* auxiliares para fazer as trocas */
  int indAux = Fila->indNodo[Fila->nodo[_ind1].id];
  int priAux = Fila->nodo[_ind1].pri;
  int idAux = Fila->nodo[_ind1].id;

  /* verifica se algum nodo tem info. invalida */
  if (indAux == INDEF || priAux == INDEF || idAux == INDEF ||
      Fila->indNodo[Fila->nodo[_ind2].id] == INDEF ||
      Fila->nodo[_ind2].pri == INDEF || 
      Fila->nodo[_ind2].id == INDEF) 
  { 
    error(0, 0, "trocaNodos: nodos com infos invalidas.");
    return;
  }
  else
  {
    /* troca os indices */
    Fila->indNodo[Fila->nodo[_ind1].id] = Fila->indNodo[Fila->nodo[_ind2].id];
    Fila->indNodo[Fila->nodo[_ind2].id] = indAux;

    /* troca as prioridades */
    Fila->nodo[_ind1].pri = Fila->nodo[_ind2].pri;
    Fila->nodo[_ind2].pri = priAux;

    /* troca os ids */
    Fila->nodo[_ind1].id = Fila->nodo[_ind2].id;
    Fila->nodo[_ind2].id = idAux;
  }
} /* fim - trocaNodos (funcao interna) */

/* Mantem a integridade do min-max-heap apos uma insercao
   ou modificacao na prioridade de um nodo na fila. */
static void heapifyUp(Fp * const Fila, const int __indOrigem,
    const bool (*__fcomparacao)(const int _prio1, const int _prio2))
{
  int indiceNodo = __indOrigem;
  int p = pai(indiceNodo);
  
  while (indiceNodo > 0 && 
    (*__fcomparacao)(Fila->nodo[p].pri, Fila->nodo[indiceNodo].pri))
  {
    trocaNodos(Fila, indiceNodo, p);
    indiceNodo = p; p = pai(indiceNodo);
  }
} /* fim - heapifyUp (funcao interna) */

/* Mantem a integridade do min-max-heap apos uma remocao
   ou modificacao na prioridade de um nodo na fila. */
static void heapifyDown(Fp * const Fila, const int __indNodo, 
    const bool (*__fcomparacao)(const int _prio1, const int _prio2))
{
  /* __indNodo = raiz da subarvore a ser 'consertada'. */
  int j, l, r, i = __indNodo;
  
  while (i >= 0)
  {
    j = INDEF; r = dir(i); l = esq(i);
    
    if (r < Fila->qtdNodos && 
      (*__fcomparacao)(Fila->nodo[i].pri, Fila->nodo[r].pri))
    {
      if ((*__fcomparacao)(Fila->nodo[r].pri, Fila->nodo[l].pri))
        j = l;
      else
        j = r;
    }
    else
    {
      if (l < Fila->qtdNodos && 
        (*__fcomparacao)(Fila->nodo[i].pri, Fila->nodo[l].pri)) { j = l; }
    }
    
    if (j >= 0) { trocaNodos(Fila, j, i); }
    i = j;
  }
} /* end - heapifyDown (funcao interna) */

/* Desativa um nodo (ativo), funcao usada durante a remocao. */
static void desativaNodo(Fp * const Fila, const int __indNodo)
{
  if (__indNodo == INDEF || (Fila->nodo[__indNodo].id == INDEF &&
      Fila->indNodo[__indNodo] == INDEF && 
      Fila->nodo[__indNodo].pri == INDEF)) 
  {
    error(0, 0, "%s %s %d", "removeDaFila: erro ao",
      "desativar nodo com ID", __indNodo); return;
  }
  else
  {
    Fila->indNodo[Fila->nodo[__indNodo].id] = INDEF;
    Fila->nodo[__indNodo].pri = INDEF;
    Fila->nodo[__indNodo].id = INDEF;
  }
} /* fim - desativaNodo (funcao interna) */

/*------------------------------------------------*/
/* Funcoes (publicas) de manipulacao de uma fila: */
/*------------------------------------------------*/

bool filaVazia(const Fp * const Fila)
{ 
  if (Fila != NULL)
    return (Fila->qtdNodos > 0) ? false : true;
  else
    error(0, 0, "filaVazia: fila invalida.");
} /* fim - filaVazia */

bool filaCheia(const Fp * const Fila)
{
  if (Fila != NULL)
    return (Fila->qtdNodos == Fila->qtdMax) ? true : false;
  else
    error(0, 0, "filaCheia: fila invalida.");
} /* fim - filaCheia */

int inicializaFila(Fp *Fila, const int N)
{
  int i;
  
  if (N < 1) /* Inicializacao deve ter pelo menos um nodo. */
    error(0, 0, "inicializaFila: quantidade invalida de nodos.");
  else if (Fila->nodo != NULL || Fila->indNodo != NULL)
    error(0, 0, "inicializaFila: fila nao criada ou ja inicializada.");
  else
  {
    Fila->qtdNodos = 0; Fila->qtdMax = N;
    Fila->nodo = NULL; Fila->indNodo = NULL;
    Fila->nodo = (NodoFp *) calloc(Fila->qtdMax, sizeof(NodoFp));
    Fila->indNodo = (int *) calloc(Fila->qtdMax, sizeof(int));

    if (Fila->nodo == NULL || Fila->indNodo == NULL) 
      error(0, 0, "%s", "inicializaFila: erro de alocacao de "
        "memoria durante a inicializacao.");
    else
    {
      for (i = 0; i <= Fila->qtdMax-1; i++)
      {
        Fila->indNodo[i] = INDEF;
        Fila->nodo[i].id = INDEF;
        Fila->nodo[i].pri = INDEF;
      }
      return EXIT_SUCCESS;
    }
  }
  
  return EXIT_FAILURE;
} /* fim - inicializaFila */

int insereNaFila(Fp * const Fila, const int idNodo, const int pri,
    const bool (*_modo)(const int, const int))
{
  short int status = 0;
  
  if (Fila->nodo == NULL || Fila->indNodo == NULL)
    error(0, 0, "insereNaFila: fila mal alocada previamente");
  else
  {
    if (idNodo > Fila->qtdMax-1)
      error(0, 0, "%s %d", "insereNaFila: ID deve ser menor que", 
        Fila->qtdMax);
    else if (filaCheia(Fila))
    {
      status = realocaFila(Fila, 1);
      if (status == EXIT_FAILURE)
        error(0, 0, "insereNaFila: erro ao aumentar a fila");
      /* Descomente o codigo abaixo e comente o codigo acima
         para que o tamanho maximo da fila seja fixo (qtdMax). */
      /*error(0, 0, "insereNaFila: fila cheia.");*/
    }
    else
    {
      Fila->nodo[Fila->qtdNodos].pri = pri;
      Fila->nodo[Fila->qtdNodos].id = idNodo;
      Fila->indNodo[idNodo] = Fila->qtdNodos;
      Fila->qtdNodos++;
      if (Fila->qtdNodos > 1)
        heapifyUp(Fila, Fila->qtdNodos-1, (*_modo));
      return EXIT_SUCCESS;
    }
  }
  
  return EXIT_FAILURE;
} /* fim - insereNaFila */

NodoFp removeDaFila(Fp *Fila, const bool (*_modo)(const int, const int))
{
  NodoFp Frente = {INDEF, INDEF};
  
  if (Fila->nodo == NULL || Fila->indNodo == NULL)
    error(0, 0, "removeDaFila: fila invalida.");
  else if (filaVazia(Fila))
    error(0, 0, "removeDaFila: fila vazia.");
  else // Fila valida e nao vazia.
  {
    Frente = Fila->nodo[0];
    
    if (Fila->qtdNodos == 1)
    {
      desativaNodo(Fila, 0);
      Fila->qtdNodos--; 
    }
    else
    {
      /* Troca frente & fim da fila e desativa nodo fim. */
      trocaNodos(Fila, 0, Fila->qtdNodos-1);
      desativaNodo(Fila, Fila->qtdNodos-1); 
      Fila->qtdNodos--;

      if (Fila->qtdNodos > 1) 
        heapifyDown(Fila, 0, (*_modo));

      /* A linha abaixo realoca a fila com 1 nodo a menos a
         cada remocao, a estrutura fica mais dinamica porem
         refaz a alocacao de memoria a cada remocao. */
      //realocaFila(Fila, -1);
    }
  }
  
  return Frente;
} /* fim - removeDaFila/desenfileira */

int alteraNodo(Fp * const Fila, const int idNodo, const int novaPrio, 
    const bool (*_modo)(const int, const int))
{
  int i;
  
  if (Fila->nodo == NULL || Fila->indNodo == NULL)
    error(0, 0, "alteraNodo: a fila nao foi bem alocada.");
  else if (filaVazia(Fila))
    error(0, 0, "alteraNodo: fila vazia.");
  else
  {
    /* Checa se o ID existe na fila. */
    for (i = 0; i < Fila->qtdNodos; i++)
    {
      if (Fila->nodo[i].id == idNodo) { break; }
      if (i == Fila->qtdNodos - 1) 
      { 
        error(0, 0, "alteraNodo: este nodo nao existe."); 
        return EXIT_FAILURE;
      }
    }
    if (Fila->indNodo[idNodo] != INDEF && idNodo <= Fila->qtdMax - 1)
    {
      Fila->nodo[Fila->indNodo[idNodo]].pri = novaPrio;
      if (Fila->qtdNodos == 1) { return EXIT_SUCCESS; }
      
      /* Se o nodo esta na frente da fila usa-se
         heapifyDown pois heapifyUp faria nada. */
      if (idNodo == Fila->nodo[0].id)
        heapifyDown(Fila, 0, (*_modo));
      else
        heapifyUp(Fila, Fila->indNodo[idNodo], (*_modo));
        
      return EXIT_SUCCESS;
    }
    else
    {
      error(0, 0, "%s %d %s", "alteraNodo: nodo com ID", idNodo,
        "esta desativado ou nao foi inicializado."); 
      return EXIT_FAILURE;
    }
  }
  
  return EXIT_FAILURE;
} /* fim - alteraNodo */

void mostraFila(const Fp * const Fila)
{
  int i;
  
  if (filaVazia(Fila)) 
    error(0, 0, "mostraFila: fila vazia.");
  else
  {
    printf(" ID | Prioridade\n");
    printf(" ---------------\n");
    
    for (i = 0; i < Fila->qtdNodos; i++)
      printf(" %.2d %s %2.d\n", Fila->nodo[i].id, 
        "|", Fila->nodo[i].pri);
  }
} /* fim - mostraFila */

int desalocaFila(Fp *Fila)
{
  if (Fila->nodo != NULL && Fila->indNodo != NULL)
  {
    Fila->qtdNodos = INDEF; Fila->qtdMax = INDEF;
    free(Fila->indNodo); Fila->indNodo = NULL;
    free(Fila->nodo); Fila->nodo = NULL; 
    return EXIT_SUCCESS;
  }
  else
  {
    error(0, 0, "desalocaFila: desalocacao nao pode ser realizada."); 
    return EXIT_FAILURE;
  }
} /* fim - desalocaFila */
