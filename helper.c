#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "helper.h"

int shouldHeapify(PQ l, PQ r, PQ i) {
    // if both children are -1 then don't heapify
    if(l.time == -1 && r.time == -1) return 0;
    if(i.time != -1){
        if(l.time != -1 && r.time != -1) {
            if(l.time < i.time || r.time < i.time) return 1;
        }  else if(l.time != -1) {
            if(l.time < i.time) return 1;
        }  else if(r.time != -1) {
            if(r.time < i.time) return 1;
        }
        return 0;
    }
    return 1;
}

void addToPath(Path* path, PQ* u) {
    if(path->front == NULL) {
        path->front = buildPathNode(u->node);
        path->rear = path->front;
    } else {
        if(isAdjencent(path->rear->node, u->node)) {
            path->rear->next = buildPathNode(u->node);
            path->rear = path->rear->next;
        } else {
            u->time = -1;
            return;
        }
    }
    path->size++;
    path->time += u->node->time;
}

int isAdjencent(GraphNode* u, GraphNode* v) {
    if(u->row == v->row) {
        if(u->col == v->col-1) return 1;
        if(u->col == v->col+1) return 1;
    } else if(u->col == v->col) {
        if(u->row == v->row-1) return 1;
        if(u->row == v->row+1) return 1;
    }
    return 0;
}
