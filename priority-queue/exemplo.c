/* Programa apenas para testar o TAD 'fila com prioridades'. */

#include <stdio.h>
#include "modfp.h" /* <----- */

/* Array de dois ponteiros de funcao do tipo funcaoModo. */
const funcaoModo modos[2] = {crescente, decrescente};

int main(void)
{
  int choice, id, prio, qtdNodos;
  funcaoModo modo = NULL;
  Fp Fprio = criaFila();
  char modoFila;
  
  /*Alternativa:
  Fp *FprioPtr; FprioPtr = criaFilaPtr();
  Sendo um ponteiro, sera passado como argumento
  como Fprio, sem o operador &.*/

  printf("TAD - Fila com Prioridades\n\n");
  printf("%s\n%s\n",
    "[0] Inicializar a fila | [1] Inserir na fila | [2] Alterar prioridade",
    "    [3] Mostrar a fila | [4] Desenfileirar | [5] Desalocar a fila");
  
  while (true)
  {
    printf("\n> "); scanf("%d", &choice);
    
    if (choice == 0)
    {
      printf("\nQuantidade inicial de nodos: "); 
      scanf("%d", &qtdNodos); inicializaFila(&Fprio, qtdNodos);
      
      /* c = crescente, d = decrescente */
      printf("\nModo da fila (c/d): "); scanf(" %c", &modoFila);
      
      while (modoFila != 'c' && modoFila != 'd')
        printf("\nModo inválido.\n");
      
      modo = (modoFila == 'c') ? modos[0] : modos[1];
    }
    else if (choice == 1)
    {
      printf("\nID: "); scanf("%d", &id);
      printf("Prioridade: "); scanf("%d", &prio);
      insereNaFila(&Fprio, id, prio, (*modo));
    }
    else if (choice == 2)
    {
      printf("\nID do nodo a ser alterado: "); scanf("%d", &id);
      printf("Nova prioridade: "); scanf("%d", &prio);
      alteraNodo(&Fprio, id, prio, (*modo));
    }
    else if (choice == 3)
    {
      printf("\n"); mostraFila(&Fprio); 
    }
    else if (choice == 4)
    {
      removeDaFila(&Fprio, (*modo));
      if (Fprio.qtdNodos > 0) { printf("\n"); }
      mostraFila(&Fprio); 
    }
    else if (choice == 5)
      desalocaFila(&Fprio);
    else
      printf("\nOpção inválida.\n");
  }

  return 0;
} /* fim - main */
