#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct linkNode {
    char *data;
    int depth;
    struct linkNode *next;
} linkNode;
typedef linkNode* linkList;


void initLinkList(linkList *L) {
    *L = (linkNode*)malloc(sizeof(linkNode));
    (*L)->data = NULL;
    (*L)->next = NULL;
}


void addLinkNode(linkList *L, char *data, int depth) {
    linkNode *node = (linkNode*)malloc(sizeof(linkNode));
    node->data = (char*)malloc(sizeof(char)*strlen(data));
    strcpy(node->data, data);
    node->depth = depth;
    linkNode *p = *L;
    while(p->next) p = p->next;
    p->next = node;
    node->next = NULL;
}