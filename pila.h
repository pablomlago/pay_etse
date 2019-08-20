#ifndef __PILA_LIB

#define __PILA_LIB

#define LONX 40

//////////////////////// ESTRUCTURAS DE DATOS

//Interfaz TAD pila
typedef struct celdapila *pila;	/*tipo opaco */


//////////////////////////////////////////INICIO PARTE MODIFICABLE
// Tipo de elemento de la pila
typedef struct
{
  char receptor[LONX];
  float cantidade;
  char concepto[LONX];
} tipoelempila;
//////////////////////////////////////////FIN PARTE MODIFICABLE

///////////////////////// FUNCIONES

/**
 * Fija a null el puntero
 * @param P
 */
void crear_pila(pila * P);

/**
 * Libera la memoria de cada celda de la pila
 * @param P
 */
void destruir_pila(pila * P);

/**
 * Comprueba si la pila está vacía
 * @return 1 si la pila está vacía y 0 en otro caso
 */
unsigned es_vacia_pila(pila P);

/**
 * Devuelve el elemento tope de la pila. No comprueba
 * si la pila está vacía, es posible que haya que llamar
 * a es_vacia_pila antes de llamar a estar función.
 * @param P
 * @return Tope de la pila
 */
tipoelempila tope(pila P);

/**
 * Introduce un nuevo elemento en el tope de la pila.
 * Importante, al introducir el elemento cambia el puntero
 * de la pila.
 * @param P
 * @param E
 */
void push(pila * P, tipoelempila E);

/**
 * Elimina de la pila el elemento tope.
 * Importante, al introducir el elemento cambia el puntero
 * de la pila.
 * @param P
 */
void pop(pila * P);

#endif				/* __PILA_LIB */
