#include <stdio.h>
#include <stdlib.h>
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

Path* shortestPath(Graph* graph, short row, short col, int start) {
    Path* path = buildPath();
    PQ* pq = buildPriorityQueue(graph, row, col, start);
    int pqSize = row*col;
    // add the start node to the path
    PQ s = extractMinPQ(pq, pqSize--);
    addToPath(path, &s);
    relaxAdjencent(graph, pq, s, row, col, pqSize);
    int i = 0;
    while(i++ < row*col-1) { // update all the nodes in the graph to the shortest time to reach from start node
        // after extracting the min, add the min to the path and update the pqsize
        PQ u = extractMinPQ(pq, pqSize--);
        // relax all four directions if possible
        relaxAdjencent(graph, pq, u, row, col, pqSize);
    }
    short endColIdx = findEndNode(pq, graph, row, col);
    printf("%hd\n", endColIdx);
    path->rear->next = buildShortestPath(pq, graph, s, endColIdx);
    PathNode* temp = path->rear;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    path->rear = temp;

    free(pq);
    return path;
}

PQ* buildPriorityQueue(Graph* graph, short row, short col, int start) {
    PQ* pq = malloc(sizeof(PQ) * (row*col+1));
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            graph->g[i][j].priority = i*col + j;
            pq[i*col+j].node = &graph->g[i][j];
            pq[i*col+j].time = -1;
            // only if the node is start then set the time to 0
            if(i == 0 && j == start) pq[i*col+j].time = 0;
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
    for(int i = (max_size-1)/2; i >= 0; i--) {
        downwardHeapify(pq, i, max_size-1);
    }
    
    return pq[max_size-1];
}

// downward heapify the PQ to maintain the min heap
void downwardHeapify(PQ* pq, int i, int max_size) {
    int l = 2*i;
    int r = 2*i+1;
    if(i == 0){
        l = 1;
        r = 2;
    }
    if(r < max_size && shouldHeapify(pq[l], pq[r])) {
        if(pq[l].time != -1) {
            if(pq[r].time != -1) {
                if(pq[l].time < pq[r].time) {
                    PQ temp = pq[l];
                    pq[l] = pq[i];
                    pq[i] = temp;
                    pq[i].node->priority = i;
                    pq[l].node->priority = l;
                    downwardHeapify(pq, l, max_size);  
                } else {
                    PQ temp = pq[r];
                    pq[r] = pq[i];
                    pq[i] = temp;
                    pq[i].node->priority = i;
                    pq[r].node->priority = r;
                    downwardHeapify(pq, r, max_size);
                }
            } else {
                PQ temp = pq[l];
                pq[l] = pq[i];
                pq[i] = temp;
                pq[i].node->priority = i;
                pq[l].node->priority = l;                
                downwardHeapify(pq, l, max_size);
            }
        } else {
            if(pq[r].time != -1) {
                PQ temp = pq[r];
                pq[r] = pq[i];
                pq[i] = temp;
                pq[i].node->priority = i;
                pq[r].node->priority = r;
                downwardHeapify(pq, r, max_size);
            }
        }
    }
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
        if(loc < max_size){
            relax(pq, &u, &pq[loc], max_size);  
        } 
    }
    // relax to the left
    if(u.node->col-1 >= 0) {
        int loc = graph->g[u.node->row][u.node->col-1].priority;
        if(loc < max_size){    
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
    if(v->time == -1) {
        v->time = u->time + u->node->time;
        v->pred = u->node;
    } else if(v->time > u->time + u->node->time) {
        v->time = u->time + u->node->time;
        v->pred = u->node;
    }

    for(int i = v->node->priority; i >= 0; i--){
        downwardHeapify(pq, i, max_size);
    }
}

short findEndNode(PQ* pq, Graph* graph, short row, short col){
    // the end node must be in the last row
    int fastest = pq[graph->g[row-1][0].priority].time + graph->g[row-1][0].time;
    short idx = 0;
    for(short i = 1; i < col; i++){
        if(fastest > pq[graph->g[row-1][i].priority].time + graph->g[row-1][i].time){
            fastest = pq[graph->g[row-1][i].priority].time + graph->g[row-1][i].time;
            idx = i;
        }
    }

    return idx;
}

PathNode* buildShortestPath(PQ* pq, Graph* graph, PQ startNode, short endColIdx) {
    short curRow = graph->row-1;
    printf("endNode: (%hd,%hd) start node: (%hd,%hd)\n", curRow,endColIdx, startNode.node->row, startNode.node->col);
    short curCol = endColIdx;
    PathNode** head = malloc(sizeof(PathNode*));
    *head = buildPathNode(&graph->g[graph->row-1][endColIdx]);
    while(curRow != startNode.node->row || curCol != startNode.node->col) {
        printf("current node: (%hd,%hd)\n", curRow, curCol);
        curRow = pq[graph->g[curRow][curCol].priority].pred->row;
        curCol = pq[graph->g[curRow][curCol].priority].pred->col;
        PathNode* temp = buildPathNode(pq[(*head)->node->priority].pred);
        temp->next = *head;
        *head = temp;
    }
    PathNode* dummy = *head;
    free(head);
    return dummy;
}
