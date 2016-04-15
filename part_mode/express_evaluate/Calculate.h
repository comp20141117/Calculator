#ifndef _CALCULATE_H_
#define _CALCULATE_H_

#include "Stack.h"
/*put infix expression(infix) to postfix expression(postfix)*/
/*eg: put "3+5\n" to "3 5 +" */
Status InfixToPostfix(char *infix, char *postfix);

/*calulation the postfix expression(arr)*/
/*eg: "3 5 +" = 8 */
Status Calculate(char *arr, void *result);

#endif
