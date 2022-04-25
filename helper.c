#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "helper.h"

/*
determine whether the priority queue needs to be heapified 
if not, return 0 so that the heapify function can be skipped
*/
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
