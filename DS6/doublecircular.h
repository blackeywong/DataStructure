#pragma once
#ifndef _DOUBLECIRCULAR_H
#define _DOUBLECIRCULAR_H

#include <iostream>
#include "../DS5/exceptions.h"
#include "../DS5/linearlist.h"
#include "doublenode.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 49-54

template<class T>
class DoubleCircular : public LinearList<T> {
	template<class T>
	friend void meld(const DoubleCircular<T>& a, const DoubleCircular<T>& b, DoubleCircular<T>& c);//Ecercise 52
	template<class T>
	friend void merge(const DoubleCircular<T>& a, const DoubleCircular<T>& b, DoubleCircular<T>& c);//Ecercise 53
	template<class T>
	friend void split(const DoubleCircular<T>& c, DoubleCircular<T>& a, DoubleCircular<T>& b); //Execise 54

public:
	DoubleCircular(int initialCapacity = 10);
	~DoubleCircular();

	DoubleCircular<T>& operator=(DoubleCircular<T>& right);

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void erase(int theIndex);
	void output(ostream& out) const;
	void clear();
	void push_back(const T& theElement);

	DoubleCircular<T>& concat(DoubleCircular<T>& a); //Exercise 51

	DoubleCircular<T>& reverse();//Execise 50
	DoubleCircular<T>& meld(DoubleCircular<T>& a, DoubleCircular<T>& b);//Exercise 52
	DoubleCircular<T>& merge(DoubleCircular<T>& a, DoubleCircular<T>& b); //Execise 53
	DoubleCircular<T>& split(DoubleCircular<T>& a, DoubleCircular<T>& b); //Execise 54

protected:
	void checkIndex(int theIndex) const;

	DoubleNode<T>* firstNode;
	DoubleNode<T> * lastNode;
	int listSize;
};

template<class T>
DoubleCircular<T>::DoubleCircular(int initialCapacity){
	if(initialCapacity < 1){
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0.";
		throw IllegalParameterValue(s.str());
	}
	firstNode = lastNode = nullptr;
	listSize = 0;
}

template<class T>
DoubleCircular<T>::~DoubleCircular(){
	clear();
}

template<class T>
void DoubleCircular<T>::clear()
{
	if (!firstNode) return;
	DoubleNode<T>* current = firstNode->right;
	delete firstNode;
	while (current != firstNode) {
		DoubleNode<T>* right = current->right;
		delete current;
		current = right;
	}
	firstNode = lastNode = nullptr;
	listSize = 0;
}

template<class T>
DoubleCircular<T>& DoubleCircular<T>::operator=(DoubleCircular<T>& right) {
	if (right.firstNode->right == right.firstNode) return *this;
	DoubleNode<T>* current = right.firstNode->right;
	while (current != right.firstNode) {
		push_back(current->element);
		current = current->right;
	}

	return *this;
}

template<class T>
void DoubleCircular<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
T& DoubleCircular<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	DoubleNode<T> * cur = firstNode;
	for (int i = 0; i < theIndex; ++i) {
		cur = cur->right;
	}

	return cur->element;
}

template<class T>
int DoubleCircular<T>::indexOf(const T& theElement) const
{
	if (!firstNode) return -1;
	DoubleNode<T>* cur = firstNode;
	int i = 0;
	while (theElement != cur->element && i < listSize)
	{
		cur = cur->right;
		++i;
	} ;
	if (i == listSize) return -1;
	return i;
}

template<class T>
void DoubleCircular<T>::output(ostream & out) const
{
	DoubleNode<T>* cur = firstNode;
	for (int i=0;i<listSize;i++)
	{
		out << cur->element << " ";
		cur = cur->right;
	}

	out << endl;
}

template<class T>
void DoubleCircular<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)	throw OutOfBounds();

	DoubleNode<T> * c = new DoubleNode<T>;
	c->element = theElement;

	DoubleNode<T>* current = firstNode;
	for (int i = 0; i < theIndex-1 && current; ++i) current = current->right;

	if (theIndex == 0){
		if (!firstNode) {
			c->right = c;
			firstNode = lastNode = c;
		}
		else {
			c->right = current;
			current->left = c;
			firstNode = c;
			lastNode->right = c;
		}
		c->left = lastNode;
	}
	else {
		c->left = current;
		c->right = current->right;
		current->right->left = c;
		current->right = c;
		if (current == lastNode) lastNode = c;
	}
	
	listSize++;
}

