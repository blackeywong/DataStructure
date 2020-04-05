#pragma once
#ifndef _EXTENDEDCIRCULAR_H
#define _EXTENDEDCIRCULAR_H

#include <iostream>
#include "../DS5/exceptions.h"
#include "../DS5/linearlist.h"
#include "chainnode.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 38-42

template<class T>
class ExtendedCircular : public LinearList<T> {
	template<class T>
	friend void meld(const ExtendedCircular<T>& a, const ExtendedCircular<T>& b, ExtendedCircular<T>& c);//Ecercise 40
	template<class T>
	friend void merge(const ExtendedCircular<T>& a, const ExtendedCircular<T>& b, ExtendedCircular<T>& c);//Ecercise 41
	template<class T>
	friend void split(const ExtendedCircular<T>& c, ExtendedCircular<T>& a, ExtendedCircular<T>& b); //Execise 42

public:
	ExtendedCircular(int initialCapacity = 10);
	~ExtendedCircular();

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void erase(int theIndex);
	void output(ostream& out) const;
	void clear();
	void push_back(const T& theElement);

	ExtendedCircular<T>& reverse();//Execise 39
	ExtendedCircular<T>& meld(ExtendedCircular<T>& a, ExtendedCircular<T>& b);//Exercise 40
	ExtendedCircular<T>& merge(ExtendedCircular<T>& a, ExtendedCircular<T>& b); //Execise 41
	ExtendedCircular<T>& split(ExtendedCircular<T>& a, ExtendedCircular<T>& b); //Execise 42

protected:
	void checkIndex(int theIndex) const;

	ChainNode<T>* firstNode;
	ChainNode<T> * lastNode;
	int listSize;
};


template<class T>
ExtendedCircular<T>::ExtendedCircular(int initialCapacity)
{
	if (initialCapacity < 1) {
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0.";
		throw IllegalParameterValue(s.str());
	}
	ChainNode<T>* t = new ChainNode<T>;
	t->next = t;
	firstNode = lastNode = t;
	listSize = 0;
}

template<class T>
ExtendedCircular<T>::~ExtendedCircular() {
	clear();
}

template<class T>
void ExtendedCircular<T>::clear()
{
	ChainNode<T>* current = firstNode->next;
	
	while (current != firstNode) {
		ChainNode<T>* next = current->next;
		delete current;
		current = next;
	}
	lastNode = firstNode;
	firstNode->next = firstNode;
	listSize = 0;
}

template<class T>
void ExtendedCircular<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
T& ExtendedCircular<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	ChainNode<T> * current = firstNode;
	for (int i = 0; i <= theIndex;++i) current = current->next;
	return current->element;
}

template<class T>
int ExtendedCircular<T>::indexOf(const T& theElement) const
{
	if (firstNode->next == firstNode) return -1;
	ChainNode<T>* current = firstNode->next;
	int i = 0;
	while (theElement != current->element && current != firstNode)
	{
		current = current->next;
		++i;
	}
	if (current == firstNode) return -1;
	return i;
}


template<class T>
void ExtendedCircular<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize + 1)	throw OutOfBounds();

	ChainNode<T> * c = new ChainNode<T>;
	c->element = theElement;

	ChainNode<T>* current = firstNode;
	for (int i = 0; i < theIndex; ++i) current = current->next;
	if (theIndex == listSize) lastNode = c;
	ChainNode<T> * d = current->next;
	current->next = c;
	c->next = d;
	listSize++;
}

template<class T>
void ExtendedCircular<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	ChainNode<T> * current = firstNode;

	for (int i = 0; i < theIndex; ++i) current = current->next;
	ChainNode<T> * next = current->next;

	if (theIndex == listSize-1) lastNode = current;

	current->next = next->next;
	delete next;
	listSize--;
}

template<class T>
void ExtendedCircular<T>::output(ostream& out) const
{
	ChainNode<T>* current = firstNode->next;
	while (current != firstNode)
	{
		out << current->element << " ";
		current = current->next;
	}

	out << endl;
}

template<class T>
void ExtendedCircular<T>::push_back(const T& theElement){
	ChainNode<T> * newNode = new ChainNode<T>(theElement, nullptr);
	if(listSize == 0){
		this->firstNode->next = lastNode = newNode;
	}else{
		lastNode->next = newNode;
		lastNode = newNode;
	}
	lastNode->next = firstNode;
	this->listSize++;
}

