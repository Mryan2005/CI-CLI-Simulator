#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkList.h"


typedef struct treeNode {
    char *data;
    struct treeNode *bro;
    struct treeNode *child;
} treeNode;
typedef treeNode* tree;


typedef struct treeStackFatherNode {
    treeNode *treenode;
    struct treeStackFatherNode *next;
} treeStackFatherNode;
typedef treeStackFatherNode* treeStackFather;


void treeStackPush(treeStackFather *stack, treeNode *treenode) {
    if(!*stack) {
        *stack = (treeStackFatherNode*)malloc(sizeof(treeStackFatherNode));
        (*stack)->treenode = treenode;
        (*stack)->next = NULL;
    } else {
        treeStackFatherNode *p = (treeStackFatherNode*)malloc(sizeof(treeStackFatherNode));
        p->treenode = treenode;
        p->next = *stack;
        *stack = p;
    }
}


treeNode *treeStackPop(treeStackFather *stack) {
    if(!*stack) return NULL;
    else {
        treeStackFatherNode *p = *stack;
        treeNode *q = p->treenode;
        (*stack) = (*stack)->next;
        free(p);
        return q;
    }
}


void clearTreeStack(treeStackFather *stack) {
    treeStackFatherNode *p = *stack, *q;
    while(p) {
        q = p;
        p = p->next;
        free(q);
    }
    *stack = NULL;
}


void tansferStackToStack(treeStackFather *stack1, treeStackFather *stack2) {
    treeStackFatherNode *p = *stack1, *q;
    while(p) {
        q = p;
        p = p->next;
        treeStackPush(stack2, q->treenode);
        free(q);
    }
    *stack1 = NULL;
}

void addTreeNode(tree *t, linkList L) {
    treeNode *tp = *t;
    treeStackFather stack = NULL;
    linkNode *lnode = L->next, *lnodeLast = L->next;
    while(lnode) {
        if(!*t) {
            tp = (treeNode*)malloc(sizeof(treeNode));
            tp->data = (char*)malloc(sizeof(char) * strlen(lnode->data) + 1);
            strcpy(tp->data, lnode->data);
            tp->bro = NULL;
            tp->child = NULL;
            *t = tp;
            lnode = lnode->next;
        } else {
            if(lnode->depth > lnodeLast->depth) {
                for(int i = lnodeLast->depth; i < lnode->depth; i++) treeStackPush(&stack, tp);
                tp->child = (treeNode*)malloc(sizeof(treeNode));
                tp = tp->child;
                tp->data = (char*)malloc(strlen(lnode->data) + 1);
                strcpy(tp->data, lnode->data);
                tp->bro = NULL;
                tp->child = NULL;
            } else if(lnode->depth < lnodeLast->depth) {
                for(int i = lnodeLast->depth; i > lnode->depth; i--) tp = treeStackPop(&stack);
                while(tp->bro) tp = tp->bro;
                tp->bro = (treeNode*)malloc(sizeof(treeNode));
                tp = tp->bro;
                tp->data = (char*)malloc(strlen(lnode->data) + 1);
                strcpy(tp->data, lnode->data);
                tp->bro = NULL;
                tp->child = NULL;
            } else {
                while(tp->bro) tp = tp->bro;
                tp->bro = (treeNode*)malloc(sizeof(treeNode));
                tp = tp->bro;
                tp->data = (char*)malloc(strlen(lnode->data) + 1);
                strcpy(tp->data, lnode->data);
                tp->bro = NULL;
                tp->child = NULL;
            }
            lnodeLast = lnode;
            lnode = lnode->next;
        }
    }
}


void addBroNodeInTree(tree *t, char *data) {
    treeNode *p = *t;
    while(p->bro) p = p->bro;
    p->bro = (treeNode*)malloc(sizeof(treeNode));
    p = p->bro;
    p->data = (char*)malloc(strlen(data) + 1);
    strcpy(p->data, data);
    p->bro = NULL;
    p->child = NULL;
}


void addChildNodeInTree(tree *t, char *data) {
    treeNode *p = *t;
    if(p->child) {
        p = p->child;
        while(p->bro) p = p->bro;
        p->bro = (treeNode*)malloc(sizeof(treeNode));
        p = p->bro;
        p->data = (char*)malloc(strlen(data) + 1);
        strcpy(p->data, data);
        p->bro = NULL;
        p->child = NULL;
    } else {
        p->child = (treeNode*)malloc(sizeof(treeNode));
        p = p->child;
        p->data = (char*)malloc(strlen(data) + 1);
        strcpy(p->data, data);
        p->bro = NULL;
        p->child = NULL;
    }
}

void goPath(tree *t, tree *currentPosition, treeStackFather *stack) {
    tree p = *t;
    treeStackPush(stack, p);
    p = (*t)->child;
    for(; p->bro; p = p->bro) if(strcmp(p->data, "home") == 0) {
        treeStackPush(stack, p);
        p = p->child;
        *currentPosition = p;
        break;
    }
}

void gotoThePath(tree *currentPosition, tree *t, char **path, treeStackFather *stack, int pathLength) {
    tree p = NULL, lastP = NULL;
    treeStackFather tempStack = NULL;
    if(**path == 0) {
        p = *t;
        // clearTreeStack(stack);
        tansferStackToStack(stack, &tempStack);
        treeStackPush(stack, p);
        for(int i = 1; i < pathLength; i++) {
            for(p = p->child; p->bro; p = p->bro) if(strcmp(p->data, path[i]) == 0) goto out1;
            if(strcmp(p->data, path[i]) == 0) goto out1;
            printf("cd: No such directory %s\n", path[i]);
            tansferStackToStack(&tempStack, stack);
            return;
            out1:;
        }
    } else {
        p = *currentPosition;
        for(int i = 0; i < pathLength && *(path[i]); i++) {
            if(strcmp(path[i], "..") == 0) {
                lastP = p;
                p = treeStackPop(stack);
                if(!p) {
                    printf("cd: You are already in the root directory\n");
                    treeStackPush(stack, lastP);
                    *currentPosition = lastP;
                    return;
                }
            } else {
                if(p->child) {
                    treeStackPush(stack, p);
                    p = p->child;
                    if(strcmp(p->data, path[i]) == 0) goto out;
                    for(; p->bro; p = p->bro) if(strcmp(p->data, path[i]) == 0) goto out;
                    if(strcmp(p->data, path[i]) == 0) goto out;
                    printf("cd: No such directory %s\n", path[i]);
                    return;
                    out:;
                } else {
                    printf("cd: No such directory %s\n",  path[i]);
                    return;
                }
            }
        }
    }
    *currentPosition = p;
}
