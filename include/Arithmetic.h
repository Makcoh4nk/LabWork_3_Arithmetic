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
	int priority(char);

public:

	Arithmetic();
	Arithmetic(char*);
	~Arithmetic();

	double calculation(char*, Variable*, int);
	char* getRPN() { return RPN; }
};

