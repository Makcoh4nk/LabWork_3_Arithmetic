#include "Stack.h"

struct Variable
{
	char name;
	int value;
};

class Arithmetic
{
	char* RPN;
	MyStack <char> ch_s;
	MyStack <double> d_s;

public:

	Arithmetic();
	Arithmetic(char*);
	~Arithmetic();

	int priority(char);
	double calculation(char*, Variable*, int);
	char* getRPN() { return RPN; }
};

