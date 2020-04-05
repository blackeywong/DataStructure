#pragma once
#ifndef _DOUBLE_H
#define _DOUBLE_H

#include <iostream>
#include "exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第三章
//Exercise 47-51

template<class T>class Double;

template<class T>
class DoubleNode {
	friend class Double<T>;
private:
	T data;
	DoubleNode<T>* left, *right;
};

template<class T>
class Double {
	template<class T>
	friend ostream& operator<<(ostream& out, const Double<T>& c);
public:
	Double() { LeftEnd = RightEnd = nullptr; }
	~Double() { Erase(); };

	bool IsEmpty() { return LeftEnd == nullptr; };
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(T& x) const;
	void Output(ostream& out) const;

	void Erase();

	Double<T>& Insert(int k, const T& x);
	Double<T>& Delete(int k, T& x);

	Double<T>& Reverse();//Execise. 48
	Double<T>& Alternate(const Double<T>& a, const Double<T>& b); //Execise. 49
	Double<T>& Merge(const Double<T>& a, const Double<T>& b); //Execise. 50
	Double<T>& Split(Double<T>& a, Double<T>& b); //Execise. 51

private:
	DoubleNode<T>* LeftEnd;
	DoubleNode<T>* RightEnd;
};


template<class T>
int Double<T>::Length() const
{
	if (!LeftEnd) return 0;

	DoubleNode<T>* current = LeftEnd;
	int len = 1;
	while (current != RightEnd) {
		++len;
		current = current->right;
	}

	return len;
}

template<class T>
void Double<T>::Erase()
{
	if (!LeftEnd) return;
	DoubleNode<T>* current = LeftEnd;
	while (current) {
		DoubleNode<T>* next = current->right;
		delete current;
		current = next;
	}
	LeftEnd = RightEnd = nullptr;
}

template<class T>
bool Double<T>::Find(int k, T& x) const
{
	if (k < 1)
		return false;

	DoubleNode<T> * current = LeftEnd;
	int i = 1;//1 means now it's already the LeftEnd node
	while (i < k && current)
	{
		++i;
		current = current->right;
	}
	if (!current) return false;

	x = current->data;
	return true;
}

template<class T>
int Double<T>::Search(T& x) const
{
	if (!LeftEnd) return -1;
	DoubleNode<T>* current = LeftEnd;
	int i = 1;
	while (x != current->data && current)
	{
		current = current->right;
		++i;
	}
	if (x != current->data) return -1;
	return i;
}

template<class T>
void Double<T>::Output(ostream & out) const
{
	DoubleNode<T>* current = LeftEnd;
	while (current)
	{
		out << current->data << " ";
		current = current->right;
	}
	out << endl;
}

template<class T>
Double<T>& Double<T>::Insert(int k, const T & x)
{
	if (k < 0)	throw OutOfBounds();

	DoubleNode<T> * c = new DoubleNode<T>;
	c->data = x;

	DoubleNode<T>* current = LeftEnd;
	for (int i = 1; i < k && current; ++i) current = current->right;
	if (!current && LeftEnd) throw OutOfBounds();

	if (k == 0){
		if (!LeftEnd) {
			c->left = c->right = nullptr;
			LeftEnd = RightEnd = c;
		}
		else {
			c->right = current;
			current->left = c;
			LeftEnd = c;
		}
		c->left = nullptr;
	}
	else {
		c->left = current;
		c->right = current->right;
		if(current->right) current->right->left = c;
		current->right = c;
		if (current == RightEnd) RightEnd = c;
	}

	return *this;
}

template<class T>
Double<T>& Double<T>::Delete(int k, T & x)
{
	if (k < 1)	throw OutOfBounds();

	DoubleNode<T> * current = LeftEnd;

	for (int i = 1; i < k && current; ++i) current = current->right;
	if(!current) throw OutOfBounds();

	x = current->data;

	if (k == 1)
	{

		if (LeftEnd == RightEnd) LeftEnd=RightEnd = nullptr;
		else {
			current->right->left = current->left;
			LeftEnd = current->right;
		}
	}
	else
	{
		current->left->right = current->right;
		if (current == RightEnd) {
			current->left->right = nullptr;
			RightEnd = current->left;
		}
		else {
			current->right->left = current->left;
		}
	}
	
	delete current;

	return *this;
}


