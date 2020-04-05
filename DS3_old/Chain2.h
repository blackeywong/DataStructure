#pragma once
#ifndef _CHAIN2_H
#define _CHAIN2_H

#include <iostream>
#include "list.h"
#include "exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第三章
//Exercise 74


template<class T>class Chain;

template<class T>
class ChainNode {
	friend class Chain<T>;
public:
	void * operator new(size_t size);
	void operator delete(void* p);
private:
	T data;
	ChainNode<T>* link;
	static ChainNode<T> * FreeNodes;
};

template<class T>
void* ChainNode<T>::operator new(size_t size)
{
	ChainNode<T>* tmp = ChainNode<T>::FreeNodes;
	if(tmp)
	{
		ChainNode<T>::FreeNodes = tmp->link;
		return tmp;
	}
	return ::new ChainNode<T>;
}

template<class T>
void ChainNode<T>::operator delete(void*p)
{
	ChainNode<T> * tmp = (ChainNode<T>*)p;
	tmp->link = ChainNode<T>::FreeNodes;
	ChainNode<T>::FreeNodes = tmp;
}

////////////////////////////////////////////////////////////////////////

template<class T>
class Chain {
	template<class T>
	friend ostream& operator<<(ostream&out, const Chain<T>& c);
public:
	Chain() { first = nullptr; }
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
	ChainNode<T>* first;
};

template<class T>
int Chain<T>::Length() const
{
	ChainNode<T>* current = first;
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
	ChainNode<T>* current = first;
	while (current) {
		ChainNode<T>* next = current->link;
		delete current;
		current = next;
	}
}

template<class T>
bool Chain<T>::Find(int k, T& x) const
{
	if (k<1)// || k>Lenth()), no need to do an extra traverse
		return false;

	ChainNode<T>* current = first;
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
	ChainNode<T>* current = first;
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
	ChainNode<T>* current = first;
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

	ChainNode<T>* c = new ChainNode<T>;
	c->data = x;


	ChainNode<T>* current = first;
	int i = 1;
	while (i < k && current)
	{
		current = current->link;
		++i;
	}

	if (k>0 && !current) throw OutOfBounds();


	if (k == 0)
	{
		c->link = first;
		first = c;
	}
	else
	{
		ChainNode<T>* d = current->link;
		current->link = c;
		c->link = d;
	}
	return *this;
}

template<class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{
	if (k < 0 || !first)	throw OutOfBounds();

	ChainNode<T>* current = first;
	int i = 1;
	while (i < k-1 && current)
	{
		current = current->link;
		++i;
	}

	if (k > 1 && (!current || !current->link)) throw OutOfBounds();

	ChainNode<T>* next = current->link;

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
