#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

Path* buildPath(){
    Path* path = (Path*)malloc(sizeof(Path));

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
