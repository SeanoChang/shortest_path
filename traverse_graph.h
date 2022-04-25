#ifndef TRAVERSE_GRAPH_H
#define TRAVERSE_GRAPH_H

Path* shortestPath(Graph*, short, short, int);
PQ* buildPriorityQueue(Graph*, short, short, int);
PQ extractMinPQ(PQ*, int);
short findEndNode(PQ*, Graph*, short, short);
PathNode* buildShortestPath(PQ*, Graph*, PQ, short);
void downwardHeapify(PQ*, int, int);
void relaxAdjencent(Graph*, PQ*, PQ, short, short, int);
void relax(PQ*, PQ*, PQ*, int);

#endif
