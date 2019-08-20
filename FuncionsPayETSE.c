#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h"
#include "pila.h"

//Mostraremos mensaxes en diferentes correspondentes
//Para facer o programa mais visual
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

//FUNCIÓNS PRIVADAS AUXILIARES

//FUNCIÓNS AUXILIARES GRAFOS

int _calcularGradoEntrada(grafo gTransferencias, int posVertice)
{
  int gradoEntrada = 0;
  int i = 0;

  int numeroVertices = num_vertices(gTransferencias);

  for(i = 0; i < numeroVertices; i++)
  {
    if(i != posVertice)
    {
      if(son_adyacentes(gTransferencias, i, posVertice))
      {
        gradoEntrada++;
      }
    }
  }

  return gradoEntrada;
}

int _calcularGradoSaida(grafo gTransferencias, int posVertice)
{
  int gradoSaida = 0;
  int i = 0;

  int numeroVertices = num_vertices(gTransferencias);

  for(i = 0; i < numeroVertices; i++)
  {
    if(i != posVertice)
    {
      if(son_adyacentes(gTransferencias, posVertice, i))
      {
        gradoSaida++;
      }
    }
  }
  return gradoSaida;
}

void _crear_arco_vertices(grafo* gAmizades, tipovertice vertice1, tipovertice vertice2)
{
  int posEmisor = 0;
  int posReceptor = 0;

  posEmisor = posicion(*gAmizades, vertice1);
  posReceptor = posicion(*gAmizades, vertice2);

  crear_arco(gAmizades, posEmisor, posReceptor);
}

void _borrar_arco_vertices(grafo* gAmizades, tipovertice vertice1, tipovertice vertice2)
{
  int posEmisor = 0;
  int posReceptor = 0;

  posEmisor = posicion(*gAmizades, vertice1);
  posReceptor = posicion(*gAmizades, vertice2);

  borrar_arco(gAmizades, posEmisor, posReceptor);
}

void _imprimirGrafo(grafo G)
{
    tipovertice *VECTOR; //Para almacenar el vector de vertices del grafo
    int N; //numero de vertices del grafo

    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j;
    for (i = 0; i < N; i++)
    {
        //Imprimo el vertice
        printf("\tVertice(%d): %s\n", i, VECTOR[i].nomeUsuario);
        //Chequeo sus arcos
        for (j = 0; j < N; j++)
            if (son_adyacentes(G, i, j))
                printf("\t\t%s-->%s\n", VECTOR[i].nomeUsuario, VECTOR[j].nomeUsuario);
    }
}

//FUNCIONS ENTRADA E SAÍDA

//Función auxiliar para modularizar a entrada
//dos datos correspondentes a unha transferencia
void _introducirDatosTransferencia(tipoelempila *infTransferencia)
{
  printf("Introduce o nome do usuario receptor: ");
  scanf("%s", infTransferencia->receptor);
  printf("Introduce o concepto da transferencia: ");
  fflush(stdin);
  scanf(" %[^\t\n]", infTransferencia->concepto);
  do
  {
    printf("Introduce a cantidade a transferir: ");
    scanf("%f",&(infTransferencia->cantidade));

    //Evitamos que o usuario poda enviar unha cantidade nula ou negativa
    if(infTransferencia->cantidade <= 0)
    {
      printf(RED"\nDebes introducir unha cantidade > 0.\n\n"RESET);
    }
  } while(infTransferencia->cantidade <= 0);
}

//Pide o nome dun usuario por pantalla ao usuario
void _introducirNomeUsuario(tipoelem* informacion)
{
  printf("Introduce o nome do usuario: ");
  scanf("%s", informacion->nomeUsuario);
}

//Funcions para modularizar a saida de Datos
//Mostra a informacion dunha transferencia
void _mostrarDatosTransferencia(tipoelempila transferencia)
{
  printf("\tReceptor: %s\n", transferencia.receptor);
  printf("\tConcepto transferencia: %s\n", transferencia.concepto);
  printf("\tCantidade transferida: %.2f\n\t________________\n", transferencia.cantidade);
}

//Mostra a informacion dunha transferencia para un receptor particular
void _mostrarDatosReceptor(tipoelempila transferencia)
{
  printf("\tConcepto transferencia: %s\n", transferencia.concepto);
  printf("\tCantidade transferida: %.2f\n\t________________\n", transferencia.cantidade);
}

//Imprimimos o contido dunha pila de transferencias, a medida que a vaciamos
//e restauramos o seu contido orixinal, para o que se emprega unha pila auxiliar
void _imprimirPila(pila *p)
{
  tipoelempila temp;
  pila tempPila;

  //Creamos uha pila auxiliar
  crear_pila(&tempPila);

  while(!es_vacia_pila(*p))
  {
    temp = tope(*p);
    push(&tempPila, temp);
    pop(p);

    //Mostramos os datos da transferencia por pantalla
    _mostrarDatosTransferencia(temp);
  }

  while(!es_vacia_pila(tempPila))
  {
    temp = tope(tempPila);
    push(p,temp);
    pop(&tempPila);
  }

  //Destruimos a pila auxiliar antes de salir da funcion
  destruir_pila(&tempPila);
}

//Realiza un recorrido inorden do arbol binario de
//búsqueda mostrando en pantalla a información
//asociada a cada un dos seus nodos
void _inorden(abb* aTransferencias, abb pos)
{
    tipoelem E;

    if (!es_vacio(pos))
    {
        _inorden(aTransferencias ,izq(pos));

        //Informacion elemento raiz subarbol pos
        info(pos, &E);
        printf(GREEN"\nUsuario: %s\n"RESET, E.nomeUsuario);
        if(es_vacia_pila(E.pTransferencias))
        {
          printf(RED"\tNingunha transferencia rexistrada.\n"RESET);
        }
        else
        {
          _imprimirPila(&(E.pTransferencias));
          modificar(aTransferencias, E);
        }

        _inorden(aTransferencias, der(pos));
    }
}

