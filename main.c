#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"
#include "dijkstra.h"
#include "heap.h"
#include "floyd.h"
/** Foi Criado nós referente a todas as capitais brasileiras, porem, só foi utilizado 4 Capitais, Curitiba, R. de Janeiro, São Paulo e B. Horizonte**/

int main() {
	
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
        printf("Digite sua localização (1 = Curitiba):\n");
        scanf("%d", &citya);
        printf("Digite seu destino (0 = B. Horizonte):\n");
        scanf("%d", &cityb);
        
    dijkstra(g, citya); /* Inicio pela Cidade A */
    floyd(g);
    graph_dump(g, cityb); /* Destino -> Cidade B */
    graph_destroy(g);

    return 0;
}
