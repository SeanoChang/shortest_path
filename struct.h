#ifndef STRUCH_H
#define STRUCH_H

typedef struct GraphNode{
    int priority;
    short time;
    short row;
    short col;
} GraphNode;

typedef struct Graph {
    short row;
    short col;
    GraphNode** g;
} Graph;

typedef struct PathNode{
    GraphNode* node;
    struct PathNode* next;
} PathNode;

typedef struct Path{
    int time;
    int size;
    PathNode* front;
    PathNode* rear;
} Path;

typedef struct PQ {
    GraphNode* node;
    int time;
    GraphNode* pred;
} PQ;


Path* buildPath();
PathNode* buildPathNode(GraphNode*);
void destroyPaths(Path**, short, int);
void destroyPath(Path*);

#endif
