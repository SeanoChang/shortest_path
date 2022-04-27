#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

Path* buildPath(){
    Path* path = malloc(sizeof(Path));

    path->time = 0;
    path->size = 0;
    path->front = NULL;
    path->rear = NULL;

    return path;
}

PathNode* buildPathNode(GraphNode* nd){
    PathNode* pnode = malloc(sizeof(PathNode));

    pnode->node = nd;
    pnode->next = NULL;

    return pnode;
}

void destroyGraph(Graph* graph){
    for(int i = 0; i < graph->row; i++){
        free(graph->g[i]);
    }
    free(graph->g);
    free(graph);
}

/*
destroy options of path but not the path with the fastest time of all paths
*/
void destroyPaths(Path** paths, short col, int fastest_idx) {
    for(int i = 0; i < col; i++){
        if(i != fastest_idx){
            destroyPath(paths[i]);
        }
    }
    free(paths);
}

void destroyPath(Path* p) {
    PathNode* cur = p->front;
    while(cur != NULL) {
        PathNode* temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(p);
}
