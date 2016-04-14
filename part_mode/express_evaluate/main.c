#include "Calculate.h"

#define BUFFERSIZE 100

int main(int argc, char *argv[])
{
	char src[BUFFERSIZE] = {'\0'};
	char *infix = src;
	char postfix[BUFFERSIZE] = {'\0'};
	fgets(infix, BUFFERSIZE, stdin);
	printf("\ninfix is %s", infix);
	InfixToPostfix(infix, postfix);
	printf("\npostfix is %s", postfix);
	double result;
	Calculate(postfix, &result);
	printf("\nthe rusult is %lf", result);
	return 0;
}
