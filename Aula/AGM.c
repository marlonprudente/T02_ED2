#include <stdio.h>
#include <stdlib.h>

/*------- Definições -------- */

#define INFTY 1000000
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

/*A structure to represent a subset for union-find: */
typedef struct subset {
  int parent;
  int rank;
} Set;

typedef struct edge {
   int u;
   int v;
   int weight;
} Edge;

/*------- Funções -------- */

Graph* criar_grafo (int V);

void adicionar_aresta (Graph *G, int u, int v, int w);

int **inicializa_matriz_de_adjacencias (int r, int c, int w);

Node* criar_vertice (int v, Node *lista);

Set* Make_sets (int V);

void Union (Set subsets[], int x, int y);

int Find (Set subsets[], int i);

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

   for (aux = G->listadj[v]; aux != NULL; aux = aux->proximo)
      if (aux->id == u) return;
   G->listadj[v] = criar_vertice (u, G->listadj[v]);

   /*Adiciona a aresta na matriz de adjacência: */
   G->matrixadj[u][v] = w;
   G->matrixadj[v][u] = w;
   G->E++; /*Incrementa o número de arestas no Grafo.*/
}

/*A função abaixo aloca um novo nó {v} na lista encadeada {lista}.*/
Node* criar_vertice (int v, Node *lista) {
   Node *novo = (Node *)malloc(sizeof(Node));
   novo->id = v;
   novo->proximo = lista;
   return novo;
}

/****************************************************/
Set* Make_sets (int V) {
    Set *set = (struct subset*)malloc(V*sizeof(struct subset));
    int v;
    for (v = 0; v < V; ++v){
        set[v].parent = v;
        set[v].rank = 0;
    }
    return set;
}

