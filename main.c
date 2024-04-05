#include "class/fileProcess.h"
#include "class/LinkList.h"
#include "class/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void preLoad(tree *root) {
    linkList list;
    initLinkList(&list);
    FILE *fp = fopen("data/systemDir", "r");
    if(fp == NULL) {
        printf("File not found\n");
        exit(1);
    }
    readFileLine(fp, &list);
    fclose(fp);
    addTreeNode(root, list);
}
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
        } else if(temp != 0){
            *(pPath++) = temp;
        }
    }
    *pPath = '\0';
    path_[count] = (char*)malloc(sizeof(char)*strlen(path)+1);
    strcpy(path_[count], path);
    path_[++count] = NULL;
    gotoThePath(currentDir, root, path_, stack, count);
}
int main() {
    treeStackFather currentDirFather = NULL;
    tree sysDir = NULL, curDir = NULL;
    preLoad(&sysDir);
    goPath(&sysDir, &curDir, &currentDirFather);
    char command[256];
    while(1) {
        printf("%s > ", curDir->data);
        scanf("%s ", command);
        if(strcmp(command, "cd") == 0) {
            cdCommand(&sysDir, &curDir, &currentDirFather);
        }
    }
}