void _inordenPilaGrafoLocal(abb* aTransferencias, abb pos)
{
    tipoelem E;

    if (!es_vacio(pos))
    {
        _inordenPilaGrafoLocal(aTransferencias ,izq(pos));

        //Informacion elemento raiz subarbol pos
        info(pos, &E);
        printf(GREEN"\nUsuario: %s\n"RESET, E.nomeUsuario);
        if(es_vacia_pila(E.pTransferencias))
        {
          printf(RED"\tNingunha transferencia rexistrada.\n"RESET);
        }
        else
        {
          _imprimirPila(&(E.pTransferencias));
          modificar(aTransferencias, E);
        }
        printf("\n\tGrafo local de transferencias: \n\n");
        _imprimirGrafo(E.gAmizades);

        _inordenPilaGrafoLocal(aTransferencias, der(pos));
    }
}

//FUNCIÓNS AUXILIARES ESTATÍSTICAS

//Obten as estatisticas das transferencias almacenadas na pila de transferencias
//dun usuario particular, a pila p non ha de ser vacia
void _obterEstatisticas(pila *p)
{
  tipoelempila temp;

  pila tempPila;
  pila pilaMaximos;

  //Almacenaremos a transferencia de maior cantidade
  tipoelempila maxPila;
  //Variable para almacenar o total de dineiro transferido
  float acumulado = 0;

  crear_pila(&tempPila);
  crear_pila(&pilaMaximos);

  while(!es_vacia_pila(*p))
  {
    temp = tope(*p);

    //Se este e o primeiro elemento que extraemos, ou se a cantidade transferida
    //no maximo temporal e menor que o da actual transferencia
    if(acumulado == 0 || maxPila.cantidade < temp.cantidade)
    {
      destruir_pila(&pilaMaximos);

      crear_pila(&pilaMaximos);
      //Gardamos o novo maximo
      maxPila = temp;

      //Engadimos este máximo temporal a pila de máximos
      push(&pilaMaximos, maxPila);
    }
    else if(maxPila.cantidade == temp.cantidade)
    {
      maxPila = temp;

      push(&pilaMaximos, maxPila);
    }
    //Actualizamos a cantidade de dineiro transferido
    acumulado += temp.cantidade;

    push(&tempPila, temp);
    pop(p);
  }
  while(!es_vacia_pila(tempPila))
  {
    temp = tope(tempPila);
    push(p,temp);
    pop(&tempPila);
  }

  //Mostramos o cantidade de dineiro transferido
  printf("1.-Cantidade total de dineiro transferido: %.2f.\n", acumulado);
  //MOstramos a transferencia de maior importe
  printf("2.-A/s transferencia/s emitida/s de maior cantidade son:\n");
  while(!es_vacia_pila(pilaMaximos))
  {
    temp = tope(pilaMaximos);
    _mostrarDatosTransferencia(temp);
    pop(&pilaMaximos);
  }

  destruir_pila(&tempPila);
  destruir_pila(&pilaMaximos);
}

//FUNCIÓNS AUXILIARES ELIMINACIÓN

//Recorre a pila buscando as transferencias a un receptor dado
//e eliminaas da pila de transerencias
void _eliminarReceptorPila(pila *p, tipoclave nomeReceptor)
{
  tipoelempila temp;
  pila tempPila;

  crear_pila(&tempPila);

  while(!es_vacia_pila(*p))
  {
    temp = tope(*p);
    //So gardamos na pila auxiliares as transferencias que non
    //van dirixidas ao receptor dado
    if(strcmp(temp.receptor,nomeReceptor) != 0)
    {
      push(&tempPila, temp);
    }
    pop(p);
  }
  while(!es_vacia_pila(tempPila))
  {
    temp = tope(tempPila);
    push(p, temp);
    pop(&tempPila);
  }

  destruir_pila(&tempPila);
}

//Anula as referencias que teñen como <receptor> un dado, das pilas de transferencias
//e dos grafos locais
void _eliminarTransferenciasPilaGrafo(abb* aTransferencias, abb pos, tipovertice vertice)
{
  tipoelem temp;

  //Comprobamos que o subarbol non sexa baleiro
  if (!es_vacio(pos))
  {
    info(pos, &temp);
    if(!es_vacia_pila(temp.pTransferencias))
    {
      //Borramos ao receptor dado da pila de transferencias do nodo
      _eliminarReceptorPila(&(temp.pTransferencias), vertice.nomeUsuario);
      //Comprobamos se dito usuario está no grafo local dun usuario particular
      if(existe_vertice(temp.gAmizades, vertice))
      {
        //En dito caso eliminámolo
        borrar_vertice(&(temp.gAmizades), vertice);
      }
      modificar(aTransferencias,temp);
    }
    //Realizamos un recorrido en preorde
    _eliminarTransferenciasPilaGrafo(aTransferencias, izq(pos), vertice);
    _eliminarTransferenciasPilaGrafo(aTransferencias, der(pos), vertice);
  }
}

//FUNCIÓNS AUXILIARES BÚSQUEDA RECEPTOR

