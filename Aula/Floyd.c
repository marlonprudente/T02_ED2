#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Floyd.h"

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

void floyd (graph* g, unsigned int source) {

   int k, i, j;
   int count = g->node_count;
   //node *n = &g->nodes[count];
   int **D = inicializa_matriz_de_adjacencias (count, count, INFTY);
   int **temp = inicializa_matriz_de_adjacencias (count, count, INFTY);
   /*Zerando os elementos da diagonal principal:*/
   for (i = 0; i < count; i++) {
       g->matrixadj[i][i] = 0;

   }
      for (i = 0; i < count; i++) {
      for(j = 0; j<count; j++)
      {
       D[i][j] = g->matrixadj[i][j];
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