template<class T>
Double<T>& Double<T>::Reverse()
{
	if (LeftEnd == nullptr || LeftEnd == RightEnd) return *this; //empty or 1 node only

	DoubleNode<T> * p = LeftEnd;
	LeftEnd = RightEnd;
	RightEnd = p;

	while (p)
	{
		DoubleNode<T>* q = p->right;
		p->right = p->left;
		p->left = q;
		p = q;
	}

	return *this;
}

template<class T>
Double<T>& Double<T>::Alternate(const Double<T> & a, const Double<T> & b)
{
	Double<T>* c = new Double<T>;
	DoubleNode<T>* curA = a.LeftEnd;
	DoubleNode<T>* curB = b.LeftEnd;
	DoubleNode<T>* tailC = nullptr;

	while (curA && curB)
	{
		DoubleNode<T>* newNode1 = new DoubleNode<T>();
		newNode1->data = curA->data;
		DoubleNode<T>* newNode2 = new DoubleNode<T>();
		newNode2->data = curB->data;
		if (!LeftEnd) {
			LeftEnd = newNode1;
			newNode1->left = nullptr;
		}
		else if (tailC){
			tailC->right = newNode1;
			newNode1->left = tailC;
		}
		newNode1->right = newNode2;
		newNode2->left = newNode1;
		newNode2->right = nullptr;
		tailC = newNode2;
		RightEnd = newNode2;
		curA = curA->right;
		curB = curB->right;
	}
	
	DoubleNode<T>* left = curA != nullptr ? curA : curB;
	while (left)
	{
		DoubleNode<T>* newNode = new DoubleNode<T>();
		newNode->data = left->data;
		if (!LeftEnd) {
			LeftEnd = newNode;
			newNode->left = nullptr;
		}
		else if (tailC) {
			tailC->right = newNode;
			newNode->left = tailC;
		}
		newNode->right = nullptr;
		tailC = newNode;
		RightEnd = newNode;
		left = left->right;
	}

	return *this;
}

template<class T>
Double<T>& Double<T>::Merge(const Double<T> & a, const Double<T> & b)
{
	Double<T>* c = new Double<T>;
	DoubleNode<T>* curA = a.LeftEnd;
	DoubleNode<T>* curB = b.LeftEnd;

	while (curA || curB)
	{
		DoubleNode<T>* newNode = new DoubleNode<T>();

		if (!curA || curB && curA->data > curB->data)
		{
			newNode->data = curB->data;
			curB = curB->right;
		}
		else if (!curB || curA && curA->data <= curB->data)
		{
			newNode->data = curA->data;
			curA = curA->right;
		}
		if (!LeftEnd) {
			LeftEnd = newNode;
			newNode->left = nullptr;
		}
		else {
			RightEnd->right = newNode;
			newNode->left=RightEnd;
		}
		RightEnd = newNode;
		newNode->right = nullptr;
	}
	return *this;

}


template<class T>
Double<T>& Double<T>::Split(Double<T> & a, Double<T> & b)
{
	DoubleNode<T> * cur = LeftEnd;

	int i = 1;
	while (cur)
	{
		DoubleNode<T>* newNode = new DoubleNode<T>;
		newNode->data = cur->data;
		newNode->right = nullptr;
		if (i % 2 == 1)
		{
			if (i == 1)	{
				a.LeftEnd = newNode;
				newNode->left=nullptr;
			}
			else {
				a.RightEnd->right = newNode;
				newNode->left = a.RightEnd;
			}
			a.RightEnd = newNode;
		}
		else {
			if (i == 2)	{
				b.LeftEnd = newNode;
				newNode->left=nullptr;
			}
			else {
				b.RightEnd->right = newNode;
				newNode->left=b.RightEnd;
			}
			b.RightEnd = newNode;
		}

		cur = cur->right;
		++i;
	} 

	return *this;
}

template<class T>
ostream& operator<<(ostream & out, const Double<T> & c)
{
	c.Output(out);
	return out;
}

#endif