//Busca nas transferencias dun usuario aquelas que teñen como receptor un dado
void _buscarReceptorPila(tipoelem* inf, tipoclave nomeReceptor, int* atopado)
{
  tipoelempila temp;
  pila tempPila;

  crear_pila(&tempPila);

  while(!es_vacia_pila(inf->pTransferencias))
  {
    temp = tope(inf->pTransferencias);
    push(&tempPila, temp);

    //Se o receptor dunha transferencia particular e o dado mostramos dita transferencia
    if(strcmp(temp.receptor,nomeReceptor) == 0)
    {
      printf(GREEN"Emisor: %s\n"RESET, inf->nomeUsuario);
      //No caso de atopar algunha transferencia a ese receptor, actualizamos a variable
      *atopado = 1;
      //Mostramos os datos da transferencia
      _mostrarDatosReceptor(temp);
    }

    pop(&(inf->pTransferencias));
  }
  while(!es_vacia_pila(tempPila))
  {
    temp = tope(tempPila);
    push(&(inf->pTransferencias), temp);
    pop(&tempPila);
  }

  destruir_pila(&tempPila);
}

//Mostra a información das transferencias recibidas por
//un <receptor> dado, gardado dentro do árbol binario
// de búsqueda. Recibe un punteiro a enteiro <atopado>
//para informar a función que a invoque que o <receptor>
//recibiu algunha transferencia.
void _buscarReceptor(abb* aTransferencias, abb pos, tipoclave receptor, int* atopado)
{
  tipoelem temp;

  if (!es_vacio(pos))
  {
    info(pos, &temp);
    //Se a pila de transferencias dun determinado non é baleira
    if(!es_vacia_pila(temp.pTransferencias))
    {
      //Buscamos nela ao receptor dado
      _buscarReceptorPila(&temp, receptor, atopado);
      //Actualizamos apropiadamente o nodo
      modificar(aTransferencias,temp);
    }
    //Realizamos un recorrido en preorde
    _buscarReceptor(aTransferencias, izq(pos), receptor, atopado);
    _buscarReceptor(aTransferencias, der(pos), receptor, atopado);
  }
}

//FUNCIÓNS AUXILIARES ESCRITURA DATOS EN ARQUIVO

//Almacena a información da pila de transferencias dun nodo no arquivo
void _imprimirPilaFicheiro(FILE* arquivo, tipoelem* info)
{
  //Precisaremos dous elementos de información auxiliares
  tipoelempila temp;
  pila tempPila;

  //Creamos uha pila auxiliar
  crear_pila(&tempPila);

  //Vaciamos a pila de transferencias dun nodo gardando a súa informacion nunha pila auxiliar
  while(!es_vacia_pila(info->pTransferencias))
  {
    temp = tope(info->pTransferencias);
    push(&tempPila, temp);
    pop(&(info->pTransferencias));
  }

  //Vaciamos a pila auxiliar na pila de transferencias dun nodo do arbol
  while(!es_vacia_pila(tempPila))
  {
    temp = tope(tempPila);
    //Gardamos a informacion de cada unha das transferencias no arquivo
    fprintf(arquivo, "%s %s %.2f %s\n", info->nomeUsuario, temp.receptor, temp.cantidade, temp.concepto);
    push(&(info->pTransferencias),temp);
    pop(&tempPila);
  }

  //Liberamos a memoria asociada a pila auxiliar
  destruir_pila(&tempPila);
}

int _existeReceptor(grafo gAmizades, tipoclave nomeUsuario)
{
  int pos = 0;
  int gradoEntrada = 0;

  tipovertice verticeUsuario;

  strcpy(verticeUsuario.nomeUsuario, nomeUsuario);

  pos = posicion(gAmizades, verticeUsuario);
  gradoEntrada = _calcularGradoEntrada(gAmizades, pos);

  return gradoEntrada;
}

//FUNCIÓNS AUXILIARES ESCRITURA

//Realiza un recorrido inorden gardando a informacion de cada un dos nodos no arquivo
void _escrituraInorden(FILE* arquivo, abb* aTransferencias, abb pos)
{
  //Elemento temporal para almacenar a información de cada elemento da árbol
  tipoelem E;

  //Variable bandeira para saber se un usuario non recibiu ningunha transferencias
  //Empregada no caso de que o usuario tampouco realizara ningunha transferencia
  int atopado = 0;

  //Realizamos un recorrido inorden recursivo no arbol
  if (!es_vacio(pos))
  {
      _escrituraInorden(arquivo, aTransferencias ,izq(pos));

      //Informacion elemento raiz subarbol pos
      info(pos, &E);
      //Comprobamos se o usuario realizou algunha transferencia
      if(es_vacia_pila(E.pTransferencias))
      {
        //Comprobamos se o usuario dado recibiu algunha transferencia
        atopado = _existeReceptor(E.gAmizades, E.nomeUsuario);
        //No caso de non recibir ningunha transferencia imprimirémolo
        //dunha forma particular
        if(!atopado)
        {
          fprintf(arquivo, "%s %s\n", E.nomeUsuario, "*");
        }
      }
      else
      {
        //Imprimimos a pila, que almacena a informacion das transferencias realizadas
        //polo usuario correspondente a un nodo do arbol
        _imprimirPilaFicheiro(arquivo, &E);
        //Actualizamos o nodo apropiadamente
        modificar(aTransferencias,E);
      }

      _escrituraInorden(arquivo, aTransferencias, der(pos));
  }
}

//FUNCIÓNS PÚBLICAS

void imprimirUsuarios(abb* aTransferencias)
{
  _inordenPilaGrafoLocal(aTransferencias, *aTransferencias);
}

void imprimirGrafoGlobal(grafo gTransferencias)
{
  printf("Grafo global de transferencias: \n");
  _imprimirGrafo(gTransferencias);
}

