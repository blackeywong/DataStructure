#pragma once
#ifndef _SIMCHAIN3_H
#define _SIMCHAIN3_H

#include <iostream>
#include "SimSpace3.h"
#include "exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第三章
//Exercise 69

template<class T>
class Chain {
	template<class T>
	friend ostream& operator<<(ostream&out, const Chain<T>& c);
public:
	Chain() { first = last = nullptr; }
	~Chain() { Erase();  };

	bool IsEmpty() { return first == nullptr; };
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(T&x) const;
	void Output(ostream & out) const;

	void Erase();

	Chain<T>& Insert(int k, const T&x);
	Chain<T>& Delete(int k, T& x);
private:
	SimNode<T>* first;
	SimNode<T>* last;
};

template<class T>
int Chain<T>::Length() const
{
	SimNode<T>* current = first;
	int len = 0;
	while (current) {
		++len;
		current = current->link;
	}

	return len;
}

template<class T>
void Chain<T>::Erase()
{
	SimNode<T>* current = first;
	while (current) {
		SimNode<T>* next = current->link;
		delete current;
		current = next;
	}
}

template<class T>
bool Chain<T>::Find(int k, T& x) const
{
	if (k<1)// || k>Lenth()), no need to do an extra traverse
		return false;

	SimNode<T>* current = first;
	int i = 1;//1 means now it's already the first node
	while (i<k && current)
	{
		++i;
		current = current->link;
	}

	if (current) {
		x = current->data;
		return true;
	}
	return false;
}

template<class T>
int Chain<T>::Search(T& x) const
{
	SimNode<T>* current = first;
	int i = 1;
	while (current && x != current->data)//add the judgement in condition
	{
		current = current->link;
		++i;
	}

	if (current) return i;
	return -1;
}

template<class T>
void Chain<T>::Output(ostream& out) const
{
	SimNode<T>* current = first;
	while (current)
	{
		out << current->data << " ";
		current = current->link;
	}
	out << endl;
}

template<class T>
Chain<T>& Chain<T>::Insert(int k, const T& x)
{
	if (k < 0)	throw OutOfBounds();

	SimNode<T>* c = new SimNode<T>;
	c->data = x;


	SimNode<T>* current = first;
	int i = 1;
	while (i < k && current)
	{
		current = current->link;
		++i;
	}

	if (k>0 && !current) throw OutOfBounds();

	if (!current || !current->link) last = c;

	if (k == 0)
	{
		c->link = first;
		first = c;
	}
	else
	{
		SimNode<T>* d = current->link;
		current->link = c;
		c->link = d;
	}
	return *this;
}

template<class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{
	if (k < 0 || !first)	throw OutOfBounds();

	SimNode<T>* current = first;
	int i = 1;
	while (i < k-1 && current)
	{
		current = current->link;
		++i;
	}

	if (k > 1 && (!current || !current->link)) throw OutOfBounds();

	SimNode<T>* next = current->link;

	if (!current || !current->link) last = current;

	if (k == 1)
	{
		x = current->data;
		first = current->link;
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
ostream& operator<<(ostream& out, const Chain<T>& c)
{
	c.Output(out);
	return out;
}

#endif
