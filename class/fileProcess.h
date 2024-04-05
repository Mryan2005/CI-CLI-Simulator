#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkList.h"


void detectFileType(char *fileName) {
    char *p = fileName;
    for(; *p != '.' && *p != '\0'; p++);
    if(*p == '\0') {
        printf("can't detect file type");
        exit(1);
    }
    if(strcmp(p, ".c") == 0) {
        printf("c file");
    } else if(strcmp(p, ".cpp") == 0) {
        printf("cpp file");
    } else if(strcmp(p, ".java") == 0) {
        printf("java file");
    } else if(strcmp(p, ".py") == 0) {
        printf("python file");
    } else if(strcmp(p, ".html") == 0) {
        printf("html file");
    } else if(strcmp(p, ".css") == 0) {
        printf("css file");
    } else if(strcmp(p, ".js") == 0) {
        printf("js file");
    } else if(strcmp(p, ".php") == 0) {
        printf("php file");
    } else if(strcmp(p, ".txt") == 0) {
        printf("txt file");
    } else {
        printf("other file");
    }
}


void readFileLine(FILE *fp, linkList *List) {
    char lineText[999];
    int depth = 0;
    char *p = NULL, *q = NULL;
    while(!feof(fp)) {
        fgets(lineText, 999, fp);
        if(lineText[strlen(lineText)-1] == '\n') lineText[strlen(lineText)-1] = '\0';
        for(p = lineText; *p == ' '; p++);
        if(*p == '}') {
            depth--;
            for(; *p == '}' && *p != '\0'; p++);
            if(*p == '\0') continue;
            addLinkNode(List, p, depth);
        } else if(*p == '{') {
            depth++;
        } else {
            q = p + strlen(p) - 1;
            if(*q == '{') {
                *q = '\0';
                for(q--; *q == ' '; q--) *q = '\0';
                addLinkNode(List, p, depth);
                depth++;
            } else {
                for(q--; *q == ' '; q--) *q = '\0';
                addLinkNode(List, p, depth);
            }
        }
    }
}