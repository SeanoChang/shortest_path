#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "traverse_graph.h"
#include "write_output.h"

/*
Write the first ouput file in text format
Text grid file format:
%hd %hd\n
matrix of size row x col
*/
int writeOutput1(char* outfile, Graph* graph){
    FILE* fp = fopen(outfile, "w");
    if(fp == NULL){
        fprintf(stderr, "write_output.c 16 Error opening output file 1\n");
        return EXIT_FAILURE;
    }

    short row = graph->row;
    short col = graph->col;

    fprintf(fp, "%hd %hd\n", row, col);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fprintf(fp, "%hd", graph->g[i][j].time);
            if(j != col - 1) fprintf(fp, " ");
        }
        if(fprintf(fp, "\n") != 1){
            fprintf(stderr, "write_output.c 30 Error writing output file 1\n");
            return EXIT_FAILURE;
        }
    }
    
    fclose(fp);
    return EXIT_SUCCESS;
}

/*
Write the second ouput file in binary format
Fastest times file format:
first store numbers of entrys -> number of columns as short
then store the fastest times for each entry to exit at the bottom of the matrix -> as int
*/
Path* writeOutput2(char* outfile, Graph* graph){
    FILE* fp = fopen(outfile, "wb");
    if(fp == NULL){
        fprintf(stderr, "write_output.c 48 Error opening output file 2\n");
        return NULL;
    }

    short row = graph->row;
    short col = graph->col;
    
    // write the first number of entrys
    if(fwrite(&col, sizeof(short), 1, fp) != 1){
        fprintf(stderr, "write_output.c 57 Error writing output file 2\n");
        return NULL;
    }

    // for storing the fastest time and fastest path
    int fastest_time = -1;
    int fastest_idx = 0;
    Path* fastestPath = NULL;

    // for each entry, find the fastest time and path, then store the paths in a list
    Path** paths = shortestPaths(graph, row, col);
    for(int i = 0; i < col; i++){
        int time = paths[i]->time;
        if(time > fastest_time){
            fastest_time = time;
            fastest_idx = i;
        }
    }
    // destroy the paths except the fastest one
    destroyPaths(paths, col, fastest_idx);
    fclose(fp);
    return fastestPath;
}

/*
Write the third ouput file in binary format
Fastest path file format:
First store the fastest time -> int
then store the number of locations that constitute the path -> int
finally stor the (row,col) for each location in the path -> (short, short)
*/
int writeOutput3(char* outfile, Path* p){
    FILE* fp = fopen(outfile, "wb");
    if(fp == NULL){
        fprintf(stderr, "write_output.c 98 Error opening output file 3\n");
        return EXIT_FAILURE;
    }

    if(fwrite(&p->time, sizeof(int), 1, fp) != 1){
        fprintf(stderr, "write_output.c 103 Error writing output file 3\n");
        return EXIT_FAILURE;
    }
    if(fwrite(&p->size, sizeof(int), 1, fp) != 1){
        fprintf(stderr, "write_output.c 107 Error writing output file 3\n");
        return EXIT_FAILURE;
    }
    PathNode* temp = p->front;
    while(temp != NULL){
        if(fwrite(&temp->node->row, sizeof(short), 1, fp) != 1){
            fprintf(stderr, "write_output.c 113 Error writing output file 3\n");
            return EXIT_FAILURE;
        }
        if(fwrite(&temp->node->col, sizeof(short), 1, fp) != 1){
            fprintf(stderr, "write_output.c 117 Error writing output file 3\n");
            return EXIT_FAILURE;
        }
        temp = temp->next;
    }
    destroyPath(p);

    fclose(fp);
    return EXIT_SUCCESS;
}
