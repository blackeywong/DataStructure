#pragma once
#ifndef _CIRCULAR2_H
#define _CIRCULAR2_H

#include <iostream>
#include "exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第三章
//Exercise 42 - 46

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
	Circular();
	~Circular() { Erase(); };

	bool IsEmpty() { return first == nullptr; };
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(T& x) const;
	void Output(ostream& out) const;

	void Erase();

	Circular<T>& Insert(int k, const T& x);
	Circular<T>& Delete(int k, T& x);

	Circular<T>& Reverse();//Execise. 43
	Circular<T>& Alternate(const Circular<T>& a, const Circular<T>& b); //Execise. 44
	Circular<T>& Merge(const Circular<T>& a, const Circular<T>& b); //Execise. 45
	Circular<T>& Split(Circular<T>& a, Circular<T>& b); //Execise. 46
private:
	ChainNode<T>* first;
	ChainNode<T>* last;
};


template<class T>
Circular<T>::Circular()
{
	ChainNode<T>* t = new ChainNode<T>;
	t->link = t;
	first = last = t;
}

template<class T>
int Circular<T>::Length() const
{
	ChainNode<T>* current = first->link;
	int len = 0;
	while (current != first) {
		++len;
		current = current->link;
	}

	return len;
}

template<class T>
void Circular<T>::Erase()
{
	ChainNode<T>* current = first->link;
	
	while (current != first) {
		ChainNode<T>* next = current->link;
		delete current;
		current = next;
	}
	last = first;
	first->link = first;
}

template<class T>
bool Circular<T>::Find(int k, T& x) const
{
	if (k < 1 || k>Length())
		return false;

	ChainNode<T> * current = first;
	for (int i = 0; i < k;++i) current = current->link;
	x = current->data;
	return true;
}

template<class T>
int Circular<T>::Search(T& x) const
{
	if (!first) return -1;
	ChainNode<T>* current = first;
	int i = 0;
	do 
	{
		current = current->link;
		++i;
	} while (x != current->data && current != first);
	if (current == first) return -1;
	return i;
}

template<class T>
void Circular<T>::Output(ostream & out) const
{
	ChainNode<T>* current = first->link;
	while (current != first)
	{
		out << current->data << " ";
		current = current->link;
	}

	out << endl;
}

template<class T>
Circular<T>& Circular<T>::Insert(int k, const T & x)
{
	int len = Length();
	if (k < 0 || k > len + 1)	throw OutOfBounds();

	ChainNode<T> * c = new ChainNode<T>;
	c->data = x;

	ChainNode<T>* current = first;
	for (int i = 0; i < k; ++i) current = current->link;
	if (k == len) last = c;
	ChainNode<T> * d = current->link;
	current->link = c;
	c->link = d;

	return *this;
}

template<class T>
Circular<T>& Circular<T>::Delete(int k, T & x)
{
	int len = Length();
	if (k < 0 || k>len)	throw OutOfBounds();

	ChainNode<T> * current = first;

	for (int i = 0; i < k - 1; ++i) current = current->link;
	ChainNode<T> * next = current->link;

	if (k == len) last = current;

	x = next->data;
	current->link = next->link;
	delete next;

	return *this;
}


template<class T>
Circular<T>& Circular<T>::Reverse()
{
	if (first == last || first->link == last) return *this; //empty or 1 node only
	last = first->link;

	ChainNode<T> * p = first, *q = p->link, *r = q->link;

	while (r!=first)
	{
		q->link = p;
		p = q;
		q = r;
		r = r->link;
	}
	first->link = q;
	q->link = p;

	return *this;
}

template<class T>
Circular<T>& Circular<T>::Alternate(const Circular<T>& a, const Circular<T>& b)
{
	ChainNode<T>* curA = a.first->link;
	ChainNode<T>* curB = b.first->link;
	ChainNode<T>* tailC = first;

	while (curA!=a.first && curB!=b.first)
	{
		ChainNode<T>* newNode1 = new ChainNode<T>();
		newNode1->data = curA->data;
		ChainNode<T>* newNode2 = new ChainNode<T>();
		newNode2->data = curB->data;
		tailC->link = newNode1;
		newNode1->link = newNode2;
		tailC = newNode2;
		last = newNode2;
		tailC->link = first;
		curA = curA->link;
		curB = curB->link;
	}

	ChainNode<T>* left = curA != a.first ? curA : curB;
	ChainNode<T>* lefthead = curA != a.first ? a.first : b.first;
	while (left !=lefthead)
	{
		ChainNode<T>* newNode = new ChainNode<T>();
		newNode->data = left->data;
		tailC->link = newNode;
		tailC = newNode;
		last = newNode;
		tailC->link = first;
		left = left->link;
	}
	return *this;
}



template<class T>
Circular<T>& Circular<T>::Merge(const Circular<T>& a, const Circular<T>& b)
{
	ChainNode<T>* curA = a.first->link;
	ChainNode<T>* curB = b.first->link;

	while (curA!=a.first || curB!=b.first)
	{
		ChainNode<T>* newNode = new ChainNode<T>();
		newNode->link = first;

		if (curA == a.first || curB != b.first && curA->data > curB->data)
		{
			newNode->data = curB->data;
			curB = curB->link;
		}
		else if (curB == b.first || curA != a.first && curA->data <= curB->data)
		{
			newNode->data = curA->data;
			curA = curA->link;
		}
		last->link = newNode;
		last = newNode;
	}

	return *this;
}


template<class T>
Circular<T>& Circular<T>::Split(Circular<T>& a, Circular<T>& b) 
{
	int len = Length();

	ChainNode<T>* cur = first->link;

	for (int i = 1; i <= len && cur!=first; ++i)
	{
		ChainNode<T>* newNode = new ChainNode<T>;
		newNode->data = cur->data;
		if (i % 2 == 1)
		{
			a.last->link = newNode;
			a.last = newNode;
			a.last->link = a.first;
		}
		else {
			b.last->link = newNode;
			b.last = newNode;
			b.last->link = b.first;
		}

		cur = cur->link;
	}

	return *this;
}


template<class T>
ostream& operator<<(ostream& out, const Circular<T>& c)
{
	c.Output(out);
	return out;
}


#endif
