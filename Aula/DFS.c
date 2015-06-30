#include <stdio.h>
#include <stdlib.h>

/*------- Definições -------- */

#define BRANCO -1
#define PRETO 0
#define CINZA 1

/*------- Estruturas -------- */

/*Lista encadeada para guardar os vizinhos de cada nó.*/
typedef struct node {
   int id; /*identificação do vértice*/
   struct node *proximo;
} Node;

typedef struct graph {
   int V; /*Número de vértices no Grafo.*/
   int E; /*Número de arestas no Grafo.*/
   Node **listadj; /*Lista de adjacências.*/
} Graph;

/*------------------------*/


/*------- Funções -------- */

Graph* criar_grafo (int V);

void adicionar_aresta (Graph *G, int v, int w);

Node* criar_vertice (int v, Node *lista);

void DFS (Graph *G, int d[], int f[], int pai[]);

void DFS_Visit (int u, Graph *G, int d[], int f[], int pai[], int cor[], int *tempo);

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
   return G;
}

/* A função abaixo insere uma aresta u-v no Grafo G.
Se o Grafo já tem a aresta então nada é feito. */
void adicionar_aresta (Graph *G, int u, int v) {
   Node *aux; /*Variável para percorrer a lista de adjacência do vértice {u}*/
   for (aux = G->listadj[u]; aux != NULL; aux = aux->proximo)
      if (aux->id == v) return;
   G->listadj[u] = criar_vertice (v, G->listadj[u]);
   G->E++; /*Incrementa o número de arestas no Grafo.*/
}

/*A função abaixo aloca um novo nó {v} na lista encadeada {lista}.*/
Node* criar_vertice (int v, Node *lista) {
   Node *novo = (Node *)malloc(sizeof(Node));
   novo->id = v;
   novo->proximo = lista;
   return novo;
}

/*Busca em profundidade: */
void DFS (Graph *G, int d[], int f[], int pai[]) {

   int cor[G->V];
   int u;
   for (u = 0; u < G->V; u++) {
      cor[u] = BRANCO;
      pai[u] = -1;
   }

   int tempo = 0;

   for (u = 0; u < G->V; u++) {
      if (cor[u] == BRANCO) {
         DFS_Visit (u, G, d, f, pai, cor, &tempo);
      }
   }
}

void DFS_Visit (int u, Graph *G, int d[], int f[], int pai[], int cor[], int *tempo) {

    cor[u] = CINZA;
    *tempo += 1;
    d[u] = *tempo;
   //printf("Complete o código para funcionar!!!!!!\n");
   Node *v; /*Variável para percorrer a lista de adjacência do vértice {u}*/
   for (v = G->listadj[u]; v != NULL; v = v->proximo) {
      if (cor[v->id] == BRANCO) {
      if(cor[u]==CINZA)
      {
      printf("Aresta de Arvore;");
      }
      pai[v->id] = u;
         DFS_Visit (v->id, G, d, f, pai, cor, tempo);
      }
      else if(cor[v->id] == CINZA)
      {
        if(cor[u]==CINZA)
        {
            printf("Aresta de Retorno");
        }

      }
      else if(cor[v->id] == PRETO)
      {
        printf("Aresta de Cruzamento");
      }
   }
   cor[u] = PRETO;
   *tempo += 1;
   f[u] = *tempo;
}

int main () {

   /*Número de vértices necessários no Grafo: */
   int V = 8;

   /*Inicializando o Grafo: */
   Graph *G = criar_grafo (V);

   /*Vetores auxiliares para guardar informações sobre a DFS: */
   int d[V], f[V], pai[V];

   /**Organização dos vértices**
          2   1   0   5
          3   4   6   7
   ***************************/

   /*Adicionando as arestas: */
   adicionar_aresta (G, 0, 4);
   adicionar_aresta (G, 0, 1);
   adicionar_aresta (G, 1, 4);
   adicionar_aresta (G, 1, 2);
   adicionar_aresta (G, 2, 3);
   adicionar_aresta (G, 3, 1);
   adicionar_aresta (G, 4, 3);
   adicionar_aresta (G, 5, 7);
   adicionar_aresta (G, 5, 6);
   adicionar_aresta (G, 6, 0);
   adicionar_aresta (G, 6, 4);
   adicionar_aresta (G, 7, 6);
   adicionar_aresta (G, 7, 5);

   DFS (G, d, f, pai);

   int v;
   for (v = 0; v < V; v++) {
      printf(" %d = [%d,%d] (%d) ", v, d[v], f[v], pai[v]);
   }
   printf("\n");

   return 0;
}

