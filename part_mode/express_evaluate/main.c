#include <stdio.h>
#include "Stack.h"

#define BUFFERSIZE 100

int main(int argc, char *argv[])
{
	Stack A;
	Stack *B = &A;
	char e;
	InitStack(B, MAXSIZE*sizeof(char), sizeof(char));
	e = 'a';
	Push(B, (void *)&e);
	printf("leng:%d\n",GetLen(B));
	Pop(B, (void *)&e);
	DestroyStack(B);
	return 0;
}
