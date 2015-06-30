#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"
#include "dijkstra.h"
#include "heap.h"
/*------- Definições -------- */

#define INFTY 1000000
#define NIL -1
#define TRUE 1
#define FALSE 0

/*------- Estruturas -------- */

/*Lista encadeada para guardar os vizinhos de cada nó.*/
typedef struct node {
   int id; /*identificação do vértice*/
   struct node *proximo;
} Node;

typedef struct graph {
   int V; /*Número de vértices no Grafo.*/
   int E; /*Número de arestas no Grafo.*/
   Node **listadj;  /*Lista de adjacências.*/
   int **matrixadj; /*Matriz de adjacências.*/
} Graph;

typedef struct queue {
   int tam;
   int *elems;
} Queue;

/*------- Funções -------- */

Graph* criar_grafo (int V);
void adicionar_aresta (Graph *G, int u, int v, int w);
int **inicializa_matriz_de_adjacencias (int r, int c, int w);
Node* criar_vertice (int v, Node *lista);
Queue* criar_queue (int tam);
int vazio_queue (Queue* Q);
int extract_min (Queue *Q, int dist[], int V);
void initialize_single_source (int source, int pai[], int dist[], Queue *Q, int V);
void relax (int u, int v, Graph *G, int pai[], int dist[]);
void Dijkstra (Graph *G, int source);
void BellmanFord (Graph *G, int source);
int FloydWarshall (Graph *G);

/*------------------------*/

/* A função abaixoc cria um Grafo e inicializa seus atributos. */
/* Também são criadas listas de adjancência vazias para cada um dos vértices. */
Graph* criar_grafo (int V) {
   Graph *G = (Graph *)malloc(sizeof(Graph));
   G->V = V;
   G->E = 0;
   G->listadj = (Node **)malloc(V * sizeof (Node *));
   int v;
   for (v = 0; v < V; v++)
      G->listadj[v] = NULL;
   G->matrixadj = inicializa_matriz_de_adjacencias (V, V, INFTY);
   return G;
}

/*Alocando memória e inicializando com {val} a matriz de adjacência do Grafo: */
int **inicializa_matriz_de_adjacencias (int r, int c, int w) {
   int i, j;
   int **mat = malloc( r * sizeof (int *));
   for (i = 0; i < r; i++)
      mat[i] = malloc( c * sizeof (int));
   for (i = 0; i < r; i++)
      for (j = 0; j < c; j++)
         mat[i][j] = w;
   return mat;
}

/* A função abaixo insere uma aresta {u-v} no Grafo {G} com peso {w}.
Se o Grafo já tem a aresta então nada é feito. */
void adicionar_aresta (Graph *G, int u, int v, int w) {

   Node *aux; /*Variável para percorrer a lista de adjacência do vértice {u}*/

   for (aux = G->listadj[u]; aux != NULL; aux = aux->proximo)
      if (aux->id == v) return;
   G->listadj[u] = criar_vertice (v, G->listadj[u]);

   /*Adiciona a aresta na matriz de adjacência: */
   G->matrixadj[u][v] = w;
   G->E++; /*Incrementa o número de arestas no Grafo.*/
}

/*A função abaixo aloca um novo nó {v} na lista encadeada {lista}.*/
Node* criar_vertice (int v, Node *lista) {
   Node *novo = (Node *)malloc(sizeof(Node));
   novo->id = v;
   novo->proximo = lista;
   return novo;
}

/*Função para inicializar uma fila: */
Queue* criar_queue (int tam) {
   Queue *Q = (Queue *)malloc(sizeof(Queue));
   Q->tam = tam;
   Q->elems = (int *)malloc(tam*sizeof(int));
   return Q;
}

int vazio_queue (Queue* Q) {
   return (Q->tam == 0);
}

/*Esta função extrai o vértice com menor custo de uma fila Q: */
int extract_min (Queue *Q, int dist[], int V)
{
   int min = INFTY, min_index;
   int v;
   for (v = 0; v < V; v++) {
      if ( (Q->elems[v] == FALSE) && (dist[v] < min) ) {
         min = dist[v];
         min_index = v;
      }
   }
   Q->elems[min_index] = TRUE;
   Q->tam--;
   return min_index;
}

/*Esta função inicializa os vértices em uma busca por caminhos mínimos: */
void initialize_single_source (int source, int pai[], int dist[], Queue *Q, int V) {
   int v;
   for (v = 0; v < V; v++) {
      pai[v] = NIL;
      dist[v] = INFTY;
      Q->elems[v] = FALSE;
   }
   dist[source] = 0;
}

/*Função para relaxação de arestas: */
void relax (int u, int v, Graph *G, int pai[], int dist[]) {
   if (dist[v] > dist[u] + G->matrixadj[u][v]) {
      dist[v] = dist[u] + G->matrixadj[u][v];
      pai[v] = u;
   }
}