template<class T>
void DoubleCircular<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	DoubleNode<T> * cur = firstNode;
	int i = 0;
	for (; i < theIndex; ++i) cur = cur->right;

	if(theIndex == 0) {
		if(listSize == 1){
			firstNode = lastNode = nullptr;
			delete cur;
			listSize--;
			return;
		}else{
			firstNode = cur->right;
		}
	}
	else if(theIndex == listSize - 1){
		lastNode = cur->left;
	}

	cur->left->right=cur->right;
	cur->right->left=cur->left;
	delete cur;

	listSize--;
}

template<class T>
void DoubleCircular<T>::push_back(const T& theElement){
	DoubleNode<T> * newNode = new DoubleNode<T>(theElement, nullptr, nullptr);
	
	if(listSize == 0){
		newNode->left = newNode->right = firstNode = lastNode = newNode;
	}else{
		firstNode->left = newNode;
		lastNode->right = newNode;
		newNode->left = lastNode;
		newNode->right = firstNode;
		lastNode = newNode;
	}
	this->listSize++;
}

template<class T>
DoubleCircular<T>& DoubleCircular<T>::concat(DoubleCircular<T>& a)
{
	if (a.listSize == 0) return *this;

	if (listSize == 0) {
		firstNode = a.firstNode;
	}
	else {
		lastNode->right = a.firstNode;
		a.firstNode->left = lastNode;
		firstNode->left = a.lastNode;
		a.lastNode->right = firstNode;
	}
	lastNode = a.lastNode;
	listSize += a.listSize;

	a.firstNode = a.lastNode = nullptr;
	a.listSize = 0;

	return *this;
}

template<class T>
DoubleCircular<T> & DoubleCircular<T>::reverse()
{
	if (listSize <= 1) return *this;

	DoubleNode<T> * p = firstNode;
	firstNode = lastNode;
	lastNode = p;

	for (int i=0;i<listSize;i++)
	{
		DoubleNode<T>* q = p->right;
		p->right = p->left;
		p->left = q;
		p = q;
	}

	return *this;
}

template<class T>
DoubleCircular<T>& DoubleCircular<T>::meld(DoubleCircular<T> & a, DoubleCircular<T> & b)
{
	DoubleNode<T>* curA = a.firstNode;
	DoubleNode<T>* curB = b.firstNode;
	DoubleNode<T>* cur = nullptr;
	int i=0,j=0;
	for (;i<a.listSize&&j<b.listSize;i++,j++)
	{
		if (!cur) {
			firstNode = curA;
		}else{
			cur->right = curA;
			curA->left = cur;
		}
		cur = curA;
		curA = curA->right;
		cur->right = curB;
		curB->left = cur;
		cur = curB;
		curB = curB->right;
	}
	if(cur)
	{
		cur->right = firstNode;
		firstNode->left = cur;
		lastNode = cur;
	}

	DoubleNode<T>* left = a.listSize >= b.listSize ? curA : curB;
	int leftsize = a.listSize >= b.listSize ? a.listSize : b.listSize;
	for (;i < leftsize;i++)
	{
		if (!cur) {
			firstNode = left;
		}else{
			cur->right = left;
			left->left = cur;
		}
		cur = left;
		left = left->right;
	}
	if(cur)
	{
		cur->right = firstNode;
		firstNode->left = cur;
		lastNode=cur;
	}
	listSize = a.listSize + b.listSize;

	a.firstNode = a.lastNode = b.firstNode = b.lastNode = nullptr;
	a.listSize = b.listSize = 0;

	return *this;
}

