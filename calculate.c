#include "calculate.h"

#define BUFFERSIZE 100

void my_err(char *str)
{
	perror(str);
	exit(1);
}

Status InfixToPostfix(char *infix, char *postfix)
{
	Stack A;
	Stack *S = &A;
	if (InitStack(S, MAXSIZE*sizeof(char), sizeof(char)) == ERROR){
		my_err("InfixToPostfix init stack error!");
	}
	char c, e;
	int j = 0, i = 0;
	c = *(infix + i);
	i++;
	while ('\n'!= c){
		while(c == '.' || (c >= '0' && c <= '9')){
			postfix[j++] = c;
			c = *(infix + i);
			i++;
			if(c != '.' && (c < '0' || c > '9'))
				postfix[j++] = ' ';
		}
		if (')' == c){
			Pop(S, (void *)&e);
			while ('(' != e){
				postfix[j++] = e;
				postfix[j++] = ' ';
				Pop(S, (void *)&e);
			}
		}else if ('+' == c || '-' == c){
			if(!GetLen(S)){
				Push(S, (void *)&c);
			}else{
				do{
					Pop(S, (void *)&e);
					if ('(' == e){
						Push(S, (void *)&e);
					}else{
						postfix[j++] = e;
						postfix[j++] = ' ';
					}
				} while (GetLen(S) && '(' != e);
				Push(S, (void *)&c);
			}
		}
		else if ('*' == c || '/' == c || '(' == c){
			Push(S, (void *)&c);
		}
		else if ('\n'== c){
			break;
		}else{
			return FALSE;
		}
		c = *(infix + i);
		i++;
	}
	while(GetLen(S)){
		Pop(S, (void *)&e);
		postfix[j++] = e;
		postfix[j++] = ' ';
	}
	DestroyStack(S);
	return OK;
}

Status Calculate(char *arr, void *result)
{
	double d, e, f;
	Stack A;
	Stack *S = &A;
	char *op;
	char *buf = arr;
	char *saveptr = NULL;
	if(InitStack(S, MAXSIZE*sizeof(double), sizeof(double)) == ERROR){
		my_err("stack init error!");
	}
	while((op = strtok_r(buf, " ", &saveptr)) != NULL){
		buf = NULL;
		switch(op[0]){
		case '+':
			Pop(S, &e);
			Pop(S, &d);
			f = d + e;
			Push(S, &f);
			break;
		case '-':
			Pop(S, &e);
			Pop(S, &d);
			f = d - e;
			Push(S, &f);
			break;
		case '*':
			Pop(S, &e);
			Pop(S, &d);
			f = d * e;
			Push(S, &f);
			break;
		case '/':
			Pop(S, &e);
			Pop(S, &d);
			f = d / e;
			Push(S, &f);
			break;
		default:
			d = atof(op);
			Push(S, &d);
			break;
		}
	}
	Pop(S, result);
	DestroyStack(S);
	return OK;
}
