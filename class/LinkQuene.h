#include <stdio.h>
#include <stdlib.h>
#define ElementType char
typedef struct LinkQueneNode {
	ElementType data;
	struct LinkQueneNode *next;
} QueneNode;
typedef struct Quene {
	QueneNode *head;
	QueneNode *last;
} Quene;
void initQuene(Quene *q) {
	q->head = q->last = NULL;
}
void EnQuene(Quene *q, ElementType data) {
	if(!q->head) {
		q->head = (QueneNode*)malloc(sizeof(QueneNode));
		q->head->data = data;
		q->head->next = NULL;
		q->last = q->head;
	} else {
		q->last->next = (QueneNode*)malloc(sizeof(QueneNode));
		q->last = q->last->next;
		q->last->data = data;
		q->last->next = NULL;
	}
}
int QueueEmpty(Quene q) {
	return !q.head && !q.last? 1:0;
}
ElementType DeQuene(Quene *q) {
	QueneNode *p = q->head;
	ElementType data;
	if(p){
		data = q->head->data;
		q->head = q->head->next;
		if(p == q->last) q->last = NULL;
		free(p);
	} else printf("NONE\n");
	return data;
}
int countQueneNode(Quene q) {
	int count = 0;
	QueneNode *p = q.head;
	while(p) {
		count++;
		p = p->next;
	}
	return count;
}
void clearQuene(Quene *q) {
	while(q->head && q->last) DeQuene(q);
}