template<class T>
DoubleCircular<T>& DoubleCircular<T>::merge(DoubleCircular<T> & a, DoubleCircular<T> & b)
{
	DoubleNode<T>* curA = a.firstNode;
	DoubleNode<T>* curB = b.firstNode;
	DoubleNode<T>* cur = nullptr;
	int i = 0, j = 0;
	while (i < a.size() && j < b.size()) {
		if(curA->element <= curB->element){
			if(!cur){
				firstNode = curA;
			}else{
				cur->right = curA;
				curA->left = cur;
			}
			cur = curA;
			curA = curA->right;
			i++;
		}else{
			if(!cur){
				firstNode = curB;
			}else{
				cur->right = curB;
				curB->left = cur;
			}
			cur = curB;
			curB = curB->right;
			j++;
		}
	}
	for (; i < a.size();i++) {
		if(!cur){
			firstNode = curA;
		}else{
			cur->right = curA;
			curA->left = cur;
		}
		cur = curA;
		curA = curA->right;
	}
	for (; j < b.size(); j++) {
		if(!cur){
			firstNode = curB;
		}else{
			cur->right = curB;
			curB->left = cur;
		}
		cur = curB;
		curB = curB->right;
	}
	if(!cur){
		lastNode = cur;
		cur->right = firstNode;
		firstNode->left = cur;
	}
	listSize = a.listSize+b.listSize;

	a.firstNode = a.lastNode = b.firstNode = b.lastNode = nullptr;
	a.listSize = b.listSize = 0;
	return *this;
}


template<class T>
DoubleCircular<T>& DoubleCircular<T>::split(DoubleCircular<T> & a, DoubleCircular<T> & b)
{
	DoubleNode<T> * cur = firstNode;
	DoubleNode<T>* curA = nullptr;
	DoubleNode<T>* curB = nullptr;

	for(int i=0;i<listSize;i++)
	{
		if (i % 2 == 0)
		{
			if (i == 0)	{
				a.firstNode = cur;
			}
			else {
				curA->right = cur;
				cur->left = curA;
			}
			curA = cur;
			a.lastNode = curA;
			a.listSize++;
		}
		else {
			if (i == 1)	{
				b.firstNode = cur;
			}
			else {
				curB->right = cur;
				cur->left=curB;
			}
			curB = cur;
			b.lastNode = curB;
			b.listSize++;
		}
		cur = cur->right;
	} 
	a.lastNode->right = a.firstNode;
	a.firstNode->left = a.lastNode;
	b.lastNode->right = b.firstNode;
	b.firstNode->left = b.lastNode;

	firstNode = lastNode = nullptr;
	listSize = 0;
	return *this;
}

template<class T>
ostream& operator<<(ostream & out, const DoubleCircular<T> & c)
{
	c.output(out);
	return out;
}

template<class T>
void reverse(DoubleCircular<T>& c, DoubleCircular<T>& d)//Execise 50
{
	for(int i=0;i<c.size();i++)
		d.insert(0, c.get(i));
}

template<class T>
void meld(const DoubleCircular<T>& a, const DoubleCircular<T>& b, DoubleCircular<T>& c){
	DoubleNode<T>* cur1 = a.firstNode;
	DoubleNode<T>* cur2 = b.firstNode;
	int i=0,j=0;
	for(;i<a.size()&&j<b.size();i++,j++){
		c.push_back(cur1->element);
		c.push_back(cur2->element);
		cur1 = cur1->right;
		cur2 = cur2->right;
	}
	for(;i<a.size();i++){
		c.push_back(cur1->element);
		cur1 = cur1->right;
	}
	for(;j<b.size();j++){
		c.push_back(cur2->element);
		cur2 = cur2->right;
	}
}

template<class T>
void merge(const DoubleCircular<T>& a, const DoubleCircular<T>& b, DoubleCircular<T>& c){
	DoubleNode<T>* cur1 = a.firstNode;
	DoubleNode<T>* cur2 = b.firstNode;
	int i = 0, j = 0;
	while (i < a.size() && j < b.size()) {
		if(cur1->element <= cur2->element){
			c.push_back(cur1->element);
			cur1 = cur1->right;
			i++;
		}else{
			c.push_back(cur2->element);
			cur2 = cur2->right;
			j++;
		}
	}
	for (; i < a.size();i++) {
		c.push_back(cur1->element);
		cur1 = cur1->right;
	}
	for (; j < b.size(); j++) {
		c.push_back(cur2->element);
		cur2 = cur2->right;
	}
}

template<class T>
void split(const DoubleCircular<T>& c, DoubleCircular<T>& a, DoubleCircular<T>& b) {
	if (c.size() == 0) return;
	DoubleNode<T>* cur = c.firstNode;

	for (int i = 0; i < c.listSize; i++) {
		if (i % 2 == 0)	a.push_back(cur->element);
		else b.push_back(cur->element);
		cur = cur->right;
	}
}

#endif
