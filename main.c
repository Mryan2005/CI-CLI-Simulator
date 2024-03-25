#include "class/CLIPath.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
    // create a path
    path PATH = (path)malloc(sizeof(path_));
    PATH->data = (char*)malloc(sizeof(char)*2);
    PATH->data[0] = '/';
    FILE *file = fopen("./data/systemDir", "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        return 1;
    }
    loadFile(file, &PATH);
}