void obterEstatisticasGlobais(grafo gTransferencias)
{
  //Serviranos para calcular o número medio de amigos
  int numeroAmigosAcumulado = 0;

  //Variables temporais para almacenar os grados de entrada e saida dun vertice particular
  int gradoSaida = 0;
  int gradoEntrada = 0;

  //Gardaremos os máximos dos grados de entrada e saída
  int maxGradoSaida = 0;
  int maxGradoEntrada = 0;

  //Variable contador
  int i = 0;

  //Número de vértices do grafo global
  int numeroVertices = num_vertices(gTransferencias);
  //Obtemos o array de vértices do grafo global
  tipovertice* vectorVertices = array_vertices(gTransferencias);

  //Calculamos os grados de entrada e saida máxmos
  for(i = 0; i < numeroVertices; i++)
  {
    gradoSaida = _calcularGradoSaida(gTransferencias, i);
    gradoEntrada = _calcularGradoEntrada(gTransferencias, i);

    numeroAmigosAcumulado += gradoSaida + gradoEntrada;

    if(gradoSaida >= maxGradoSaida)
    {
      maxGradoSaida = gradoSaida;
    }

    if(gradoEntrada >= maxGradoEntrada)
    {
      maxGradoEntrada = gradoEntrada;
    }
  }

  printf("Numero de usuarios rexistrados: %d\n", numeroVertices);
  printf("Número medio de amigos por usuario: %f\n", (float)numeroAmigosAcumulado/(float)numeroVertices);

  printf("O/s usuario/s que emiten transferencias a un maior número de usuarios son:\n");

  //Mostramos os usuarios co grado de saida maximo
  for(i = 0; i < numeroVertices; i++)
  {
    gradoSaida = _calcularGradoSaida(gTransferencias, i);

    if(gradoSaida == maxGradoSaida)
    {
      printf("Nome: %s\tUsuarios: %d\n", vectorVertices[i].nomeUsuario, maxGradoSaida);
    }
  }

  printf("O/s usuario/s con reciben transferencias dun maior número de usuarios son: \n");

  //MOstramos os usuarios co grado de entrada máximo
  for(i = 0; i < numeroVertices; i++)
  {
    gradoEntrada = _calcularGradoEntrada(gTransferencias, i);

    if(gradoEntrada == maxGradoEntrada)
    {
      printf("Nome: %s\tUsuarios: %d\n", vectorVertices[i].nomeUsuario, maxGradoEntrada);
    }
  }
}

void usuariosMaisActivos(grafo gTransferencias)
{
  //Gardaremos a actividade maxima
  int actividadeMaxima = 0;
  //Variable para gardar a actividade dun vertice particular
  int actividade = 0;

  //numero de vértices do grafo global
  int numeroVertices = num_vertices(gTransferencias);
  //Gardamos nun array os vértices do grafo de transferencias global
  tipovertice* vertices = array_vertices(gTransferencias);

  //Variable global
  int i = 0;

  for(i = 0; i < numeroVertices; i++)
  {
    actividade = _calcularGradoSaida(gTransferencias, i) + _calcularGradoEntrada(gTransferencias, i);

    if(actividade > actividadeMaxima)
    {
      actividadeMaxima = actividade;
    }
  }

  printf("Usuario/s con actividade %d:\n", actividadeMaxima);

  //Mostramos os usuarios coa actividade maxima
  for(i = 0; i < numeroVertices; i++)
  {
    actividade = _calcularGradoSaida(gTransferencias, i) + _calcularGradoEntrada(gTransferencias, i);

    if(actividade == actividadeMaxima)
    {
      printf("\tNome: %s\n", vertices[i].nomeUsuario);
    }
  }
}

//ELimina os datos dun usario do grafo global, o arbol de transferencias e os grafos locais
void eliminarUsuario(abb* aTransferencias, grafo* gTransferencias, tipoclave usuario)
{
  //Elementos temporais de información
  tipoelem temp;
  tipovertice vertice;

  //Comprobamos se o árbol binario de búsqueda ten algún nodo
  if(es_vacio(*aTransferencias))
  {
    printf(RED"Ningun usuario rexistrado.\n"RESET);
  }
  else
  {
    //Comprobamos se o nome do usuario a eliminar xa foi pasado como parámetro
    if(strcmp(usuario,""))
    {
      strcpy(temp.nomeUsuario, usuario);
    }
    else
    {
      //De non ser asi pedimosllo ao usuario
      _introducirNomeUsuario(&temp);
    }
    strcpy(vertice.nomeUsuario, temp.nomeUsuario);

    //Comprobamos se está rexistrado no árbol
    if(es_miembro(*aTransferencias,temp))
    {
      //Eliminamos o usuario do grafo de transferencias global
      borrar_vertice(gTransferencias, vertice);
      //De estar rexistrado, eliminamos todas as transferencias asociadas ao mesmo
      _eliminarTransferenciasPilaGrafo(aTransferencias,*aTransferencias, vertice);
      //E eliminamos o seu rexistro no árbol
      suprimir(aTransferencias,temp);

      printf(GREEN"Eliminacion realizada con exito.\n"RESET);
    }
    else
    {
      printf(RED"O usuario %s non esta rexistado.\n"RESET,temp.nomeUsuario);
    }
  }
}


