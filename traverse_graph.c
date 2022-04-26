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
    PQ s = pq[0];
    while(pqSize > 0) { // update all the nodes in the graph to the shortest time to reach from start node
        // after extracting the min, add the min to the path and update the pqsize
        PQ u = extractMinPQ(pq, pqSize--);
        // relax all four directions if possible
        relaxAdjencent(graph, pq, u, row, col, pqSize);
    }
    short endColIdx = findEndNode(pq, graph, row, col);
    path->front = buildShortestPath(pq, graph, s, endColIdx);
    path->rear = path->front;
    PathNode* temp = path->rear;
    while(temp->next != NULL) {
        path->time += temp->node->time;
        path->size++;
        temp = temp->next;
    }
    path->time += temp->node->time;
    path->size++;

    free(pq);
    return path;
}

/*
build the priority queue for maintaining the shortest path to each node
*/
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
    downwardHeapify(pq, 0, max_size-1);
    
    return pq[max_size-1];
}

// downward heapify the PQ to maintain the min heap
void downwardHeapify(PQ* pq, int i, int max_size) {
    int j = 2*i+1;
    PQ temp = pq[i];
    while(j <= max_size) {
        printf("j: %d max_size: %d\n", j, max_size);
        if(j < max_size){
            if(j < max_size && pq[j].time != -1 && pq[j+1].time != -1) {
                if(pq[j].time > pq[j+1].time) {
                    j++;
                } 
            } else if(j < max_size && pq[j+1].time != -1) {
                j++;
            }
            printf("i: %d j: %d max_size: %d\n", i, j, max_size);
            if(temp.time > pq[j].time) {
                pq[i] = pq[j];
                pq[i].node->priority = i;
                i = j;
                j = 2*i+1;
            } else {
                break;
            }
            printf("i: %d j: %d max_size: %d\n", i, j, max_size);
        } else {
            printf("!i: %d j: %d max_size: %d\n", i, j, max_size);
            if(pq[j].time != -1) {
                if(temp.time > pq[j].time) {
                    pq[i] = pq[j];
                    pq[i].node->priority = i;
                    i = j;
                    j = 2*i+1;
                } else {
                    break;
                }
                printf("?i: %d j: %d max_size: %d\n", i, j, max_size);
            } else {
                break;
            }
        }
    }
    printf("->i: %d j: %d max_size: %d\n", i, j, max_size);
    pq[i] = temp;
    pq[i].node->priority = i;
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

    for(int i = max_size/2; i >= 0; i--) {
        downwardHeapify(pq, i, max_size);
    }
}

/*
find the end node that has the shortest time to exit the graph
*/
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

/*
the function find the shortest path from the start node to the end node with the given end column index
each PQ struct stores the predecessor of the node 
find each node's predecessor and stack up the path to return
*/
PathNode* buildShortestPath(PQ* pq, Graph* graph, PQ startNode, short endColIdx) {
    short curRow = graph->row-1;
    short curCol = endColIdx;
    PathNode** head = malloc(sizeof(PathNode*));
    *head = buildPathNode(&graph->g[graph->row-1][endColIdx]);

    while(curRow != startNode.node->row || curCol != startNode.node->col) {
        short tmpRow = curRow;
        curRow = pq[graph->g[curRow][curCol].priority].pred->row;
        curCol = pq[graph->g[tmpRow][curCol].priority].pred->col;
        PathNode* temp = buildPathNode(pq[(*head)->node->priority].pred);
        temp->next = *head;
        *head = temp;
    }

    PathNode* dummy = *head;
    free(head);
    return dummy;
}
