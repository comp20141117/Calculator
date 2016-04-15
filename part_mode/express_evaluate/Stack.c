#include "Stack.h"

Status InitStack(Stack * stack, unsigned stacksize, unsigned typesize)
{
	stack->base = malloc(stacksize);
	if(!stack->base)
		return ERROR;
	stack->top = stack->base;
	stack->stacksize = stacksize;
	stack->typesize = typesize;
	return OK;
}


Status DestroyStack(Stack *stack)
{
	free(stack->base);
	stack->top = stack->base = NULL;
	stack->stacksize = stack->typesize = 0;
	return OK;
}

Status Push(Stack *stack, void *e)
{
	if((unsigned long)stack->top - (unsigned long)stack->base + (unsigned long)stack->typesize > (unsigned long)stack->stacksize){
		printf("stack is full!\n");
		return FALSE;
	}
	memcpy(stack->top, e, stack->typesize);
	stack->top = (void *)((unsigned long)stack->top + (unsigned long)stack->typesize);
	return OK;
}

Status Pop(Stack *stack, void *e)
{
	if(stack->top == stack->base){
		printf("stack is empty!\n");
		return FALSE;
	}
	stack->top = (void *)((unsigned long)stack->top - (unsigned long)stack->typesize);
	memcpy(e, stack->top, stack->typesize);
	return OK;
}

Status GetLen(Stack *stack)
{
	return (((unsigned long)stack->top - (unsigned long)stack->base) / (unsigned long)stack->typesize);
}
