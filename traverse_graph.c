#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "struct.h"
#include "helper.h"
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

Path** shortestPaths(Graph* graph, short row, short col) {
    PQ* pq = buildPriorityQueue(graph, row, col);
    int pqSize = row*col;
    while(pqSize > 0) { // update all the nodes in the graph to the shortest time to reach from start node
        // after extracting the min, add the min to the path and update the pqsize
        PQ u = extractMinPQ(pq, pqSize--);
        // relax all four directions if possible
        relaxAdjencent(graph, pq, u, row, col, pqSize);
    }
    Path** paths = malloc(sizeof(Path*)*(col+1));
    for(int i = 0; i < col; i++) {
        paths[i] = buildShortestPath(pq, graph, i);
    }

    free(pq);
    return paths;
}

/*
build the priority queue for maintaining the shortest path to each node
*/
PQ* buildPriorityQueue(Graph* graph, short row, short col) {
    PQ* pq = malloc(sizeof(PQ) * (row*col+1));
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            graph->g[i][j].priority = i*col + j;
            pq[i*col+j].node = &graph->g[i][j];
            pq[i*col+j].time = INT_MAX;
            // initialize the last row to zeros
            if(i == row-1) pq[i*col+j].time = 0;
            pq[i*col+j].pred = NULL;
        }
    }

    // create the min heap
    for(int i = row*col/2; i >= 0; i--) {
        downwardHeapify(pq, i, row*col);
    }

    return pq;
}

/*
extract the min from the heap -> the top of the heap
replace it with the last element and perform downward heapify
*/
PQ extractMinPQ(PQ* pq, int max_size) {
    PQ min = pq[0];
    pq[0] = pq[max_size-1];
    pq[max_size-1] = min;
    pq[0].node->priority = 0;
    pq[max_size-1].node->priority = max_size-1;
    downwardHeapify(pq, 0, max_size-1);
    
    return pq[max_size-1];
}

// downward heapify the PQ to maintain the min heap
void downwardHeapify(PQ* pq, int i, int max_size) {
    int max = max_size - 1;
    int j = 2*i+1;
    PQ temp = pq[i];
    while(j <= max) {
        if(j < max && pq[j].time > pq[j+1].time) {
            j++;
        }
        if(temp.time <= pq[j].time) {
            break;
        } else {
            pq[i] = pq[j];
            pq[i].node->priority = i;
            i = j;
            j = 2*i+1;
        }
    }
    pq[i] = temp;
    pq[i].node->priority = i;
}

// upward heapify the PQ to maintain the min heap
void upwardHeapify(PQ* pq, int i, int max_size) {
    PQ temp = pq[i];
    int c = i;
    int p = (c-1)/2;
    while(c > 0 && pq[p].time > temp.time) {
        pq[c] = pq[p];
        pq[c].node->priority = c;
        c = p;
        p = (c-1)/2;
    }
    pq[c] = temp;
    pq[c].node->priority = c;
}

/*
the adjencent nodes are the nodes that are one step away from the current node -> right, left, bot, and top
for each direction, relax the node if it less than the current time.
The initial value for each node is set to -1.
*/
void relaxAdjencent(Graph* graph, PQ* pq, PQ u, short row, short col, int max_size) {
    // relax to the bot
    if(u.node->row+1 < row) {
        int loc = graph->g[u.node->row+1][u.node->col].priority;
        if(loc  < max_size){
            relax(pq, &u, &pq[loc], max_size);
        }
    }
    // relax to the right
    if(u.node->col+1 < col) {
        int loc = graph->g[u.node->row][u.node->col+1].priority;
        // if the right is also last row, dont relax
        if(loc < max_size && pq[loc].node->row != row-1) {
            relax(pq, &u, &pq[loc], max_size); 
        } 
    }
    // relax to the left
    if(u.node->col-1 >= 0) {
        int loc = graph->g[u.node->row][u.node->col-1].priority;
        // if the left is also last row, dont relax
        if(loc < max_size && pq[loc].node->row != row-1){    
            relax(pq, &u, &pq[loc], max_size);
        }
    }
    // relax to the top
    if(u.node->row-1 >= 0) {
        int loc = graph->g[u.node->row-1][u.node->col].priority;
        if(loc  < max_size){
            relax(pq, &u, &pq[loc], max_size);
        }
    }
}

void relax(PQ* pq, PQ* u, PQ* v, int max_size) {
    if(v->time > u->time + u->node->time) {
        v->time = u->time + u->node->time;
        v->pred = u->node;
        upwardHeapify(pq, v->node->priority, max_size);
    }
}

/*
the function find the shortest path from the start node to the end node with the given end column index
each PQ struct stores the predecessor of the node 
find each node's predecessor and stack up the path to return
*/
Path* buildShortestPath(PQ* pq, Graph* graph, short endColIdx) {
    short curRow = 0;
    short curCol = endColIdx;
    Path* path = buildPath();
    path->front = buildPathNode(&graph->g[curRow][curCol]);
    path->rear = path->front;
    path->time += path->front->node->time;
    path->size += 1;

    while(curRow != graph->row-1) {
        short tmpRow = curRow;
        curRow = pq[graph->g[curRow][curCol].priority].pred->row;
        curCol = pq[graph->g[tmpRow][curCol].priority].pred->col;
        PathNode* temp = buildPathNode(pq[path->rear->node->priority].pred);
        path->rear->next = temp;
        path->rear = temp;
        path->time += temp->node->time;
        path->size += 1;
    }

    return path;
}