//Introduce os datos dunha nova transferencia
//no arbol binario de búsqueeda
void introducirTransferencia(abb* aTransferencias, grafo* gTransferencias, tipoelem informacionEmisor)
{
  //tipoelem infIntroducir;
  tipoelem informacionReceptor;

  tipoelempila transferencia;

  tipovertice verticeEmisor;
  tipovertice verticeReceptor;

  //Pedimos ao usuario os datos da transferencia
  _introducirDatosTransferencia(&transferencia);

  strcpy(informacionReceptor.nomeUsuario,transferencia.receptor);

  strcpy(verticeEmisor.nomeUsuario, informacionEmisor.nomeUsuario);
  strcpy(verticeReceptor.nomeUsuario, informacionReceptor.nomeUsuario);

  //Comprobamos se o emisor da transferencia está rexistrado
  if(es_miembro(*aTransferencias, informacionEmisor))
  {
    //No caso de estar rexistrado, actualizamos os seus datos
    //cos detalles da nova transferencia
    buscar_nodo(*aTransferencias, informacionEmisor.nomeUsuario, &informacionEmisor);
    //Insertamos a nova transferencia
    push(&(informacionEmisor.pTransferencias), transferencia);

    //Comprobamos se existe o vértice do receptor no arbol local do emisor
    if(!existe_vertice(informacionEmisor.gAmizades, verticeReceptor))
    {
      //De non existir insertámolo no árbol local
      insertar_vertice(&(informacionEmisor.gAmizades), verticeReceptor);
    }
    //E creamos o arco entre ambos vértices
    _crear_arco_vertices(&(informacionEmisor.gAmizades), verticeEmisor, verticeReceptor);

    //Actualizamos o árbol apropiadamente
    modificar(aTransferencias, informacionEmisor);
  }
  else
  {
    //Se non está rexistrado creamos o seu vértice correspondente no grafo global
    insertar_vertice(gTransferencias, verticeEmisor);

    //Se non está rexistrado, insertamos os seus datos e os
    //da transferencia no arbol
    crear_pila(&(informacionEmisor.pTransferencias));
    //Introducimos a transferencia na pila
    push(&(informacionEmisor.pTransferencias),transferencia);

    //Creamos o grafo local do emisor
    crear_grafo(&(informacionEmisor.gAmizades));

    //Introducimos os vertices de emisor e receptor no árbol local
    insertar_vertice(&(informacionEmisor.gAmizades), verticeEmisor);
    insertar_vertice(&(informacionEmisor.gAmizades), verticeReceptor);

    //Cremos o arco entre emisor e receptor
    _crear_arco_vertices(&(informacionEmisor.gAmizades), verticeEmisor, verticeReceptor);

    //Introducimos este elemento no árbol
    insertar(aTransferencias,informacionEmisor);
  }
  //Comprobamos se o receptor da transferencia está rexistrado
  if(es_miembro(*aTransferencias,informacionReceptor))
  {
    //No caso de estar rexistrado, actualizamos os seus datos
    //cos detalles da nova transferencia
    buscar_nodo(*aTransferencias, informacionReceptor.nomeUsuario, &informacionReceptor);
    //Creamos o arco entre emisor e receptor no grafo global
    _crear_arco_vertices(gTransferencias, verticeEmisor, verticeReceptor);

    //Comprobamos se existe o vértice do receptor no arbol local do receptor
    if(!existe_vertice(informacionReceptor.gAmizades, verticeEmisor))
    {
      //De non existir insertámolo no árbol local
      insertar_vertice(&(informacionReceptor.gAmizades), verticeEmisor);
    }
    _crear_arco_vertices(&(informacionReceptor.gAmizades), verticeEmisor, verticeReceptor);

    //Actualizamos o árbol apropiadamente
    modificar(aTransferencias, informacionReceptor);
  }
  else
  {
    //De non existir creamos o vértice no grafo global
    insertar_vertice(gTransferencias, verticeReceptor);
    //E asociamos os vértices de emisor e receptor
    _crear_arco_vertices(gTransferencias, verticeEmisor, verticeReceptor);
    //Se non está, insertamos os seus datos no árbol
    crear_pila(&(informacionReceptor.pTransferencias));

    crear_grafo(&(informacionReceptor.gAmizades));

    //Introducimos os vertices de emisor e receptor no árbol local
    insertar_vertice(&(informacionReceptor.gAmizades), verticeEmisor);
    insertar_vertice(&(informacionReceptor.gAmizades), verticeReceptor);

    //Cremos o arco entre emisor e receptor
    _crear_arco_vertices(&(informacionEmisor.gAmizades), verticeEmisor, verticeReceptor);

    //Insertamos o elemento no árbol
    insertar(aTransferencias,informacionReceptor);
  }

}

//Busca un usuario dado no árbol binario de búsqueeda
//e imprimie os seus datos e da súa última transferencias
//realizada, se existe
void consultaPorUsuario(abb* aTransferencias, tipoelem informacion)
{
  //Comprobamos se o árbol binario de búsqueda ten algún nodo
  if(es_vacio(*aTransferencias))
  {
    //De ser baleiro, notificámosllo ao usuario
    printf(RED"Non hai informacion rexistrada.\n"RESET);
  }
  else
  {
    //Comprobamos se está rexistrado no árbol
    if(es_miembro(*aTransferencias,informacion))
    {
      //De estar rexistrado no arbol, mostramos a súa información
      buscar_nodo(*aTransferencias, informacion.nomeUsuario, &informacion);

      printf(GREEN"\nNome usuario: %s\n"RESET, informacion.nomeUsuario);
      //Comrpobamos se a pila é baleira
      if(es_vacia_pila(informacion.pTransferencias))
      {
         printf(RED"\tNingunha transferencia rexistrada.\n"RESET);
      }
      else
      {
        //De non ser baleira imprimimos as transferencias contidas nela
         _imprimirPila(&(informacion.pTransferencias));
      }
      //Actualizamos o árbol apropiadamente
      modificar(aTransferencias, informacion);
    }
    else
    {
      printf(RED"O usuario %s non esta rexistrado.\n"RESET,informacion.nomeUsuario);
    }

  }
}

