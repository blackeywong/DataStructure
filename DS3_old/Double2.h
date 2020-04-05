#pragma once
#ifndef _DOUBLECIRCULAR_H
#define _DOUBLECIRCULAR_H

#include <iostream>
#include "exceptions.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第三章
//Exercise 52 - 56, 57

template<class T>class DoubleCircular;

template<class T>
class DoubleNode {
	friend class DoubleCircular<T>;
private:
	T data;
	DoubleNode<T>* left, *right;
};

template<class T>
class DoubleCircular {
	template<class T>
	friend ostream& operator<<(ostream& out, const DoubleCircular<T>& c);
public:
	DoubleCircular();
	~DoubleCircular() { Erase(); };

	bool IsEmpty() { return LeftEnd == nullptr; };
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(T& x) const;
	void Output(ostream& out) const;

	void Erase();

	DoubleCircular<T>& Insert(int k, const T& x);
	DoubleCircular<T>& Delete(int k, T& x);

	DoubleCircular<T>& Reverse();//Execise. 53
	DoubleCircular<T>& Alternate(const DoubleCircular<T>& a, const DoubleCircular<T>& b); //Execise. 54
	DoubleCircular<T>& Merge(const DoubleCircular<T>& a, const DoubleCircular<T>& b); //Execise. 55
	DoubleCircular<T>& Split(DoubleCircular<T>& a, DoubleCircular<T>& b); //Execise. 56
	//Exercise 57
	bool ResetLeft();
	bool ResetRight();
	bool Current(T&x);
	bool End();
	bool Front();
	bool Next();
	bool Previous();

private:
	DoubleNode<T>* LeftEnd;
	DoubleNode<T>* current;
};


template<class T>
DoubleCircular<T>::DoubleCircular()
{
	DoubleNode<T>* t = new DoubleNode<T>;
	t->left=t->right = t;
	LeftEnd = t;
}

template<class T>
int DoubleCircular<T>::Length() const
{
	DoubleNode<T>* cur = LeftEnd->right;
	int len = 0;
	while (cur != LeftEnd) {
		++len;
		cur = cur->right;
	}

	return len;
}

template<class T>
void DoubleCircular<T>::Erase()
{
	DoubleNode<T>* cur = LeftEnd->right;

	while (cur != LeftEnd) {
		DoubleNode<T>* next = cur->right;
		delete cur;
		cur = next;
	}
	LeftEnd->right = LeftEnd;
}

template<class T>
bool DoubleCircular<T>::Find(int k, T& x) const
{
	if (k < 1)
		return false;

	DoubleNode<T> * cur = LeftEnd->right;
	for (int i = 0; i < k&&cur!=LeftEnd; ++i) {
		cur = cur->right;
	}
	if(cur==LeftEnd) {
		return false;
	}
	x = cur->data;
	return true;
}

template<class T>
int DoubleCircular<T>::Search(T & x) const
{
	if (LeftEnd == LeftEnd->right) return -1;
	DoubleNode<T>* cur = LeftEnd;
	int i = 0;
	do
	{
		cur = cur->right;
		++i;
	} while (x != cur->data && cur != LeftEnd);
	if (cur == LeftEnd) return -1;
	return i;
}

template<class T>
void DoubleCircular<T>::Output(ostream & out) const
{
	DoubleNode<T>* cur = LeftEnd->right;
	while (cur != LeftEnd)
	{
		out << cur->data << " ";
		cur = cur->right;
	}

	out << endl;
}

template<class T>
DoubleCircular<T>& DoubleCircular<T>::Insert(int k, const T & x)
{
	if (k < 0)	throw OutOfBounds();

	DoubleNode<T> * c = new DoubleNode<T>;
	c->data = x;

	DoubleNode<T> * cur = LeftEnd;
	int i=0;
	if(k>0)
	{
		do{
			++i;
			cur = cur->right;
		}while(i < k&&cur!=LeftEnd);
	}
	if (i>0 && cur==LeftEnd) throw OutOfBounds();
	c->right = cur->right;
	c->left=cur;
	c->right->left=c;
	cur->right=c;

	return *this;
}

template<class T>
DoubleCircular<T> & DoubleCircular<T>::Delete(int k, T & x)
{
	if (k < 1)	throw OutOfBounds();

	DoubleNode<T> * cur = LeftEnd->right;
	int i = 1;
	for (; i < k &&cur!=LeftEnd; ++i) cur = cur->right;
	if (cur==LeftEnd) throw OutOfBounds();

	x = cur->data;
	cur->left->right=cur->right;
	cur->right->left=cur->left;
	delete cur;

	return *this;
}


template<class T>
DoubleCircular<T> & DoubleCircular<T>::Reverse()
{
	if (LeftEnd->right == LeftEnd) return *this; //empty

	DoubleNode<T> * p = LeftEnd;

	do
	{
		DoubleNode<T> * q = p->right;
		p->right = p->left;
		p->left = q;
		p = q;
	}while (p != LeftEnd);

	return *this;
}

