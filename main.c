#define ElementType char
#include "class/CLIPath.h"
#include "class/LinkQuene.h"
#include "class/LinkStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    stack s, stemp;
    char path[255], command[255];
    s = initStack();
    stemp = initStack();
    push(&s, "workspace");
    printf("/ > ");
    while(1) {
        scanf("%s", command);
        if(!strcmp(command, "exit")) break;
        else if(!strcmp(command, "cd")) {
            scanf("%s", path);
            if(!strcmp(path, "..")) {
                pop(&s, path);
                if(!strcmp(path, "workspace")) {
                    printf("You are in the root directory\n");
                    push(&s, path);
                } else {
                    while(stackEmpty(s)) {
                        pop(&s, path);
                        push(&stemp, path);
                    }
                    while(stackEmpty(stemp)) {
                        pop(&stemp, path);
                        printf("/%s", path);
                        push(&s, path);
                    }
                }
                printf("> ");
            } else {
                push(&s, path);
                while(stackEmpty(s)) {
                    pop(&s, path);
                    push(&stemp, path);
                }
                while(stackEmpty(stemp)) {
                    pop(&stemp, path);
                    printf("/%s", path);
                    push(&s, path);
                }
                printf("> ");
            }
        }
    }
}