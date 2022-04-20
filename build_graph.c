#include <stdlib.h> 
#include <stdio.h>
#include "struct.h"

// from input file, read the graphs and store them in the short** array
short** readGraph(char** infile){
    FILE* fp = fopen(infile, "rb");
    if(fp == NULL){
        fprintf(stderr, "Error opening input file\n");
        return NULL;
    }

    short row = 0;
    short col = 0;
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

// with the short** array, build the graph with linked list
Node** buildGraph(short** g, short row, short col){
    Node** graph = (Node**)malloc(row * sizeof(Node*));
    for(int i = 0; i < row; i++){
        graph[i] = (Node*)malloc(col * sizeof(Node));
        for(int j = 0; j < col; j++){
            Node* nd = buildNode(i, j, g[i][j]);
            nd->next = buildPath(g, i, j, row, col);
        }
    }
    return graph;
}

// build the linked list for each node, the path that each node can reach
Node* buildPath(short** g, short curRow, short curCol, short maxRow, short maxCol) {
    Node** head = NULL;
    if(curRow - 1 >= 0) {
        Node* nd = buildNode(curRow - 1, curCol, g[curRow - 1][curCol]);
        *head = nd;
    }
    if(curCol - 1 >= 0) {
        Node* nd = buildNode(curRow, curCol - 1, g[curRow][curCol - 1]);
        nd->next = *head;
        *head = nd;
    }
    if(curCol + 1 <= maxCol) {
        Node* nd = buildNode(curRow, curCol + 1, g[curRow][curCol + 1]);
        nd->next = *head;
        *head = nd;
    }
    if(curRow + 1 <= maxRow) {
        Node* nd = buildNode(curRow + 1, curCol, g[curRow + 1][curCol]);
        nd->next = *head;
        *head = nd;
    }

    return *head;
}