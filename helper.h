#ifndef HELPER_H
#define HELPER_H

int reachedBottom(Path*, short);
int shouldHeapify(PQ, PQ);
void addToPath(Path*, PQ*);
int isAdjencent(GraphNode*, GraphNode*); 

#endif
