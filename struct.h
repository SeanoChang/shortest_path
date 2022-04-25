#ifndef STRUCH_H
#define STRUCH_H

/*
priority is the index of the node in the priority queue -> easy for finding nodes
time, row, col is the basic information of the node
*/
typedef struct GraphNode{
    int priority;
    short time;
    short row;
    short col;
} GraphNode;

/*
Graph stores the graph itself
also stores the dimension of the graph
*/
typedef struct Graph {
    short row;
    short col;
    GraphNode** g;
} Graph;

/*
A pathnode stores the graphnode
*/
typedef struct PathNode{
    GraphNode* node;
    struct PathNode* next;
} PathNode;

/*
path stores the intire pathnodes that construct the shortest path
*/
typedef struct Path{
    int time;
    int size;
    PathNode* front;
    PathNode* rear;
} Path;

/*
node stores the graphnode it represents
time stores the time it takes from the start node to get this point
pred stores the predesessor node of this node
*/
typedef struct PQ {
    GraphNode* node;
    int time;
    GraphNode* pred;
} PQ;


Path* buildPath();
PathNode* buildPathNode(GraphNode*);
void destroyGraph(Graph*);
void destroyPaths(Path**, short, int);
void destroyPath(Path*);

#endif