template<class T>
DoubleCircular<T>& DoubleCircular<T>::Alternate(const DoubleCircular<T> & a, const DoubleCircular<T> & b)
{
	DoubleNode<T>* curA = a.LeftEnd->right;
	DoubleNode<T>* curB = b.LeftEnd->right;
	DoubleNode<T>* tailC = LeftEnd;
	DoubleNode<T>* newNode = nullptr, *newNode2 = nullptr;
	while (curA != a.LeftEnd && curB != b.LeftEnd)
	{
		newNode = new DoubleNode<T>();
		newNode->data = curA->data;
		newNode2 = new DoubleNode<T>();
		newNode2->data = curB->data;
		tailC->right = newNode;
		newNode->left = tailC;
		newNode->right = newNode2;
		newNode2->left = newNode;
		tailC = newNode2;
		curA = curA->right;
		curB = curB->right;
	}
	if(newNode2)
	{
		newNode2->right = LeftEnd;
		LeftEnd->left = newNode2;	
	}

	DoubleNode<T>* left = curA != a.LeftEnd ? curA : curB;
	DoubleNode<T>* lefthead = curA != a.LeftEnd ? a.LeftEnd : b.LeftEnd;
	newNode = nullptr;
	while (left != lefthead)
	{
		newNode = new DoubleNode<T>();
		newNode->data = left->data;
		tailC->right = newNode;
		tailC = newNode;
		left = left->right;
	}
	if(newNode)
	{
		newNode->right = LeftEnd;
		LeftEnd->left = newNode;	
	}

	return *this;
}

template<class T>
DoubleCircular<T>& DoubleCircular<T>::Merge(const DoubleCircular<T> & a, const DoubleCircular<T> & b)
{
	DoubleNode<T>* curA = a.LeftEnd->right;
	DoubleNode<T>* curB = b.LeftEnd->right;
	DoubleNode<T>* tailC = LeftEnd;
	DoubleNode<T>* newNode = nullptr;
	while (curA != a.LeftEnd || curB != b.LeftEnd)
	{
		newNode = new DoubleNode<T>();

		if (curA == a.LeftEnd || curB != b.LeftEnd && curA->data > curB->data)
		{
			newNode->data = curB->data;
			curB = curB->right;
		}
		else if (curB == b.LeftEnd || curA != a.LeftEnd && curA->data <= curB->data)
		{
			newNode->data = curA->data;
			curA = curA->right;
		}
		newNode->left = tailC;
		tailC->right = newNode;
		tailC = newNode;
	}
	if(newNode){
		newNode->right = LeftEnd;
		LeftEnd->left = newNode;
	}

	return *this;
}


template<class T>
DoubleCircular<T>& DoubleCircular<T>::Split(DoubleCircular<T> & a, DoubleCircular<T> & b)
{
	DoubleNode<T>* cur = LeftEnd->right;
	DoubleNode<T>* tailA = a.LeftEnd;
	DoubleNode<T>* tailB = b.LeftEnd;
	for (int i = 1; cur != LeftEnd; ++i)
	{
		DoubleNode<T>* newNode = new DoubleNode<T>;
		newNode->data = cur->data;
		if (i % 2 == 1)
		{
			tailA->right = newNode;
			newNode->left = tailA;
			tailA = newNode;
			tailA->right = a.LeftEnd;
		}
		else {
			tailB->right = newNode;
			newNode->left = tailB;
			tailB = newNode;
			tailB->right = b.LeftEnd;
		}

		cur = cur->right;
	}
	if(tailA != a.LeftEnd){
		tailA->right = a.LeftEnd;
		a.LeftEnd->left = tailA;
	}
	if(tailB != b.LeftEnd){
		tailB->right = b.LeftEnd;
		b.LeftEnd->left = tailB;
	}
	return *this;
}

template<class T>
bool DoubleCircular<T>::ResetLeft(){
	if(LeftEnd == LeftEnd->right){
		current = nullptr;
		return false;
	}
	current = LeftEnd->right;
	return true;
}

template<class T>
bool DoubleCircular<T>::ResetRight(){
	if(LeftEnd == LeftEnd->right){
		current = nullptr;
		return false;
	}
	current = LeftEnd->left;
	return true;
}

template<class T>
bool DoubleCircular<T>::Current(T&x){
	if(!current){
		return false;
	}
	x = current->data;
	return true;
}

template<class T>
bool DoubleCircular<T>::End(){
	if(!current) return true;
	return current == LeftEnd->left;
}

template<class T>
bool DoubleCircular<T>::Front(){
	if(!current) return true;
	return current == LeftEnd->right;
}

template<class T>
bool DoubleCircular<T>::Next(){
	if(End()) return false;
	current=current->right;
	return true;
}

template<class T>
bool DoubleCircular<T>::Previous(){
	if(Front()) return false;
	current=current->left;
	return true;
}

template<class T>
ostream& operator<<(ostream & out, const DoubleCircular<T> & c)
{
	c.Output(out);
	return out;
}


#endif
