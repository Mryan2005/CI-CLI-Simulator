#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct path_ {
    char *data;
    struct path_ *bro;
    struct path_ *child;
    struct path_ *dad;
} path_;
typedef path_* path;
void loadFile(FILE *f, path *PATH) {
    path PATH_ = *PATH, root = PATH_, line, sub;
    PATH_->bro = NULL;
    PATH_->child = NULL;
    PATH_->dad = NULL;
    char ch[256];
    while(fscanf(f, "%s", ch) != EOF) {
        if(ch[0] == '\\') {
            if(root->child == NULL) {
                root->child = (path)malloc(sizeof(path_));
                root->child->data = (char*)malloc(sizeof(char)*strlen(ch)+1);
                for(int i = 0; i < strlen(ch); i++) if(ch[i] != '\\' && ch[i] != '\r') root->child->data[i] = ch[i];
                root->child->dad = root;
                root->child->bro = NULL;
                root->child->child = NULL;
            } else {
                line = root->child;
                while(line->bro != NULL) line = line->bro;
                line->bro = (path)malloc(sizeof(path_));
                line->bro->data = (char*)malloc(sizeof(char)*strlen(ch)+1);
                for(int i = 0; i < strlen(ch); i++) if(ch[i] != '\\' && ch[i] != '\r') line->bro->data[i-1] = ch[i];
                line->bro->dad = root;
                line->bro->bro = NULL;
                line->bro->child = NULL;
            }
        } else {
            if(root->bro == NULL) {
                root->bro = (path)malloc(sizeof(path_));
                root->bro->data = (char*)malloc(sizeof(char)*strlen(ch)+1);
                strcpy(root->bro->data, ch);
                root->bro->dad = root->dad;
                root->bro->bro = NULL;
                root->bro->child = NULL;
                root = root->bro;
            } else {
                sub = root->bro;
                while(sub->bro != NULL) sub = sub->bro;
                sub->bro = (path)malloc(sizeof(path_));
                sub->bro->dad = root->dad;
                sub->bro->bro = NULL;
                sub->bro->child = NULL;
                root = sub->bro;
            }
        }
    }
}
void addData(path *node) {
    char dataTemp[256], ch;
    int count = 0;
    while((ch = getchar()) != '\n') dataTemp[count++] = ch;
    char *data = (char*)malloc(sizeof(char)*(count+1)), *p = data;
    for(int i = 0; i < count; i++) {
        *p = dataTemp[i];
    }
    *p = 0;
    (*node)->data = data;
}
void gotoDir(path *PATH) {
    ;
}