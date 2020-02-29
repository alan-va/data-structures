#include <stdio.h>
#include "pilhas.h"

int main(void)
{
  Pilha pilhaTeste, *pilhaTestePtr; 
  int esc, qtd, num;

  pilhaTestePtr = &pilhaTeste;

  printf("Interface - Pilhas - Implementação em C\n\n");
  printf("[1] Inicializar pilha | [2] Empilhar | [3] Desempilhar\n");
  printf("        [4] Mostrar pilha | [5] Desalocar pilha\n");

  while (true)
  {
    printf("\n> "); scanf("%d", &esc);
    
    if (esc == 1)
    {
      printf("\nQuantidade de nodos: "); scanf("%d", &qtd);
      inicializaPilha(pilhaTestePtr, qtd); 
    }
    else if (esc == 2)
    {
      printf("\nInsira o numero: "); scanf("%d", &num);
      empilha(pilhaTestePtr, num);
    }
    else if (esc == 3)
    {
      desempilha(pilhaTestePtr); 
      mostraPilha(pilhaTestePtr); 
    }
    else if (esc == 4)
      mostraPilha(pilhaTestePtr);
    else if (esc == 5)
      desalocaPilha(pilhaTestePtr); 
    else
      printf("\nEscolha invalida.\n");
  }

  return 0;
}
