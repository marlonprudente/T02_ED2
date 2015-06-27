/**************************************
 
	Um heap é usado para se fazer a lista
	de prioridade para o algoritmo de 
	Dijkstra.
	
	O heap guarda índices para o 
	arranjo de nós do grafo. A
	prioridade é a distancia ao nó
	de origen.

***************************************/

/* 
 * File:   heap.h
 * Author: Marlon Prudente <marlonmateuspr@gmail.com>
 */
#ifndef HEAP_H
#define HEAP_H
#include <stdbool.h>
#include "graph.h"


typedef int (heap_compare)(graph*, unsigned int, unsigned int);

#define HEAP_LEFT(nodo) ((nodo)+(nodo)+1)
#define HEAP_RIGHT(nodo) ((nodo)+(nodo)+2)
#define HEAP_PARENT(nodo) (((nodo)-1)>>1)

typedef struct {
    unsigned int* nodes;
    unsigned int space;
    unsigned int count;
    heap_compare* compare;
	graph* g; 
} heap; 

/*
	Poe-se na heap todos os elementos do grafo, em orden de distancia
	a origem, segundo Dijkstra.
	
	O(|V| log|V|)
*/	

heap* heap_make(heap_compare*, graph*);

void heap_insert(heap*, const unsigned int);

/*
	Busca o elemento com a prioridade maxima.
	O(1)
*/

unsigned int heap_find_min(const heap*);

/*
	Busca o elemento com a prioridade maxima, e o
	tira da heap.
	O(log n)
*/

unsigned int heap_delete_min(heap*);

/*
	Imprime a Heap no console, em formato DOT.
*/
void heap_dump(const heap*, const unsigned int);

/*
	Libera a memoria ocupada pelo heap.
*/
void heap_destroy(heap*);

bool heap_is_empty(const heap*);

void heap_heapify_up(heap*, unsigned int);
										
#endif HEAP_H