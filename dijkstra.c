#include "dijkstra.h"
#include "heap.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double* distances;

int compare(graph* g, unsigned int i, unsigned int j) {
    if(g->nodes[i].distance == g->nodes[j].distance) { return 0; }
    if(g->nodes[i].distance > g->nodes[j].distance) { return 1; }
    return -1;
}

void dijkstra(graph* g, unsigned int source) {
	unsigned int u, v, edge_count;
	node *n, *d;
	edge *e;
	heap *Q;

	g->nodes[source].distance = 0;
	Q = heap_make(compare, g);

	while(!heap_is_empty(Q)) {
		u = heap_delete_min(Q);
		n = &g->nodes[u];
		edge_count = n->edge_count;
		for(v = 0; v < edge_count; v++) {	
			e = &n->edges[v];	
			d = &g->nodes[e->destination];
			if(d->distance > n->distance + e->weight) {
				/* 
                                 Calcula-se os Vértices
				*/			
				d->distance = n->distance + e->weight;
				/* 
                                 Atualiza-se os nós com a distância ótima
				*/
				d->previous = u;
				/* 
                                 Atualiza a lista de prioridade.
				*/
				heap_heapify_up(Q, d->heap_index);				
			}
		}
	}
	heap_destroy(Q);
}