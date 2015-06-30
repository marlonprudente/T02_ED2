/* 
 * File:   floyd.C
 * Author: Marlon Prudente <marlonmateuspr@gmail.com>
 * 
 * Created on 29 de Junho de 2015, 21:52
 */
#include "floyd.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define INF  1000000
int retornamenor( int a, int b)
{
    if (a > b)
    {
    return b;
    }
    else
    {
    return a;
    }
    
}
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

void floyd(graph* g) {
      int k, i, j;
   int **D = inicializa_matriz_de_adjacencias(g->node_count, g->node_count, INF);
   int **temp = inicializa_matriz_de_adjacencias(g->node_count, g->node_count, INF);


    /*for (i = 0; i < g->node_count; i++) {
        for (j = 0; j < g->node_count; j++) {
                printf("%d | ", g->matrixadj[i][j]);
            }
            printf("\n");

    }*/
   
    for (i = 0; i < g->node_count; i++) {
        for (j = 0; j < g->node_count; j++) {
            D[i][j] = g->matrixadj[i][j];            
        }
    } 

   /*****************************/
   /*FAZER: termine o algoritmo!*/
    /*****************************/
    
    for(k = 0; k < g->node_count; k++)
    {
        for(i = 0; i< g->node_count; i++)
        {
            for( j = 0; j < g->node_count; j++)
            {
                temp[i][j] = retornamenor(D[i][j], D[i][k] + D[k][j]);
                
            }
 
        }
        /***/
        for(i = 0; i< g->node_count; i++)
        {
            for( j = 0; j < g->node_count; j++)
            {
                D[i][j] = temp[i][j];

            }
        }


    }
   
       for(i = 0; i< g->node_count; i++)
        {
            for( j = 0; j < g->node_count; j++)
            {
                printf("%d | ", D[i][j]);
            }
            printf("\n");
        }
}