//Busca a un usuario introducido polo usuario e mostra as transerencias
//que recibiu
void consultaPorReceptor(abb* aTransferencias, tipoelem informacion)
{
  //Variable para determinar se o usuario dado recibiu algunha transferencia
  int atopado = 0;

  //Comprobamos se o árbol binario de búsqueda ten algún nodo
  if(es_vacio(*aTransferencias))
  {
      printf(RED"Ningunha transferencia rexistrada.\n"RESET);
  }
  else
  {
    //Comprobamos se está rexistrado no árbol
    if(es_miembro(*aTransferencias, informacion))
    {
      //Recorreremos o árbol buscando as aTransferencias
      //das cales é receptor e mostramos a información
      //das mesmas
      _buscarReceptor(aTransferencias, *aTransferencias, informacion.nomeUsuario, &atopado);
      if(!atopado)
      {
        //Se non hai notificámosllo ao usuario
        printf(RED"O usuario %s non recibiu ningunha transferencia.\n"RESET, informacion.nomeUsuario);
      }
    }
    //Sería redundante nesta versión
    else
    {
      printf(RED"O usuario %s non está rexistrado.\n"RESET, informacion.nomeUsuario);
    }
  }
}

//Mostra as estatisticas dun usuario: a total de dineiro trasnferido, e a
//transferencia de maior cantidade
void obterEstatisticasUsuario(abb* aTransferencias, tipoelem informacion)
{
  //Comprobamos se o arbol e baleiro
  if(es_vacio(*aTransferencias))
  {
    printf(RED"Ningun usuario rexistado.\n"RESET);
  }
  else
  {
    //Comprobamos se o usuario está no arbol
    if(es_miembro(*aTransferencias, informacion))
    {
      //Obtemos a informacion do usuario
      buscar_nodo(*aTransferencias, informacion.nomeUsuario, &informacion);
      //Se realizou algunha transferencia
      if(!es_vacia_pila(informacion.pTransferencias))
      {
        //Mostramos as estatisticas
        printf(GREEN"\nEstatisticas de %s:\n"RESET, informacion.nomeUsuario);
        //Extraemos a información da pila de transferencias asociada ao usuario
        _obterEstatisticas(&(informacion.pTransferencias));

        //Modificamos a pila contida no nodo apropiadamente
        modificar(aTransferencias, informacion);
      }
      else
      {
        printf(RED"O usuario %s non realizou ningunha transferencia.\n"RESET, informacion.nomeUsuario);
      }
    }
    else
    {
      printf(RED"O usuario %s non esta rexistado.\n"RESET, informacion.nomeUsuario);
    }
  }
}

//Elimina todas as referencias a relación entre o usuario dado e un amigo do mesmo
void borrarAmigo(abb* aTransferencias, grafo* gTransferencias, tipoelem informacion)
{
  //Elemento de información auxiliares
  tipoelem informacionReceptor;

  tipovertice verticeEmisor;
  tipovertice verticeReceptor;

  //Imprimimos o grafo local do usuario que vai borrar un dos seus amigos
  _imprimirGrafo(informacion.gAmizades);
  //Pedimos ao usuario o nome do amigo que desexa borrar
  _introducirNomeUsuario(&informacionReceptor);

  //Debemos comprobar que o usuario non se está eliminando a si mesmo
  if(strcmp(informacion.nomeUsuario, informacionReceptor.nomeUsuario))
  {
    //Comprobamos se dito usuario está rexistrado no árbol
    if(es_miembro(*aTransferencias, informacionReceptor))
    {
      //Obtemos a información asociada ao usuario que deixara de ser amigo
      buscar_nodo(*aTransferencias, informacionReceptor.nomeUsuario, &informacionReceptor);

      //Inicializamos apropiadamente os vertices
      strcpy(verticeEmisor.nomeUsuario, informacion.nomeUsuario);
      strcpy(verticeReceptor.nomeUsuario, informacionReceptor.nomeUsuario);

      //Comrpobamos se existe unha relación de amistade entre ambos usuarios
      if(existe_vertice(informacion.gAmizades, verticeReceptor))
      {
        //No caso de existir eliminamos as transferencias que existen entre eles
        _eliminarReceptorPila(&(informacion.pTransferencias), informacionReceptor.nomeUsuario);
        _eliminarReceptorPila(&(informacionReceptor.pTransferencias), informacion.nomeUsuario);

        //Eliminamos as relacións entre ambos usuarios no grafo global
        _borrar_arco_vertices(gTransferencias, verticeEmisor, verticeReceptor);
        _borrar_arco_vertices(gTransferencias, verticeReceptor, verticeEmisor);

        //Eliminamos os respectivos vertices nos grafos locais
        borrar_vertice(&(informacion.gAmizades), verticeReceptor);
        borrar_vertice(&(informacionReceptor.gAmizades), verticeReceptor);

        //Imprimimos o grafo do usuario e o grafo global actualizados
        _imprimirGrafo(informacion.gAmizades);
        _imprimirGrafo(*gTransferencias);

        //Actualizamos os elementos do arbol apropiadamente
        modificar(aTransferencias, informacion);
        modificar(aTransferencias, informacionReceptor);
      }
      else
      {
        printf(RED"%s e %s non son amigos.\n", informacion.nomeUsuario, informacionReceptor.nomeUsuario);
      }
    }
    else
    {
      printf(RED"O usuario %s non está rexistrado.\n"RESET, informacionReceptor.nomeUsuario);
    }
  }
  else
  {
    printf(RED"Para darse de baixa débese empregar a opción (e).\n"RESET);
  }
}

//Saimos do programa mostrando o contido do árbol,
//e liberando a memoria asociada ao mesmo
void sairPrograma(abb* aTransferencias, grafo* gTransferencias)
{
  _inorden(aTransferencias, *aTransferencias);
  destruir_arbol(aTransferencias);
  borrar_grafo(gTransferencias);
}

