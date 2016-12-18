#include "Stack.h"

int priority(char op)
{
	switch (op)
	{
	case '(':
		return 0;
		break;
	case ')':
		return 0;
		break;
	case '|':
		return 0;
		break;
	case '+':
		return 1;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 2;
		break;
	case '^':
		return 3;
		break;
	}
}
