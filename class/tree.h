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
    if(!*stack) {
        return NULL;
    } else {
        treeStackFatherNode *p = *stack;
        treeNode *q = p->treenode;
        (*stack) = (*stack)->next;
        free(p);
        return q;
    }
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
                for(int i = lnodeLast->depth; i < lnode->depth; i++) {
                    treeStackPush(&stack, tp);
                }
                tp->child = (treeNode*)malloc(sizeof(treeNode));
                tp = tp->child;
                tp->data = (char*)malloc(strlen(lnode->data) + 1);
                strcpy(tp->data, lnode->data);
                tp->bro = NULL;
                tp->child = NULL;
            } else if(lnode->depth < lnodeLast->depth) {
                for(int i = lnodeLast->depth; i > lnode->depth; i--) {
                    tp = treeStackPop(&stack);
                }
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


void goPath(tree *t, tree *currentPosition, treeStackFather *stack) {
    tree p = *t;
    treeStackPush(stack, p);
    p = (*t)->child;
    for(; p->bro; p = p->bro) {
        if(strcmp(p->data, "home") == 0) {
            treeStackPush(stack, p);
            p = p->child;
            *currentPosition = p;
            break;
        }
    }
}

void gotoThePath(tree *currentPosition, tree *t, char **path, treeStackFather *stack, int pathLength) {
    char **pPath = path;
    tree p = NULL;
    if(**path == '\0') {
        p = *t;
    } else {
        p = *currentPosition;    
    }
    while(*pPath) {
        if(strcmp(*pPath, "..") == 0) {
            if(!*stack) {
                printf("you are in the root directory\n");
                break;
            }
            p = treeStackPop(stack);
            pPath++;
            goto out;
        } else {
            for(; p && p->bro; p = p->bro) {
                if(strcmp(p->data, *pPath) == 0) {
                    if(pPath != pPath+pathLength-1) {
                        goto out;
                    } else {
                        *currentPosition = p;
                        goto out2;
                    }
                }
            }
        }
        pPath++;
        goto out;
        out1:;
        printf("I can't find %s\n", *pPath);
        break;
        out:;
    }
    *currentPosition = p;
    out2:;
}
