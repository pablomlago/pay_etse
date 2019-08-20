#include <stdlib.h>
#include "pila.h"


//////////////////////////////// ESTRUCTURAS DE DATOS

struct celdapila {
	tipoelempila elemento;
	struct celdapila *sig;
};


/////////////////////////////// FUNCIONES

void crear_pila(pila * P) {
	*P = NULL;
}

void destruir_pila(pila * P) {
	pila aux;
	aux = *P;
	while (aux != NULL) {
		aux = aux->sig;
		free(*P);
		*P = aux;
	}
}

unsigned es_vacia_pila(pila P) {
	return P == NULL;
}

tipoelempila tope(pila P) {
//	if (!es_vacia_pila(P)) {	/*si pila no vacía */
//		return P->elemento;
//	}
	return P->elemento;
}

void push(pila * P, tipoelempila E) {
	pila aux;
	aux = (pila) malloc(sizeof(struct celdapila));
	aux->elemento = E;
	aux->sig = *P;
	*P = aux;
}

void pop(pila * P) {
	pila aux;
	if (!es_vacia_pila(*P)) {	/*si pila no vacía */
		aux = *P;
		*P = (*P)->sig;
		free(aux);
	}
}

