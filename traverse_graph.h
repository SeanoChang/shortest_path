#ifndef TRAVERSE_GRAPH_H
#define TRAVERSE_GRAPH_H

Path** shortestPaths(Graph*, short, short);
PQ* buildPriorityQueue(Graph*, short, short);
PQ extractMinPQ(PQ*, int);
short findEndNode(PQ*, Graph*, short, short);
Path* buildShortestPath(PQ*, Graph*, PQ, short);
void downwardHeapify(PQ*, int, int);
void relaxAdjencent(Graph*, PQ*, PQ, short, short, int);
void relax(PQ*, PQ*, PQ*, int);

#endif
