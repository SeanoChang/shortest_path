#ifndef STRUCH_H
#define STRUCH_H

typedef struct Node{
    int row;
    int col;
    int time;
    struct Node *next;
} Node;

typedef struct Path{
    int time;
    int size;
    Node *head;
} Path;

typedef struct PQ {
    short row;
    short col;
    int time;
    short pred_row;
    short pred_col;
} PQ;

Node* buildNode(short, short, short);
Path* buildPath();
void destroyList(Node*);

#endif
