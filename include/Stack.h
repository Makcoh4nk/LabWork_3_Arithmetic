#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

template <class T>
struct CNode
{
	T data;
	CNode* next;
};

//-----------------------------------------

template <class T>
class MyStack
{
	CNode<T>* first;
	CNode<T>* last;

public:

	MyStack();
	~MyStack();
	void push(T);
	void pop();
	T top();
	bool empty();
};

	template <class T>
	MyStack<T>::MyStack()
	{
		first = NULL;
		last = NULL;
	}

	template <class T>
	MyStack<T>::~MyStack()
	{
		while (first != last)
		{
			CNode<T>* temp = last;
			last = temp->next;
			temp->next = NULL;
			temp = NULL;
			delete temp;
		}
		first = NULL;
		last = NULL;
	}

	template <class T>
	void MyStack<T>::push(T data)
	{
		CNode<T>* temp = new CNode<T>;
		temp->data = data;
		if (first != NULL)
		{
			temp->next = last;
			last = temp;
		}
		else
		{
			temp->next = NULL;
			first = last = temp;
		}
	}

	template <class T>
	void MyStack<T>::pop()
	{
		if (!empty())
		{
			if (last == first)
			{
				last = NULL;
				first = NULL;
				return;
			}
			CNode<T>* temp = last;
			last = temp->next;
			temp->next = NULL;
		}
		else
			throw logic_error("Error description");
	}

	template <class T>
	T MyStack<T>::top()
	{
		if (!empty())
			return last->data;
		else
			throw logic_error("Error description");
	}

	template <class T>
	bool MyStack<T>::empty()
	{
		if ((first == NULL) && (last == NULL))
			return true;
		else
			return false;
	}

//--------------------------------------------------

struct Variable
{
	char name;
	int value;
};

int priority(char);
char* RPN(int, char*, Variable*);

template <class T>
T calculation(char*, Variable*);

//--------------------------------------------------

template <class T>
char* RPN(int size_t, char* str, Variable* arr)					// Функция перевода в обратную польскую запись
{
	MyStack s;

	char* res = new char[size_t];
	int i = 0, j = 0;
	bool flag_abs = 0;											// Флаг для операции модуль 
	bool flag_var = 0;											// Флаг для проверки наличия переменной в структуре

	while (str[i] != '\0')
	{
		if ((str[i] >= '0') && (str[i] <= '9'))					// Если символ - число
		{
			while ((str[i] >= '0') && (str[i] <= '9'))
			{
				res[j++] = str[i++];
			}
			res[j++] = ' ';
		}
		else
		{
			if ((str[i] >= 'a') && (str[i] <= 'z'))             // Если символ - переменная
			{
				flag_var = 1;
				for (int k = 0; k < 2; ++k)
					if (str[i] == (arr[k].name))
					{
						res[j++] = str[i++];
						flag_var = 0;
					}
				if (flag_var == 1)
					throw logic_error("Error description");
				res[j++] = ' ';
			}
			else													// Если символ - оператор
			{
				if (s.empty())
				{
					if (i == 0)
						throw logic_error("Error description");
					if (str[i] == '|')
						flag_abs = 1;
					s.push(str[i++]);
				}
				else
				{
					switch (str[i])
					{
					case '+':
						if (priority(str[i]) <= priority(s.top()))
						{
							res[j++] = s.top();
							res[j++] = ' ';
							s.pop();
						}
						s.push('+');
						break;

					case '-':
						if (priority(str[i]) <= priority(s.top()))
						{
							res[j++] = s.top();
							res[j++] = ' ';
							s.pop();
						}
						s.push('-');
						break;

					case '*':
						if (priority(str[i]) <= priority(s.top()))
						{
							res[j++] = s.top();
							res[j++] = ' ';
							s.pop();
						}
						s.push('*');
						break;

					case '/':
						if (priority(str[i]) <= priority(s.top()))
						{
							res[j++] = s.top();
							res[j++] = ' ';
							s.pop();
						}
						s.push('/');
						break;

					case '^':
						if (priority(str[i]) <= priority(s.top()))
						{
							res[j++] = s.top();
							res[j++] = ' ';
							s.pop();
						}
						s.push('^');
						break;

					case '(':
						s.push('(');
						break;

					case ')':
						while (s.top() != '(')
						{
							if ((s.top() == '|') && (flag_abs == 1))
								throw logic_error("Error description");
							res[j++] = s.top();
							res[j++] = ' ';
							s.pop();
						}
						s.pop();
						break;

					case '|':

						if (flag_abs == 0)
						{
							s.push('|');
							flag_abs = 1;
						}
						else
						{
							while (s.top() != '|')
							{
								if (s.top() == '(')
									throw logic_error("Error description");
								res[j++] = s.top();
								res[j++] = ' ';
								s.pop();
							}
							res[j++] = s.top();
							s.pop();
							res[j++] = '|';
							res[j++] = ' ';
							flag_abs = 0;
						}
						break;
					}
					++i;
				}
			}
		}
	}


	while (!s.empty())
	{
		res[j++] = s.top();
		res[j++] = ' ';
		s.pop();
	}
	res[j] = '\0';

	return res;
}


template <class T>
T calculation(char* str, Variable* arr)						// Функция вычисления выражения
{
	MyStack<T> s;

	int i = 0;
	int temp = 0;
	int op1, op2 = 0;

	while (str[i] != '\0')
	{
		if ((str[i] >= '0') && (str[i] <= '9'))					// Если символ - число
		{
			while ((str[i] >= '0') && (str[i] <= '9'))
			{
				temp = temp * 10 + str[i];
			}
			s.push(temp);
		}
		else
		{
			if ((str[i] >= 'a') && (str[i] <= 'z'))             // Если символ - переменная
			{
				for (int k = 0; k < 2; ++k)
					if (str[i] == (arr[k].name))
					{
						s.push(arr[k].value);
					}
			}
			else                                                // Если символ - оператор
			{
				switch (str[i])
				{
				case '+':
					op2 = s.top();
					s.pop();
					op1 = s.top();
					s.pop();
					s.push(op1 + op2);
					break;

				case '-':
					op2 = s.top();
					s.pop();
					op1 = s.top();
					s.pop();
					s.push(op1 - op2);
					break;

				case '*':
					op2 = s.top();
					s.pop();
					op1 = s.top();
					s.pop();
					s.push(op1 * op2);
					break;

				case '/':
					op2 = s.top();
					s.pop();
					op1 = s.top();
					s.pop();
					s.push(op1 / op2);
					break;

				case '^':
					op2 = s.top();
					s.pop();
					op1 = s.top();
					s.pop();
					s.push((int)pow(op1, op2));
					break;

				case '|':
					if (s.top() < 0)
					{
						op1 = s.top();
						s.pop();
						s.push(-op1);
					}
					break;
				}
				++i;
			}
		}


		++i;
	}
	return s.top();
}

