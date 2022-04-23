#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

Node* buildNode(short row, short col, short time){
    Node* nd = (Node*)malloc(sizeof(Node));

    nd->row = row;
    nd->col = col;
    nd->time = time;
    nd->next = NULL;

    return nd;
}

Path* buildPath(){
    Path* path = (Path*)malloc(sizeof(Path));

    path->time = 0;
    path->size = 0;
    path->head = NULL;

    return path;
}

void destroyList(Node* head){
    while(head!= NULL){
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}
