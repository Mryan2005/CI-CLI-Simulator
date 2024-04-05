#include "class/fileProcess.h"
#include "class/LinkList.h"
#include "class/tree.h"
#include "class/commands.h"
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
        } else if(strcmp(command, "wget") == 0) {
            wgetCommand(&curDir);
        } 
    }
}