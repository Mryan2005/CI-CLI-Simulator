#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ElementType char
typedef struct StackNode {
	ElementType data[255];
	struct StackNode *next;
} stackNode;
typedef stackNode *stack;
stack initStack() {
	stack stack_ = NULL;
	return stack_;
}
void clearStack(stack *stack_) {
	stackNode *p = *stack_;
	while(p) {
		*stack_ = p->next;
		free(p);
		p = *stack_;
	}
	*stack_ = NULL;
}
void push(stack *stack_, ElementType *data) {
	stackNode *p;
	p = (stackNode *)malloc(sizeof(stackNode));
	strcpy(p->data, data);
	p->next = *stack_;
	*stack_ = p;
}
void pop(stack *stack_, ElementType *data) {
	stackNode *p = *stack_;
	strcpy(data, p->data);
	*stack_ = p->next;
	free(p);
}
int getStackLength(stack stack_) {
	int count = 0;
	stackNode *p = stack_;
	while(p) {
		count++;
		p = p->next;
	}
	return count;
}
int stackEmpty(stack stack_) {
	return stack_? 1: 0;
}