template<class T>
ExtendedCircular<T>& ExtendedCircular<T>::reverse()
{
	if (firstNode == lastNode || firstNode->next == lastNode) return *this; //empty or 1 node only
	lastNode = firstNode->next;

	ChainNode<T> * p = firstNode, *q = p->next, *r = q->next;

	while (r!=firstNode)
	{
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	firstNode->next = q;
	q->next = p;

	return *this;
}

template<class T>
ExtendedCircular<T>& ExtendedCircular<T>::meld(ExtendedCircular<T>& a, ExtendedCircular<T>& b)
{
	ChainNode<T>* curA = a.firstNode->next;
	ChainNode<T>* curB = b.firstNode->next;
	while (curA!=a.firstNode && curB!=b.firstNode)
	{
		ChainNode<T>* tmp = curA->next;
		lastNode->next = curA;
		curA->next = firstNode;
		lastNode = curA;
		curA = tmp;
		tmp = curB->next;
		lastNode->next = curB;
		curB->next = firstNode;
		lastNode = curB;
		curB = tmp;
	}

	ChainNode<T>* left = curA != a.firstNode ? curA : curB;
	ChainNode<T>* lefthead = curA != a.firstNode ? a.firstNode : b.firstNode;
	while (left !=lefthead)
	{
		ChainNode<T>* tmp = left->next;
		lastNode->next = left;
		left->next = firstNode;
		lastNode = left;
		left = tmp;
	}
	listSize = a.listSize + b.listSize;
	a.listSize = b.listSize = 0;
	a.lastNode = a.firstNode;
	a.firstNode->next = a.firstNode;
	b.lastNode = b.firstNode;
	b.firstNode->next = b.firstNode;
	return *this;
}

template<class T>
ExtendedCircular<T>& ExtendedCircular<T>::merge(ExtendedCircular<T>& a, ExtendedCircular<T>& b)
{
	ChainNode<T>* cur1 = a.firstNode->next;
	ChainNode<T>* cur2 = b.firstNode->next;
	ChainNode<T>* cur = firstNode;
	int i = 0, j = 0;
	while (i < a.size() && j < b.size()) {
		if (cur1->element <= cur2->element) {
			cur->next = cur1;
			cur = cur1;
			cur1 = cur1->next;
			i++;
		}
		else {
			if (!firstNode) firstNode = cur2;
			else cur->next = cur2;
			cur = cur2;
			cur2 = cur2->next;
			j++;
		}
	}
	for (; i < a.size(); i++) {
		cur->next = cur1;
		cur = cur1;
		cur1 = cur1->next;
	}
	for (; j < b.size(); j++) {
		cur->next = cur2;
		cur = cur2;
		cur2 = cur2->next;
	}
	lastNode = cur;
	cur->next = firstNode;
	listSize = a.listSize + b.listSize;

	a.listSize = b.listSize = 0;
	a.lastNode = a.firstNode;
	a.firstNode->next = a.firstNode;
	b.lastNode = b.firstNode;
	b.firstNode->next = b.firstNode;
	return *this;

}

template<class T>
ExtendedCircular<T>& ExtendedCircular<T>::split(ExtendedCircular<T> & a, ExtendedCircular<T> & b)
{
	if (listSize == 0) return *this;
	ChainNode<T>* cur1 = a.firstNode;
	ChainNode<T>* cur2 = b.firstNode;
	ChainNode<T>* cur = firstNode->next;

	for (int i = 0; i < listSize; i++) {
		if (i % 2 == 0) {
			cur1->next = cur;
			cur1 = cur;
			a.listSize++;
		}
		else {
			cur2->next = cur;
			cur2 = cur;
			b.listSize++;
		}
		cur = cur->next;
	}
	cur1->next = a.firstNode;
	a.lastNode = cur1;
	cur2->next = b.firstNode;
	b.lastNode = cur2;

	listSize = 0;
	lastNode = firstNode;
	firstNode->next = firstNode;

	return *this;
}


template<class T>
ostream& operator<<(ostream& out, const ExtendedCircular<T>& c)
{
	c.output(out);
	return out;
}

template<class T>
void reverse(ExtendedCircular<T>& c, ExtendedCircular<T>& d)//Execise 39
{
	for(int i=0;i<c.size();i++)
		d.insert(0, c.get(i));
}

template<class T>
void meld(const ExtendedCircular<T>& a, const ExtendedCircular<T>& b, ExtendedCircular<T>& c){//Exercise 40
	int smallsize = a.size() <= b.size() ? a.size() : b.size();
	ChainNode<T>* cur1 = a.firstNode->next;
	ChainNode<T>* cur2 = b.firstNode->next;
	for(int i=0;i<smallsize;i++){
		c.push_back(cur1->element);
		c.push_back(cur2->element);
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	while(cur1!=a.firstNode){
		c.push_back(cur1->element);
		cur1 = cur1->next;
	}
	while(cur2 != b.firstNode){
		c.push_back(cur2->element);
		cur2 = cur2->next;
	}
}

template<class T>
void merge(const ExtendedCircular<T>& a, const ExtendedCircular<T>& b, ExtendedCircular<T>& c){ //Execise 41
	ChainNode<T>* cur1 = a.firstNode->next;
	ChainNode<T>* cur2 = b.firstNode->next;
	int i = 0, j = 0;
	while (i < a.size() && j < b.size()) {
		if(cur1->element <= cur2->element){
			c.push_back(cur1->element);
			cur1 = cur1->next;
			i++;
		}else{
			c.push_back(cur2->element);
			cur2 = cur2->next;
			j++;
		}
	}
	for (; i < a.size();i++) {
		c.push_back(cur1->element);
		cur1 = cur1->next;
	}
	for (; j < b.size(); j++) {
		c.push_back(cur2->element);
		cur2 = cur2->next;
	}
}

template<class T>
void split(const ExtendedCircular<T>& c, ExtendedCircular<T>& a, ExtendedCircular<T>& b) { //Execise 42
	if (c.size() == 0) return;
	ChainNode<T>* cur = c.firstNode->next;

	for (int i = 0; i < c.listSize; i++) {
		if (i % 2 == 0)	a.push_back(cur->element);
		else b.push_back(cur->element);
		cur = cur->next;
	}
}

#endif