/*Caminhos mínimos por Dijkstra: */
void Dijkstra (Graph *G, int source) {

   int pai[G->V];  /*Árvore de caminhos mínimos.*/
   int dist[G->V]; /*Distâncias mínimas.*/
   Queue *Q = criar_queue (G->V);

   initialize_single_source (source, pai, dist, Q, G->V);

   while (!vazio_queue(Q)) {
      int u = extract_min (Q, dist, G->V);
      Node *v; /*Variável para percorrer a lista de adjacência do vértice {u}*/
      for (v = G->listadj[u]; v != NULL; v = v->proximo) {
         relax (u, v->id, G, pai, dist);
      }
      printf("Nó = %d (predecessor = %d), caminho mínimo do nó %d até o nó %d = %d\n", u, pai[u], source, u, dist[u]);
   }
}


/*Caminhos mínimos por Bellman-Ford: */
void BellmanFord (Graph *G, int source) {
    int i, u;
   int pai[G->V];  /*Árvore de caminhos mínimos.*/
   int dist[G->V]; /*Distâncias mínimas.*/
   Queue *Q = criar_queue (G->V);

   initialize_single_source (source, pai, dist, Q, G->V);

   /*****************************/
   /*FAZER: termine o algoritmo!*/
   /*****************************/
   Node *v;
     /*Variável para percorrer a lista de adjacência do vértice {u}*/

    for(i = 0; i< G->V - 1; i++)
    {

        int u;
        for(u = 0; u < G->V; u++)
        {
            for(v = G->listadj[u]; v != NULL; v = v->proximo)
            {
                relax (u, v->id, G, pai, dist);
            }
        }


    }

    for(u = 0; u < G->V; u++)
    {
        for(v = G->listadj[u]; v != NULL; v = v->proximo)
        {
            if(dist[v->id] > dist[u] + v->id)
            {
                printf("Falso\n");
                printf("Tem solução\n");
                exit(0);
            }
            printf("Verdadeiro");
            exit(1);
        }
    }


}

int retornamenor( int a, int b)
{
    if (a > b)
    {
    return b;
    }
    else
    return a;
}

/*Caminhos mínimos entre todos os pares por Floyd-Warshall.*/
int FloydWarshall (Graph *G) {

   int k, i, j;
   int **D = inicializa_matriz_de_adjacencias (G->V, G->V, INFTY);
    int **temp = inicializa_matriz_de_adjacencias (G->V, G->V, INFTY);
   /*Zerando os elementos da diagonal principal:*/
   for (i = 0; i < G->V; i++) {
       G->matrixadj[i][i] = 0;

   }
      for (i = 0; i < G->V; i++) {
      for(j = 0; j<G->V; j++)
      {
       D[i][j] = G->matrixadj[i][j];
      }

   }

   /*****************************/
   /*FAZER: termine o algoritmo!*/
    /*****************************/
    for(k = 0; k < G->V; k++)
    {
        for(i = 0; i< G->V; i++)
        {
            for( j = 0; j < G->V; j++)
            {
                temp[i][j] = retornamenor(D[i][j], D[i][k] + D[k][j]);
            }
        }
        /****/
        for(i = 0; i< G->V; i++)
        {
            for( j = 0; j < G->V; j++)
            {
                D[i][j] = temp[i][j];
            }
        }


    }

  for(i = 0; i< G->V; i++)
   {
        for( j = 0; j < G->V; j++)
        {
           printf("%d | ", D[i][j]);
        }
        printf("\n");
   }


}

int main () {
    
        graph* g;

	FILE *f;
	char buffer[100], city[100], *city_tmp;
	bool started_vertices;
	int src, dest, citya, cityb;
	double distance;
        
        started_vertices = false;
	g = graph_make();
	f = fopen("grafo.txt", "r");

	while(fgets(buffer, 100, f) != NULL) {
		if(!started_vertices) {
			if(*buffer == '\n') { continue; }
			if(strcmp(buffer, "---\n") == 0) { 
				started_vertices = true;
				continue;
			}
			sscanf(buffer, "%d) %[^\n]", &src, city);
			city_tmp = malloc(strlen(city)+1);
			strcpy(city_tmp, city);
			graph_add_node(g, city_tmp);
		} else {
			if(*buffer == '\n') { continue; }
			sscanf(buffer, "%d -> %d %lf\n", &src, &dest, &distance);
			graph_add_edge(g, src, dest, distance);			
		}
		
	}
        printf("Digite sua localização (7 = Curitiba):\n");
        scanf("%d", &citya);
        printf("Digite seu destino (2 = B. Horizonte):\n");
        scanf("%d", &cityb);
        
    dijkstra(g, citya); /* Inicio pela Cidade A */
    graph_dump(g, cityb); /* Destino -> Cidade B */
    graph_destroy(g);
   
   return 0;
}

