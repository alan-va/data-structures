/* Estruturas de dados - Fila com prioridades (TAD)
 *
 * Programa teste das funcoes se encontra em exemplo.c
 *
 * Todas as funcoes, com excecao de criaFila/criaFilaPtr que
 * apenas retornam uma variavel e crescente/decrescente que
 * sao funcoes de modo, mostram uma mensagem de erro caso
 * ocorra algum (ex: fila vazia, ponteiro invalido, erro de
 * alocacao de memoria, etc).
 * 
 * As funcoes inicializaFila, insereNaFila, alteraNodo e
 * desalocaFila retornam 0 caso nenhum erro ocorra e 1 se
 * ocorrer algum. */

#ifndef MODFP_H
#define MODFP_H

#include <stdbool.h>
#define INDEF -1

/* Define um nodo em uma fila com prioridades. Uma
   variavel NodoFp eh retornada por removeDaFila. */
typedef struct NodoDaFila
{
  int id; /* ID do nodo. */
  int pri; /* Prioridade do nodo. */
} NodoFp; /* -> Alias. */

/* Define uma fila com prioridades, usado por todas as
   funcoes de manipulacao de uma fila Fp e retornado
   pelas funcoes criaFila e criaFilaPtr. */
typedef struct FilaPrioritaria
{
  NodoFp *nodo; /* Array de nodos. */
  int *indNodo; /* Indice no heap. */
  int qtdNodos; /* nodos ativos. */
  int qtdMax;   /* qtd limite. */
} Fp; /* -> Alias. */

/* Um alias para um ponteiro de uma funcao do tipo bool com
   dois argumentos const int identificado por funcaoModo. */
typedef bool (*funcaoModo)(const int x, const int y);

/* As duas funcoes modo, usando 'crescente' o nodo frontal sempre tem
   a menor prioridade, usando 'decrescente' o contrario acontece. */
extern bool crescente(const int x, const int y);
extern bool decrescente(const int x, const int y);

/* Retorna uma variavel do tipo Fp com pointeiros nodo (NodoFp*)
   e indNodo (int*) apontando para NULL; qtdNodos e qtdMax = INDEF.*/
extern Fp criaFila(void);

/* Retorna uma variavel do tipo Fp* com pointeiros nodo (NodoFp*)
   e indNodo (int*) apontando para NULL; qtdNodos e qtdMax = INDEF.*/
extern Fp* criaFilaPtr(void);

/* Retorna TRUE se a fila estiver vazia e FALSE caso contrario. */
extern bool filaVazia(const Fp * const Fila);

/* Retorna TRUE se a fila estiver cheia e FALSE caso contrario. */
extern bool filaCheia(const Fp * const Fila);

/* Inicializa Fila com N nodos atraves de seu endereco de memoria. */
extern int inicializaFila(Fp *Fila, const int N);

/* Insere na Fila um nodo com (ID, Prioridade) = (idNodo, pri)
   usando uma funcaoModo (crescente/decrescente). */
extern int insereNaFila(Fp * const Fila, const int idNodo, 
    const int pri, const funcaoModo Modo);

/* Altera a prioridade de um nodo em Fila com ID idNodo para
   novaPrioridade usando uma funcaoModo(crescente/decrescente). */
extern int alteraNodo(Fp * const Fila, const int idNodo,
    const int novaPrioridade, const funcaoModo Modo);

/* Remove o nodo da frente da fila e o retorna. A funcao usa
   uma funcaoModo (crescente/decrescente). Caso ocorra algum
   erro (fila invalida ou vazia) a funcao retorna um nodo do
   tipo NodoFp com (ID, Prioridade) = (INDEF, INDEF). */
extern NodoFp removeDaFila(Fp *Fila, const funcaoModo Modo);

/* Mostra ID & Prioridade de cada nodo da fila. */
extern void mostraFila(const Fp * const Fila);

/* Desaloca os arrays nodo e indNodo e atribui INDEF a qtdNodos
   e qtdMax. Ao finalizar o uso de uma fila, sempre desaloque-a.*/
extern int desalocaFila(Fp *Fila);

#endif /* modfp.h */
