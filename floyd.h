/* 
 * File:   floyd.h
 * Author: Marlon Prudente <marlonmateuspr@gmail.com>
 *
 * Created on 29 de Junho de 2015, 21:52
 */

#ifndef FLOYD_H
#define	FLOYD_H

#include "graph.h"
int retornamenor( int a, int b);
int **inicializa_matriz_de_adjacencias (int r, int c, int w);
void floyd(graph*);

#endif	/* FLOYD_H */

