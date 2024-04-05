#pragma once
#include "fileProcess.h"
#include "LinkList.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void cdCommand(tree *root, tree *currentDir, treeStackFather *stack) {
    char path[256], temp, *path_[256], *pPath = path;
    int count = 0;
    while((temp = getchar()) != '\n') {
        if(temp == '/') {
            *pPath = '\0';
            path_[count] = (char*)malloc(sizeof(char)*strlen(path)+1);
            strcpy(path_[count], path);
            count++;
            pPath = path;
        } else if(temp != 0) *(pPath++) = temp;
    }
    *pPath = '\0';
    path_[count] = (char*)malloc(sizeof(char)*strlen(path)+1);
    strcpy(path_[count], path);
    path_[++count] = NULL;
    gotoThePath(currentDir, root, path_, stack, count);
}


void wgetCommand(tree *currentDir) {
    char ch, *url = (char*)malloc(sizeof(char)*10000), *pUrl = url;
    while((ch = getchar()) != '\n') *(pUrl++) = ch;
    *pUrl = '\0';
    for(pUrl = url+strlen(url)-1; *pUrl != '/'; pUrl--);
    pUrl++;
    addChildNodeInTree(currentDir, pUrl);
    printf("Downloaded %s successfully from %s\n", pUrl, url);
    free(url);
}