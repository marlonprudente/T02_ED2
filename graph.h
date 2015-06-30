/****************************
 
 * 1) Tipos de dados do grafo.
 * 2) API publica de grafos.

****************************/
/* 
 * File:   graph.h
 * Author: Marlon Prudente <marlonmateuspr@gmail.com>
 */
#ifndef GRAPH_H
#define GRAPH_H

struct node;

/* 
	Um vertice é direccional: tem fonte, direção, e um peso.
	Os IDs são índices aos nós do grafo.
*/
typedef struct {
    unsigned int source;
    unsigned int destination;
    double weight;
} edge;
 

/* 	
	Um nó tem vertices adjacentes.
   	edge_count é a quantidade de vertices adjacentes.
	edge_space é o espaço alocado (sempre >= edge_count) para vertices.
	distance, heap_index e previous são usados pelo algoritmo de Dijkstra.
*/

typedef struct node {
    edge* edges;
    unsigned int edge_count;
    unsigned int edge_space;
   	char* value;

/* 
	Distancia estimada no algoritmo de Dijkstra.
*/
    double distance;
/* 
	Se usa para mantener ordenada a lista de prioridade em Dijkstra.
*/ 
    int heap_index;
/* 
	O nó previsto no caminho mais curto, segundo Dijkstra. É um índice dos 
	nós do grafo.
*/ 
	int previous;
} node; 

/* 	
	Conceitualmente, um grafo é uma coleção de nós, cada nó tendo 
	suas vertices. Usa o mesmo tipo de reserva de espaço que un nó - 
	node_space é a quantidade de memoria reservada para nós, node_count é
	a quantidade de nós no grafo.
*/

typedef struct {
    node* nodes;
    unsigned int node_count;
    unsigned int node_space;
    int **matrixadj;
    } graph;

/* 
	API de um grafo.
*/

graph* graph_make();

/* 
	Matriz de Adjacência para Floyd.	
*/





/* 
	Insere um nó ao grafo, com char* sendo o nome do nó.	
*/
void graph_add_node(graph*, char*);
/* 
	Insere um vertice entre dois nós
*/
void graph_add_edge(graph*, unsigned int, unsigned int, double);

/*
	Libera a memoria ocupada pelo grafo.
*/

void graph_destroy(graph*);

/*
	Imprimi o grafo no console, em formato DOT.

*/
void graph_dump(graph*, int);

#endif // GRAPH_H