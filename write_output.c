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
int writeOutput1(char** outfile, short** g, short row, short col){
    FILE* fp = fopen(outfile, "w");
    if(fp == NULL){
        fprintf(stderr, "Error opening output file 1\n");
        return EXIT_FAILURE;
    }
    fprintf(fp, "%hd %hd\n", row, col);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fprintf(fp, "%hd", g[i][j]);
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
int writeOutput2(char** outfile, Node** g, short col){
    FILE* fp = fopen(outfile, "wb");
    if(fp == NULL){
        fprintf(stderr, "Error opening output file 2\n");
        return -1;
    }

    fwrite(&col, sizeof(short), 1, fp);
    int fastest_idx = 0;
    int fastest_time = 0;
    for(int i = 0; i < col; i++){
        Path* p = shortestPath(g, g[0][i]);
        if(p->time < fastest_time){
            fastest_time = p->time;
            fastest_idx = i;
        }
        fwrite(&p->time, sizeof(int), 1, fp);
    }

    return fastest_idx;
}

/*
Write the third ouput file in binary format
Fastest path file format:
First store the fastest time -> int
then store the number of locations that constitute the path -> int
finally stor the (row,col) for each location in the path -> (short, short)
*/
int writeOutput3(char** outfile, Path* p, int fastest_idx){
    FILE* fp = fopen(outfile, "wb");
    if(fp == NULL){
        fprintf(stderr, "Error opening output file 3\n");
        return EXIT_FAILURE;
    }

    fwrite(&p->time, sizeof(int), 1, fp);
    fwrite(&p->size, sizeof(int), 1, fp);
    Node* temp = p->head;

    while(temp != NULL){
        fwrite(&temp->row, sizeof(short), 1, fp);
        fwrite(&temp->col, sizeof(short), 1, fp);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}