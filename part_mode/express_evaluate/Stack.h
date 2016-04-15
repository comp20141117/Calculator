#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR -1
#define FALSE 0
#define MAXSIZE 100

typedef int Status;

typedef struct _STACK
{
	void *base;
	void *top;
	int stacksize;
	int typesize;
}Stack;

Status InitStack(Stack * stack, unsigned stacksize, unsigned typesize);
Status DestroyStack(Stack *stack);
Status Push(Stack *stack, void *e);
Status Pop(Stack *stack, void *e);
Status GetLen(Stack *stack);

#endif
