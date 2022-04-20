#ifndef STRUCH_H
#define STRUCH_H

typedef struct Node{
    int row;
    int col;
    int time;
    struct Node *next;
} Node;

Node* buildNode(short, short, short);
void destroyList(Node*);

#endif
