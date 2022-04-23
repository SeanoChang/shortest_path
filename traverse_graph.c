#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "traverse_graph.h"

/* 
For each node at the top row, we need to find the shortest path to the bottom row.
Once I get to a node at the bottom row, I return the shortest Path
set S = null
PQ = G,V
while PQ is not empty
    u = extract min(PQ)
    S = S U {u}
    for each v in adj(u)
        relax(u, v, w(u, v))
*/

Path* shortesetPath(short** g, short row, short col) {
    Path* path = buildPath();
    PQ* pq = buildPiorityQueue(g, row, col);
    PQ* front = pq;
    while(!reachedBottom(pq, row)) {
        PQ u = extractMinPQ(pq, row*col);
        path = addToPath(u.row, u.col, u.time);
        
    }
    free(front);
}

PQ* PriorityQueue(short** g, short row, short col) {
    PQ* pq = malloc(sizeof(PQ) * (row*col+1));

    for(int i = 0; i < row*col; i++) {
        pq[i].time = -1;
        pq[i].pred_col = -1;
        pq[i].pred_row = -1;
    }
    pq[row*col].time = -2;
    return pq;
}

int reachedBottom(PQ* pq, short row) {
    if((*pq).row == row) return 1;
    return 0;
}

PQ extractMinPQ(PQ* pq, int max_size) {
    PQ min = *pq;
    *pq = *(pq+1);
}

// downward heapify the PQ to maintain the min heap
void downwardHeapify(PQ* pq, int i, int max_size) {
    int l = 2*i;
    int r = 2*i+1;
    if(l < max_size && (pq[l].time > pq[i].time || pq[r].time > pq[i].time)) {
        if(pq[l].time < pq[r].time) {
            PQ temp = pq[l];
            pq[l] = pq[i];
            pq[i] = temp;
            downwardHeapify(pq, l, max_size);
        } else {
            PQ temp = pq[r];
            pq[r] = pq[i];
            pq[i] = temp;
            downwardHeapify(pq, r, max_size);
        }
    }
}