//Funcions para a lectura dos datos de transferencias almacenados nun ficheiro
void lecturaDatos(abb* aTransferencias, grafo* gTransferencias, char* ficheiro)
{
  //Punteiro que gardará a direción do ficheiro onde se almacenan as transferencias
  FILE* arquivo = NULL;

  tipoelem informacion;
  tipoelem informacionReceptor;

  tipovertice verticeGrafoEmisor;
  tipovertice verticeGrafoReceptor;

  //Variable bandeira para distinguir o caso no que un usuario está rexistrado
  //pero non realizou nin recibiu ningunha transferencia
  int existeReceptor = 0;

  tipoelempila transferencia;

  //Abrimos o ficheiro en modo lectura
  arquivo = fopen(ficheiro,"r");

  //Comprobamos se o arquivo foi aberto correctamente
  if(arquivo != NULL)
  {
    printf(GREEN"O arquivo foi aberto adecuadamente.\n"RESET);

    //Leemos a informacion da primeira liña e gardámola nas estruturas correspondentes
    fscanf(arquivo, "%s %s", informacion.nomeUsuario, transferencia.receptor);


    //Mentras non chegamos o final do ficheiro
    while(!feof(arquivo))
    {
      //Comprobamos se é necesario seguir lendo o contido da liña
      existeReceptor = strcmp(transferencia.receptor, "*");
      if(existeReceptor)
      {
          fscanf(arquivo, "%f %[^\t\n]", &transferencia.cantidade, transferencia.concepto);
      }

      //Copiamos a información nas estruturas correspondentes
      strcpy(informacionReceptor.nomeUsuario,transferencia.receptor);
      strcpy(verticeGrafoEmisor.nomeUsuario, informacion.nomeUsuario);
      strcpy(verticeGrafoReceptor.nomeUsuario, transferencia.receptor);

      //Comprobamos se o emisor esta rexistrado (asumimos que se xa está rexistrado existe un receptor)
      if(es_miembro(*aTransferencias,informacion))
      {
        //No caso de estar rexistrado, actualizamos os seus datos
        //cos detalles da nova transferencia
        buscar_nodo(*aTransferencias, informacion.nomeUsuario, &informacion);
        //Engadimos a última transferencia realizada
        push(&(informacion.pTransferencias),transferencia);

        //Comprobamos se o vértice do receptor non está no grafo local do emisor
        if(!existe_vertice(informacion.gAmizades, verticeGrafoReceptor))
        {
          insertar_vertice(&(informacion.gAmizades), verticeGrafoReceptor);
        }
        //Creamos un arco no seu grafo local representando a transferencia
        _crear_arco_vertices(&(informacion.gAmizades), verticeGrafoEmisor, verticeGrafoReceptor);

        //Actualizamos o árbol apropiadamente
        modificar(aTransferencias, informacion);
      }
      else
      {
        //De non existir, introducimos o vértice correspondente ao emisor
        //no grafo global
        insertar_vertice(gTransferencias, verticeGrafoEmisor);

        //Creamos a pila de transferencias
        crear_pila(&(informacion.pTransferencias));
        //Creamos o grafo local
        crear_grafo(&(informacion.gAmizades));
        //Introducimos no mesmo o vértice correspondente ao emisor
        insertar_vertice(&(informacion.gAmizades), verticeGrafoEmisor);

        //Se non está rexistrado, insertamos os seus datos e os
        //da transferencia no arbol
        if(existeReceptor)
        {
          //Introducimos a informacion da transferencia
          push(&(informacion.pTransferencias), transferencia);

          //Insertamos o grafo correspondente ao receptor
          insertar_vertice(&(informacion.gAmizades), verticeGrafoReceptor);
          //Unimos ambos vértices representando así a relación creada pola transferencia
          _crear_arco_vertices(&(informacion.gAmizades), verticeGrafoEmisor, verticeGrafoReceptor);
        }
        //Introducimos este elemento no árbol
        insertar(aTransferencias, informacion);
      }
      //Comprobamos se hai un receptor
      if(existeReceptor)
      {
        //Comprobamos se este está no árbol
        if(es_miembro(*aTransferencias, informacionReceptor))
        {
          //Creamos o arco de emisor a receptor no grafo global
          _crear_arco_vertices(gTransferencias, verticeGrafoEmisor, verticeGrafoReceptor);

          //Obtemos a informacion asociada a ese receptor
          buscar_nodo(*aTransferencias, informacionReceptor.nomeUsuario, &informacionReceptor);

          //Comprobamos se o vértice correspondente ao emisor existe no grafo local do receptor
          if(!existe_vertice(informacionReceptor.gAmizades, verticeGrafoEmisor))
          {
            insertar_vertice(&(informacionReceptor.gAmizades), verticeGrafoEmisor);
          }
          //Creamos o arco entre emisor e receptor
          _crear_arco_vertices(&(informacionReceptor.gAmizades), verticeGrafoEmisor, verticeGrafoReceptor);

          //Actualizamos o elemento do árbol apropiadamente
          modificar(aTransferencias, informacion);
        }
        //De non estar rexistrado no árbol o receptor
        else
        {
          //Creamos no grafo global o vértice correspondente ao receptor
          insertar_vertice(gTransferencias, verticeGrafoReceptor);
          //E o arco entre os vértices de emisor e receptor
          _crear_arco_vertices(gTransferencias, verticeGrafoEmisor, verticeGrafoReceptor);

          //Creamos a súa pila de transferencias baleira
          crear_pila(&(informacionReceptor.pTransferencias));
          //Así como o seu grafo local
          crear_grafo(&(informacionReceptor.gAmizades));

          //Insertamos os vértices de emisor e receptor no grafo local e cremaos o arco entre ambos
          insertar_vertice(&(informacionReceptor.gAmizades), verticeGrafoReceptor);
          insertar_vertice(&(informacionReceptor.gAmizades), verticeGrafoEmisor);

          _crear_arco_vertices(&(informacionReceptor.gAmizades), verticeGrafoEmisor, verticeGrafoReceptor);

          //E insertamos esta informacion no arbol de transferencias
          insertar(aTransferencias, informacionReceptor);
        }
      }
      //Proseguimos a lectura dos datos do ficheiro
      fscanf(arquivo, "%s %s", informacion.nomeUsuario, transferencia.receptor);
    }
    //Pechamos arquivo e comprobamos que esta operacion se realizou adecuadamente
    if(fclose(arquivo))
    {
      printf(RED"O arquivo non foi pechado adecuadamente.\n"RESET);
    }
    else
    {
      printf(GREEN"O arquivo foi pechado adecuadamente.\n"RESET);
    }
  }
  else
  {
    printf(RED"Non se logrou abrir o arquivo.\n" RESET);
  }
}

