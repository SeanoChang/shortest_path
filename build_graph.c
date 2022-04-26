#include <stdlib.h> 
#include <stdio.h>
#include "struct.h"
#include "build_graph.h"

// from input file, read the graphs and store them in the short** array
Graph* readGraph(char* infile){
    FILE* fp = fopen(infile, "rb");
    if(fp == NULL){
        fprintf(stderr, "build_graph.c Error opening input file\n");
        fclose(fp);
        return NULL;
    }

    short row;
    short col;
    // read row and col from the file
    fread(&row, sizeof(short), 1, fp);
    fread(&col, sizeof(short), 1, fp);

    // initialize the graph matrix
    Graph* graph = malloc(sizeof(Graph));
    graph->row = row;
    graph->col = col;
    graph->g = malloc(sizeof(GraphNode*)*row);

    for(int i = 0; i < row; i++){
        graph->g[i] = malloc(sizeof(GraphNode)*col);
        for(int j = 0; j < col; j++){
            fread(&graph->g[i][j].time, sizeof(short), 1, fp);
            graph->g[i][j].row = i;
            graph->g[i][j].col = j;
        }
    }
    
    fclose(fp);
    return graph;
}