/****************************************************/
int Find (Set subsets[], int i) {
    /*Find root and make root as parent of i (path compression): */
    if (subsets[i].parent != i) {
        subsets[i].parent = Find (subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

/****************************************************/
void Union (Set subsets[], int x, int y) {
    int xroot = Find (subsets, x);
    int yroot = Find (subsets, y);
    /*Attach smaller rank tree under root of high rank tree (Union by Rank): */
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    }
    /*If ranks are same, then make one as root and increment its rank by one: */
    else{
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

/* A utility function to find the vertex with minimum key
value, from the set of vertices not yet included in MST: */
int extract_min (int key[], int Q[], int V)
{
   /* Initialize min value: */
   int min = INFTY;
   int min_index;

   int v;
   for (v = 0; v < V; v++) {
      if ( (Q[v] == TRUE) && (key[v] < min) ) {
         min = key[v];
         min_index = v;
      }
   }
   Q[min_index] = FALSE;
   return min_index;
}

/*Ordenação de arestas EXTREMAMENTE ineficiente: */
Edge* sort_edges (Graph *G) {
   int i, j, u, v, k = 0;
   Edge *sort = (Edge *)malloc(G->V * G->V * sizeof(Edge));
   for (u = 0; u < G->V; u++) {
      for (v = u + 1; v < G->V; v++) {
         if (G->matrixadj[u][v] != INFTY) {
            Edge e = {u, v, G->matrixadj[u][v]};
            sort[k] = e;
            k++;
         }
      }
   }
   /*Selection sort: */
   for (i = 0; i < k; i++) {
      int menor = i;
      for (j = i+1; j < k; j++) {
         if (sort[j].weight < sort[menor].weight) {
            menor = j;
         }
      }
      Edge tmp = sort[menor];
      sort[menor] = sort[i];
      sort[i] = tmp;
   }
   return sort;
}

/*Arvore Geradora Mínima através do algoritmo de Kruskal.*/
void AGM_Kruskal (Graph *G) {

   /*Arestas da árvore geradora mínima: */
   Edge MST[G->V];

   /*Para cada v em G->V crie um conjunto: */
   Set *sets = Make_sets (G->V);

   Edge *E = sort_edges (G);

   int uv, i;

   int e = 0;

   /*Para cada aresta {u,v} do Grafo: */
   for (uv = 0; uv < G->E-1; uv++) {

        /*Retire a aresta com menor peso: */
        Edge min = E[uv];

        /*Verifique quem são as raizes: */
        int u = Find (sets, min.u);
        int v = Find (sets, min.v);

        /*Se a inclusão da aresta não cria um ciclo, então a adicione:*/
        if (u != v) {
           MST[e++] = min;
           Union (sets, u, v);
        }
    }

    printf("\n\nÁrvore geradora mínima por Kruskal: \n");
    for (i = 0; i < e; i++) {
       printf("Aresta: %d - %d com peso %d.\n", MST[i].u, MST[i].v, MST[i].weight);
    }
    free(E);
}


/*Arvore Geradora Mínima através do algoritmo de Prim.*/
void AGM_Prim (Graph *G) {

   int pai[G->V];   /*Árvore geradora mínima.*/
   int key[G->V];   /*Valores utilizados para retirar o vértice com menor peso no corte.*/
   int Q[G->V];     /*O vetor Q simula os vértices que ainda estão na fila de prioridade.*/

   /* Inicializando todas as chaves como INFINITO: */
   int u;
   for (u = 0; u < G->V; u++) {
      key[u] = INFTY;
      pai[u] = INFTY;
      Q[u] = TRUE; /*Todos os vértices são adicionados na fila de prioridade {TRUE}. */
   }

   /* Incluindo o primeiro vértice na MST: */
   key[0] =  0;
   pai[0] = -1;  /* Primeiro vértice é sempre a raiz da MST. */

   printf("\n\nÁrvore geradora mínima por Prim: \n");

   int i = 0;
   int soma = 0;
   while (i < G->V) {
      int u = extract_min (key, Q, G->V);
      Node *v; /*Variável para percorrer a lista de adjacência do vértice {u}*/
      for (v = G->listadj[u]; v != NULL; v = v->proximo) {
         if ( (Q[v->id] == TRUE) && (G->matrixadj[u][v->id] < key[v->id]) ) {
            pai[v->id] = u;
            key[v->id] = G->matrixadj[u][v->id];
         }
      }
      if (i != 0) {
         printf("Aresta: %d - %d com peso %d. \n", pai[u], u, G->matrixadj[u][pai[u]]);
         soma += G->matrixadj[u][pai[u]];
      }
      i++;
   }

   int l, m;
   int soma2 = 0;
   for (l = 0; l < G->V; l++) {
     for (m = l + 1; m < G->V; m++) {
        if (G->matrixadj[l][m] != INFTY) {
           soma2 += G->matrixadj[l][m];
        }
     }
   }

   printf("Soma total: %d, Soma tudo: %d\n", soma, soma2);
}
void Prim_problema1(Graph *G, int ini, int fim)
{
    int pai[G->V];   /*Árvore geradora mínima.*/
   int key[G->V];   /*Valores utilizados para retirar o vértice com menor peso no corte.*/
   int Q[G->V];     /*O vetor Q simula os vértices que ainda estão na fila de prioridade.*/
    int peso = 0;
   /* Inicializando todas as chaves como INFINITO: */
   int u;
   for (u = 0; u < G->V; u++) {
      key[u] = INFTY;
      pai[u] = INFTY;
      Q[u] = TRUE; /*Todos os vértices são adicionados na fila de prioridade {TRUE}. */
   }

   /* Incluindo o primeiro vértice na MST: */
   key[0] =  fim;
   pai[0] = -1;  /* Primeiro vértice é sempre a raiz da MST. */

   printf("\n\nÁrvore geradora mínima por Prim: \n");

   int i = ini;
   int soma = 0;
   while (i < fim) {
      int u = extract_min (key, Q, G->V);
      Node *v; /*Variável para percorrer a lista de adjacência do vértice {u}*/
      for (v = G->listadj[u]; v != NULL; v = v->proximo) {
         if ( (Q[v->id] == TRUE) && (G->matrixadj[u][v->id] < key[v->id]) ) {
            pai[v->id] = u;
            key[v->id] = G->matrixadj[u][v->id];
         }
      }
      if (i != 0) {
      /*
         printf("Aresta: %d - %d com peso %d. \n", pai[u], u, G->matrixadj[u][pai[u]]);
         soma += G->matrixadj[u][pai[u]];*/
         if(G->matrixadj[u][pai[u]] > peso)
         {
            peso = G->matrixadj[u][pai[u]];
         }
      }
      i++;
   }

   int l, m;
   int soma2 = 0;
   for (l = 0; l < G->V; l++) {
     for (m = l + 1; m < G->V; m++) {
        if (G->matrixadj[l][m] != INFTY) {
           soma2 += G->matrixadj[l][m];
        }
     }
   }
    printf("De %d a %d => %d Decibeis.\n", ini, fim, peso);
   //printf("Soma total: %d, Soma tudo: %d\n", soma, soma2);
}

int main () {

   /*       Posição dos vértices:     */
   /*                                 */
   /*        1       2       3        */
   /*   0        8                4   */
   /*        7       6       5        */
   /*                                 */

   /*Número de vértices necessários no Grafo: */
   int V = 7, inicio , fim ;

   /*Inicializando o Grafo: */
   Graph *G = criar_grafo (V);


                    /*  u, v, w (peso)*/
    adicionar_aresta (G, 0, 1, 50); /* Zero a Um com Peso 50*/
    adicionar_aresta (G, 0, 2, 60);
    adicionar_aresta (G, 1, 3, 120);
    adicionar_aresta (G, 1, 4, 90);
    adicionar_aresta (G, 2, 5, 50);
    adicionar_aresta (G, 3, 5, 80);
    adicionar_aresta (G, 3, 6, 70);
    adicionar_aresta (G, 4, 6, 40);
    adicionar_aresta (G, 5, 6, 140);
    printf("\nDigite o Inicio e o Fim:\n");
    scanf("%d%d", &inicio, &fim);
    Prim_problema1(G, inicio, fim);


    int conec, tabas;
    printf("\n\nProblema 2 - Kruskal");
   /* while(tabas!=0||conec!=0)
    {*/
    printf("Digite o numero de tapas e de conexoes:\n");
    scanf("%d%d", &tabas, &conec);
    Graph *G2 = criar_grafo (tabas + 1);
    int arest1, arest2, peso, i;
    for(i = 0; i<conec; i++)
    {
        printf("Digite a aresta 1:\n");
        scanf("%d%", &arest1);
        printf("Digite a aresta 2:\n");
        scanf("%d%", &arest2);
        printf("Digite o peso desse caminho:\n");
        scanf("%d%", &peso);
        adicionar_aresta (G2, arest1, arest2, peso);
        }
    //}
   //AGM_Prim (G);

   AGM_Kruskal (G2);

   return 0;
}

