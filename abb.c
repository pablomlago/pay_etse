#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Importar aqui abb.h permite no repetir la definicion de
// tipoelem. Si no lo hiciesemos tendriamos que copiarla
// en la implementacion.
#include "abb.h"

///////////////////////// ESTRUCTURAS DE DATOS

struct celda {
	tipoelem info;
	struct celda *izq, *der;
};

//////////////////////// FUNCIONES


/////////////////////////// INICIO PARTE MODIFICABLE

/*
 * Extraer la clave de una celda
 */
tipoclave _clave_elem(tipoelem * E){
	return E->nomeUsuario;
}

/* Esta funcion puente nos permite modificar el tipo de
 * de datos del TAD sin tener que cambiar todas las
 * comparaciones del resto de la biblioteca y en su lugar
 * cambiando solo esta.
 */
int _comparar_claves(tipoclave cl1, tipoclave cl2){
	int comp = strcmp(cl1,cl2);
	return comp == 0 ? 0 : comp > 0 ? 1 : -1;
}

/*
 * Si tipoelem tiene alguna estructura que necesite
 * destruirse ha de hacerse aqui. El uso de esta funcion
 * permite hacer mas eficiente la destruccion del arbol.
 */
void _destruir_elem(tipoelem *E){
	destruir_pila(&(E->pTransferencias));
	borrar_grafo(&(E->gAmizades));
}


/////////////////////////// FIN PARTE MODIFICABLE

// Funcion privada (no esta en el .h)
int _comparar_clave_elem(tipoclave cl, tipoelem E){
	return _comparar_claves(cl, _clave_elem(&E));
}

void crear_arbol(abb *A) {
	*A = NULL;
}

unsigned es_vacio(abb A) {
	return A == NULL;
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}

void destruir_arbol(abb *A) {
	if (!es_vacio(*A)) {
		destruir_arbol(&((*A)->izq));
		destruir_arbol(&((*A)->der));
		_destruir_elem(&((*A)->info));
		free(*A);
		*A = NULL;
	}
}

/* Funcion privada para pasar la clave y no tener que
   extraerla del nodo en las llamadas recursivas.
   Esta funcion no aparece en el fichero .h
   */
void _modificar(abb *A, tipoclave cl, tipoelem nodo){
    if (es_vacio(*A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp == 0) {
        (*A)->info = nodo;
    } else if (comp < 0) {
        _modificar(&(*A)->izq, cl, nodo);
    } else {
        _modificar(&(*A)->der, cl, nodo);
    }
}

/* Permite modificar el nodo extrayendo del mismo
   la clave */
void modificar(abb *A, tipoelem nodo) {
    tipoclave cl = _clave_elem(&nodo);
    _modificar(A,cl,nodo);
}

/* Funcion recursiva para insertar un nuevo nodo
   en el arbol. Se presupone que no existe un nodo
   con la misma clave en el arbol. */
void insertar(abb *A, tipoelem E) {
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info = E;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return;
    }
    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info );
    if (comp > 0 ) {
        insertar(&(*A)->der, E);
    } else {
        insertar(&(*A)->izq, E);
    }
}

/* Funcion privada que permite ...
*/
tipoelem _suprimir_min(abb *A) {
    abb aux;
    tipoelem ele;
    if (es_vacio((*A)->izq)) {
        ele = (*A)->info;
        aux = *A;
        *A = (*A)->der;
        //_destruir_elem(&aux->info);
        free(aux);
        return ele;
    } else {
        return _suprimir_min(&(*A)->izq);
	}
}

/* Funcion que permite eliminar un nodo del arbol */
void suprimir(abb *A, tipoelem E) {
    abb aux;
    if(es_vacio(*A)){
       return;
    }

    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if(comp < 0){ //if (E < (*A)->info) {
        suprimir(&(*A)->izq, E);
    } else if (comp > 0){ //(E > (*A)->info) {
        suprimir(&(*A)->der, E);
    } else if (es_vacio((*A)->izq) && es_vacio((*A)->der)) {
        _destruir_elem(&((*A)->info));
        free(*A);
        *A = NULL;
    } else if (es_vacio((*A)->izq)) { 	// pero no es vacio derecha
        aux = *A;
        *A = (*A)->der;
        _destruir_elem(&aux->info);
        free(aux);
    } else if (es_vacio((*A)->der)) { 	//pero no es vacio izquierda
        aux = *A;
        *A = (*A)->izq;
        _destruir_elem(&aux->info);
        free(aux);
    } else { 							//ni derecha ni izquierda esta vacio
        (*A)->info = _suprimir_min(&(*A)->der);
    }
}

unsigned es_miembro(abb A, tipoelem E) {
    return es_miembro_clave(A, _clave_elem(&E));
}

unsigned es_miembro_clave(abb A, tipoclave cl) {
    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { 	//cl == A->info
        return 1;
    }
    if (comp > 0) {		//cl > A->info
        return es_miembro_clave(A->der, cl);
    }
    //cl < A->info
    return es_miembro_clave(A->izq, cl);
}

void buscar_nodo(abb A, tipoclave cl, tipoelem *nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);

	if (comp == 0) { 		// cl == A->info
    	*nodo = A->info;
	} else if (comp < 0) { 	// cl < A->info
	    buscar_nodo(A->izq, cl, nodo);
	} else { 				// cl > A->info
	    buscar_nodo(A->der, cl, nodo);
	}
}

void info(abb A, tipoelem *E) {
    *E = A->info;
}
