#include <stdlib.h> 
#include <stdio.h>
#include "struct.h"
#include "build_graph.h"

// from input file, read the graphs and store them in the short** array
short** readGraph(char** infile, short row, short col){
    FILE* fp = fopen(infile, "rb");
    if(fp == NULL){
        fprintf(stderr, "Error opening input file\n");
        return NULL;
    }

    fread(&row, sizeof(short), 1, fp);
    fread(&col, sizeof(short), 1, fp);


    short** graph = (char**)malloc(row * sizeof(short*));
    for(int i = 0; i < row; i++){
        graph[i] = (char*)malloc(col * sizeof(short));
        for(int j = 0; j < col; j++){
            fread(&graph[i][j], sizeof(short), 1, fp);
        }
    }
    return graph;
}
