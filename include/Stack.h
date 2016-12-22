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
