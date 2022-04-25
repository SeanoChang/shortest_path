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
int writeOutput1(char* outfile, Graph* graph, short row, short col){
    FILE* fp = fopen(outfile, "w");
    if(fp == NULL){
        fprintf(stderr, "write_output.c Error opening output file 1\n");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%hd %hd\n", row, col);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fprintf(fp, "%hd", graph->g[i][j].time);
            if(j != col - 1) fprintf(fp, " ");
        }
        fprintf(fp, "\n");
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
Path* writeOutput2(char* outfile, Graph* graph, short row, short col){
    FILE* fp = fopen(outfile, "wb");
    if(fp == NULL){
        fprintf(stderr, "write_output.c Error opening output file 2\n");
        return NULL;
    }

    fwrite(&col, sizeof(short), 1, fp);
    int fastest_time = -1;
    int fastest_idx = 0;
    Path* fastestPath = NULL;
    Path** paths = malloc(sizeof(Path*)*col);
    for(int i = 0; i < col; i++){
        Path* p = shortestPath(graph, row, col, i);
        fwrite(&p->time, sizeof(int), 1, fp);
        if(fastest_time == -1 || fastest_time > p->time){
            fastest_time = p->time;
            fastest_idx = i;
            fastestPath = p;
        }
        paths[i] = p;
    }

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
        fprintf(stderr, "write_output.c Error opening output file 3\n");
        return EXIT_FAILURE;
    }

    fwrite(&p->time, sizeof(int), 1, fp);
    fwrite(&p->size, sizeof(int), 1, fp);
    PathNode* temp = p->front;
    while(temp != NULL){
        fwrite(&temp->node->row, sizeof(short), 1, fp);
        fwrite(&temp->node->col, sizeof(short), 1, fp);
        temp = temp->next;
    }
    destroyPath(p);

    fclose(fp);
    return EXIT_SUCCESS;
}
