#include "Arithmetic.h"

Arithmetic::Arithmetic()
{
	RPN = NULL;
}

Arithmetic::Arithmetic(char* str)
{
	const int max = 100;
	int i = 0, j = 0;
	bool flag_abs = 0;												// Ôëàã äëÿ îïåğàöèè ìîäóëü 
	bool flag_var = 0;												// Ôëàã äëÿ ïğîâåğêè íàëè÷èÿ ïåğåìåííîé â ñòğóêòóğå

	RPN = new char[max];

	while (str[i] != '\0')
	{
		if ((str[i] >= '0') && (str[i] <= '9'))						// Åñëè ñèìâîë - ÷èñëî
		{
			while ((str[i] >= '0') && (str[i] <= '9'))
			{
				RPN[j++] = str[i++];
			}
			RPN[j++] = ' ';
		}
		else
		{
			if ((str[i] >= 'a') && (str[i] <= 'z'))					// Åñëè ñèìâîë - ïåğåìåííàÿ
			{
				RPN[j++] = str[i++];
				RPN[j++] = ' ';
			}
			else													// Åñëè ñèìâîë - îïåğàòîğ
			{
				if (ch_s.empty())
				{
					if (str[i] == '|')
						flag_abs = 1;
					else
						if ((str[i] != '(') && (i == 0))
							throw logic_error("Error description");
					ch_s.push(str[i++]);
				}
				else
				{
					switch (str[i])
					{
					case '+':
						if (priority(str[i]) <= priority(ch_s.top()))
						{
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.push('+');
						break;

					case '-':
						if (priority(str[i]) <= priority(ch_s.top()))
						{
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.push('-');
						break;

					case '*':
						if (priority(str[i]) <= priority(ch_s.top()))
						{
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.push('*');
						break;

					case '/':
						if (priority(str[i]) <= priority(ch_s.top()))
						{
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.push('/');
						break;

					case '^':
						if (priority(str[i]) < priority(ch_s.top()))
						{
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.push('^');
						break;

					case '(':
						ch_s.push('(');
						break;

					case ')':
						while (ch_s.top() != '(')
						{
							if ((ch_s.top() == '|') && (flag_abs == 1))
								throw logic_error("Error description");
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.pop();
						break;

					case '|':

						if (flag_abs == 0)
						{
							ch_s.push('|');
							flag_abs = 1;
						}
						else
						{
							while (ch_s.top() != '|')
							{
								if (ch_s.top() == '(')
									throw logic_error("Error description");
								RPN[j++] = ch_s.top();
								RPN[j++] = ' ';
								ch_s.pop();
							}
							RPN[j++] = ch_s.top();
							ch_s.pop();
							RPN[j++] = '|';
							RPN[j++] = ' ';
							flag_abs = 0;
						}
						break;
					}
					++i;
				}
			}
		}
	}


	while (!ch_s.empty())
	{
		if ((ch_s.top() == '(') || (ch_s.top() == ')'))
			throw logic_error("Error description");
		RPN[j++] = ch_s.top();
		ch_s.pop();
		if (!ch_s.empty())
			RPN[j++] = ' ';
	}
	RPN[j] = '\0';
}

Arithmetic::~Arithmetic()
{
	delete[] RPN;
	RPN = NULL;
}

int Arithmetic::priority(char op)
{
	switch (op)
	{
	case '(':
	case ')':
	case '|':
		return 0;
		break;
	case '+':
	case '-':
		return 1;
		break;
	case '*':
	case '/':
		return 2;
		break;
	case '^':
		return 3;
		break;
	default: throw logic_error("Error description");
	}
}

double Arithmetic::calculation(char* str, Variable* arr, int size)
{
	int i = 0;
	double temp = 0;
	double op1 = 0, op2 = 0;
	bool flag_var = 0;

	while (str[i] != '\0')
	{
		if ((str[i] >= '0') && (str[i] <= '9'))						// Åñëè ñèìâîë - ÷èñëî
		{
			while ((str[i] >= '0') && (str[i] <= '9'))
			{
				temp = temp * 10 + str[i++] - '0';
			}
			d_s.push(temp);
			temp = 0;
		}
		else
		{
			if ((str[i] >= 'a') && (str[i] <= 'z'))					// Åñëè ñèìâîë - ïåğåìåííàÿ
			{
				flag_var = 1;
				for (int k = 0; k < size; ++k)
					if (str[i] == (arr[k].name))
					{
						d_s.push(arr[k].value);
						flag_var = 0;
					}
				if (flag_var == 1)
					throw logic_error("Error description");
				++i;
			}
			else													// Åñëè ñèìâîë - îïåğàòîğ
			{
				if (d_s.empty())
					throw logic_error("Error description");
				else 
					switch (str[i])
					{
					case '+':
						op2 = d_s.top();
						d_s.pop();
						if (d_s.empty())
							throw logic_error("Error description");
						op1 = d_s.top();
						d_s.pop();
						d_s.push(op1 + op2);
						break;

					case '-':
						op2 = d_s.top();
						d_s.pop();
						if (d_s.empty())
							throw logic_error("Error description");
						op1 = d_s.top();
						d_s.pop();
						d_s.push(op1 - op2);
						break;

					case '*':
						op2 = d_s.top();
						d_s.pop();
						if (d_s.empty())
							throw logic_error("Error description");
						op1 = d_s.top();
						d_s.pop();
						d_s.push(op1 * op2);
						break;

					case '/':
						if (d_s.top() == 0)
							throw logic_error("Error description");
						op2 = d_s.top();
						d_s.pop();
						if (d_s.empty())
							throw logic_error("Error description");
						op1 = d_s.top();
						d_s.pop();
						d_s.push(op1 / op2);
						break;

					case '^':
						op2 = d_s.top();
						d_s.pop();
						if (d_s.empty())
							throw logic_error("Error description");
						op1 = d_s.top();
						d_s.pop();
						d_s.push(pow(op1, op2));
						break;

					case '|':
						if (d_s.top() < 0)
						{
							op1 = d_s.top();
							d_s.pop();
							d_s.push(-op1);
						}
						break;
					}
				++i;
			}
		}
	}
	return d_s.top();
}