#include <stdlib.h>
#include <stdio.h>

#include "abb.h"
#include "FuncionsPayETSE.h"

int main()
{
  //Variable para almacenar a opcion elixida polo usuario no menu
  char opcion = '\0';

  //Usaremos un arbol binario de busqueda para almacenar as transferencias
  abb aTransferencias;

  //Usaremos un grafo global para almacenar as transferencias
  grafo gTransferencias;

  //Inicializamos o arbol binario de busqueda
  crear_arbol(&aTransferencias);
  crear_grafo(&gTransferencias);

  lecturaDatos(&aTransferencias, &gTransferencias, "listaTransferencias.txt");

  do
  {
      //Permitimos ao usuario elixir o que desexa facer
      printf("\n");
      printf("Que desexas facer?\n");
      printf("l: Log in\n");
      printf("s: Sair do programa\n");
      printf("Opcion: ");
      scanf(" %c",&opcion);
      printf("\n");

      switch(opcion)
      {
        case 'l':
          login(&aTransferencias, &gTransferencias);
          break;
        case 's':
          escrituraDatos(&aTransferencias,"listaTransferencias.txt");
          sairPrograma(&aTransferencias, &gTransferencias);
          break;
        default:
          printf("Non se introduciu unha opcion valida\n");
          break;
      }

    } while(opcion != 's');

    return (EXIT_SUCCESS);
}
