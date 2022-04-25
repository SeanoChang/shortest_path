#ifndef TRAVERSE_GRAPH_H
#define TRAVERSE_GRAPH_H

Path* shortestPath(Graph*, short, short, int);
PQ* buildPriorityQueue(Graph*, short, short, int);
int reachedBottom(Path*, short);
PQ extractMinPQ(PQ*, int);
void downwardHeapify(PQ*, int, int);
int shouldHeapify(PQ, PQ, PQ);
void addToPath(Path*, PQ);
void relaxAdjencent(Graph*, PQ*, PQ, short, short, int);
void relax(PQ*, PQ, PQ, int);

#endif