//Función para gardar os datos de transferencias nun ficheiro
void escrituraDatos(abb* aTransferencias, char* ficheiro)
{
  //Punteiro que gardará a direción do ficheiro onde se almacenan as transferencias
  FILE* arquivo = NULL;
  //Abrimos o arquivo en modo escritura
  arquivo = fopen(ficheiro, "w");

  //Comprobamos se o abrimos correctamente
  if(arquivo != NULL)
  {
    printf(GREEN"O arquivo foi aberto adecuadamente.\n"RESET);
    //Chamamos a función que imprimirá as transferencias gardadas en cada un dos nodos no arquivo
    _escrituraInorden(arquivo, aTransferencias, *aTransferencias);
    //Pechamos o arquivo comprobando que esta operacion se realizou con éxito
    if(fclose(arquivo))
    {
      printf(RED"O arquivo non foi pechado adecuadamente.\n"RESET);
    }
    else
    {
      printf(GREEN"O arquivo foi pechado adecuadamente.\n"RESET);
    }
  }
  else
  {
    printf(RED"NOn se logrou abrir o arquivo.\n"RESET);
  }
}

//Menú de usuario
void menuUsuario(abb* aTransferencias, grafo* gTransferencias, tipoelem informacion)
{
  char opcion = '\0';

  do
  {
      //Permitimos ao usuario elixir o que desexa facer
      printf("\n");
      printf("Que desexas facer?\n");
      printf("a: Introducir transferencia\n");
      printf("b: Consultar transferencias emitidas\n");
      printf("c: Consultar transferencias recibidas\n");
      printf("d: Estatísticas de usuario\n");
      printf("e: Darse de baixa na aplicacion\n");
      printf("f: Borrar amigo\n");
      printf("s: Sair do menu de usuario\n");
      printf("Opcion: ");
      scanf(" %c",&opcion);
      printf("\n");

      switch(opcion)
      {
        case 'a':
          introducirTransferencia(aTransferencias, gTransferencias, informacion);
          break;
        case 'b':
          consultaPorUsuario(aTransferencias, informacion);
          break;
        case 'c':
          consultaPorReceptor(aTransferencias, informacion);
          break;
        case 'd':
          obterEstatisticasUsuario(aTransferencias, informacion);
          break;
        case 'e':
          eliminarUsuario(aTransferencias, gTransferencias, informacion.nomeUsuario);
          break;
        case 'f':
          borrarAmigo(aTransferencias, gTransferencias, informacion);
          break;
        case 's':
          break;
        default:
          printf("Non se introduciu unha opcion valida\n");
          break;
      }

    } while(opcion != 'e' && opcion != 's');
}

//Menú de administrador
void menuAdministrador(abb* aTransferencias, grafo* gTransferencias)
{
  char opcion = '\0';

  do
  {
      //Permitimos ao usuario elixir o que desexa facer
      printf("\n");
      printf("Que desexas facer?\n");
      printf("a: Imprimir usuarios\n");
      printf("b: Imprimir grafo global\n");
      printf("c: Estatísticas globais\n");
      printf("d: Usuario/s máis activo/s\n");
      printf("e: Dar de baixa un usuario\n");
      printf("s: Sair do menú de administrador\n");
      printf("Opcion: ");
      scanf(" %c",&opcion);
      printf("\n");

      switch(opcion)
      {
        case 'a':
          imprimirUsuarios(aTransferencias);
          break;
        case 'b':
          imprimirGrafoGlobal(*gTransferencias);
          break;
        case 'c':
          obterEstatisticasGlobais(*gTransferencias);
          break;
        case 'd':
          usuariosMaisActivos(*gTransferencias);
          break;
        case 'e':
          eliminarUsuario(aTransferencias, gTransferencias, "");
          break;
        case 's':
          break;
        default:
          printf("Non se introduciu unha opcion valida\n");
          break;
      }

    } while(opcion != 's');
}

//Menú global para iniciar sesión
void login(abb* aTransferencias, grafo* gTransferencias)
{
  //Elemento de información auxiliar
  tipoelem informacion;

  //Pedimos ao usuario que introduza o tipo de acceso
  printf("Introduce o tipo de acceso: ");
  scanf("%s", informacion.nomeUsuario);

  //Comprobamos se o acceso se fixo como administrador
  if(strcmp(informacion.nomeUsuario,"admin"))
  {
    //Se o usuario introducido xa existe entramos no seu menú
    if(es_miembro_clave(*aTransferencias, informacion.nomeUsuario))
    {
      menuUsuario(aTransferencias, gTransferencias, informacion);
    }
    //Noutro caso, damos ao usuario a posibilidade de darse de alta na aplicacion
    //facendo unha transferencia
    else
    {
      //Introducimos a transferencia correspondente ao novo receptor
      introducirTransferencia(aTransferencias, gTransferencias, informacion);
      menuUsuario(aTransferencias, gTransferencias, informacion);
    }
  }
  //Se o usuario introduciu "admin" entramos no menú de administrador
  else
  {
    menuAdministrador(aTransferencias, gTransferencias);
  }
}
