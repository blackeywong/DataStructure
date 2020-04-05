#pragma once
#ifndef _CIRCULAR_H
#define _CIRCULAR_H

#include <iostream>
#include "exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第三章
//Exercise 35-40

template<class T>class Circular;

template<class T>
class ChainNode {
	friend class Circular<T>;
private:
	T data;
	ChainNode<T>* link;
};

template<class T>
class Circular {
	template<class T>
	friend ostream& operator<<(ostream& out, const Circular<T>& c);
public:
	Circular() { first = last = nullptr; }
	~Circular() { Erase(); };

	bool IsEmpty() { return first == nullptr; };
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(T& x) const;
	void Output(ostream& out) const;

	void Erase();

	Circular<T>& Insert(int k, const T& x);
	Circular<T>& Delete(int k, T& x);

	Circular<T>& Reverse();//Execise. 37
	Circular<T>& Alternate(const Circular<T>& a, const Circular<T>& b); //Execise. 38
	Circular<T>& Merge(const Circular<T>& a, const Circular<T>& b); //Execise. 39
	Circular<T>& Split(Circular<T>& a, Circular<T>& b); //Execise. 40

private:
	ChainNode<T>* first;
	ChainNode<T>* last;
};


template<class T>
int Circular<T>::Length() const
{
	if (!first) return 0;
	if (!first->link) return 1;

	ChainNode<T>* current = first->link;
	int len = 1;
	while (current != first) {
		++len;
		current = current->link;
	}

	return len;
}

template<class T>
void Circular<T>::Erase()
{
	if (!first) return;
	ChainNode<T>* current = first->link;
	delete first;
	while (current != last) {
		ChainNode<T>* next = current->link;
		delete current;
		current = next;
	}
	first = last = nullptr;
}

template<class T>
bool Circular<T>::Find(int k, T & x) const
{
	if (k < 1 || k>Length())
		return false;

	ChainNode<T>* current = first;
	int i = 1;//1 means now it's already the first node
	while (i < k)
	{
		++i;
		current = current->link;
	}
	
	x = current->data;
	return true;
}

template<class T>
int Circular<T>::Search(T & x) const
{
	if (!first) return -1;
	ChainNode<T>* current = first;
	if (current && x == current->data) return 1;
	int i = 2;
	current = current->link;
	while (x != current->data && current != first)
	{
		current = current->link;
		++i;
	}
	if (current == first) return -1;
	return i;
}

template<class T>
void Circular<T>::Output(ostream & out) const
{
	if (first)
	{
		out << first->data << " ";
		ChainNode<T>* current = first->link;
		while (current!=first)
		{
			out << current->data << " ";
			current = current->link;
		}
	}
	out << endl;
}

template<class T>
Circular<T>& Circular<T>::Insert(int k, const T & x)
{
	int len = Length();
	if (k < 0 || k > len + 1)	throw OutOfBounds();

	ChainNode<T>* c = new ChainNode<T>;
	c->data = x;

	if (k == 0)
	{
		if (len == 0)
		{
			c->link = c;
			last = c;
		}
		else c->link = first;
		first = c;
		last->link = c;
	}
	else
	{
		ChainNode<T>* current = first;
		for (int i = 1;i < k ; ++i) current = current->link;
		if (k == len) last = c;
		ChainNode<T>* d = current->link;
		current->link = c;
		c->link = d;

	}
	return *this;
}

template<class T>
Circular<T>& Circular<T>::Delete(int k, T & x)
{
	int len = Length();
	if (k < 0 || k>len)	throw OutOfBounds();

	ChainNode<T> * current = first;
	
	for (int i = 1;i < k-1; ++i) current = current->link;
	ChainNode<T> * next = current->link;

	if (k == len) last = current;

	if (k == 1 && len == 1)
	{
		first = last = nullptr;
		delete current;
	}
	else if (k == 1)
	{
		x = current->data;
		first = current->link;
		last->link = current->link;
		delete current;
	}
	else
	{
		x = next->data;
		current->link = next->link;
		delete next;
	}

	return *this;
}


template<class T>
Circular<T>& Circular<T>::Reverse()
{
	if (first == nullptr || first == last) return *this; //empty or 1 node only

	ChainNode<T> * p = last, *q = first, *r = first->link;
	last = first;

	while (r!=first)
	{
		q->link = p;
		p = q;
		q = r;
		r = r->link;
	}
	first = q;
	q->link = p;

	return *this;
}

template<class T>
Circular<T>& Circular<T>::Alternate(const Circular<T>& a, const Circular<T>& b)
{
	Circular<T>* c = new Circular<T>;
	ChainNode<T>* curA = a.first;
	ChainNode<T>* curB = b.first;
	ChainNode<T>* tailC = nullptr;

	if(curA && curB)
	{
		do 
		{
			ChainNode<T>* newNode1 = new ChainNode<T>();
			newNode1->data = curA->data;
			ChainNode<T>* newNode2 = new ChainNode<T>();
			newNode2->data = curB->data;
			if (!first) first = newNode1;
			else if (tailC) tailC->link = newNode1;
			newNode1->link = newNode2;
			tailC = newNode2;
			last = newNode2;
			tailC->link = first;
			curA = curA->link;
			curB = curB->link;
		} while (curA != a.first && curB != b.first);
	}
	ChainNode<T>* left = curA != a.first ? curA : curB;
	ChainNode<T>* leftfirst = curA != a.first ? a.first : b.first;
	do
	{
		ChainNode<T>* newNode = new ChainNode<T>();
		newNode->data = left->data;
		if (!first) first = newNode;
		else if (tailC) tailC->link = newNode;
		tailC = newNode;
		last = newNode;
		tailC->link = first;
		left = left->link;
	} while (left != leftfirst);

	return *this;
}

template<class T>
Circular<T>& Circular<T>::Merge(const Circular<T>& a, const Circular<T>& b)
{
	Circular<T>* c = new Circular<T>;
	ChainNode<T>* curA = a.first, *preA = nullptr;
	ChainNode<T>* curB = b.first, * preB = nullptr;

	if (curA || curB)
	{
		do
		{
			ChainNode<T>* newNode = new ChainNode<T>();

			if (curA == a.first && preA == a.last || preB != b.last && curA->data > curB->data)
			{
				newNode->data = curB->data;
				preB = curB;
				curB = curB->link;
			}
			else if (curB == b.first && preB == b.last || preA != a.last && curA->data <= curB->data)
			{
				newNode->data = curA->data;
				preA = curA;
				curA = curA->link;
			}
			if (!first) first = newNode;
			else last->link = newNode;
			last = newNode;
			newNode->link = first;
		} while (curA != a.first || curB != b.first);
	}
	return *this;

}


template<class T>
Circular<T>& Circular<T>::Split(Circular<T> & a, Circular<T> & b)
{
	int len = Length();
	if (len == 0) return *this;
	ChainNode<T>* cur = first;

	int i = 1;
	do
	{
		ChainNode<T>* newNode = new ChainNode<T>;
		newNode->data = cur->data;
		newNode->link = nullptr;
		if (i % 2 == 1)
		{
			if (i == 1)	a.first = newNode;
			else a.last->link = newNode;
			a.last = newNode;
			newNode->link = a.first;
		}
		else {
			if (i == 2)	b.first = newNode;
			else b.last->link = newNode;
			b.last = newNode;
			newNode->link = b.first;
		}

		cur = cur->link;
		++i;
	}while (i <= len && cur != first);

	return *this;
}

template<class T>
ostream& operator<<(ostream & out, const Circular<T> & c)
{
	c.Output(out);
	return out;
}

#endif
