#pragma once
#ifndef _CIRCULAR_H
#define _CIRCULAR_H

#include <iostream>
#include "../DS5/exceptions.h"
#include "../DS5/linearlist.h"
#include "chainnode.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 29-37

template<class T>
class Circular : public LinearList<T> {
	template<class T>
	friend void meld(const Circular<T>& a, const Circular<T>& b, Circular<T>& c);//Ecercise 32
	template<class T>
	friend void merge(const Circular<T>& a, const Circular<T>& b, Circular<T>& c);//Ecercise 33
	template<class T>
	friend void split(const Circular<T>& c, Circular<T>& a, Circular<T>& b); //Execise 35

public:
	Circular(int initialCapacity = 10);
	~Circular();

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void erase(int theIndex);
	void output(ostream& out) const;
	void clear();
	void push_back(const T& theElement);

	ChainNode<T>* getNode(int theIndex) const;
	void removeNode(ChainNode<T>* x);//Exercise 37

	Circular<T>& reverse();//Execise 30
	Circular<T>& merge(Circular<T>& a, Circular<T>& b); //Execise 34
	Circular<T>& split(Circular<T>& a, Circular<T>& b); //Execise 36

protected:
	void checkIndex(int theIndex) const;

	ChainNode<T>* firstNode;
	ChainNode<T> * lastNode;
	int listSize;
};

template<class T>
Circular<T>::Circular(int initialCapacity){
	if(initialCapacity < 1){
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0.";
		throw IllegalParameterValue(s.str());
	}
	firstNode = lastNode = nullptr;
	listSize = 0;
}

template<class T>
Circular<T>::~Circular(){
	clear();
}

template<class T>
void Circular<T>::clear()
{
	if (!firstNode) return;
	ChainNode<T>* current = firstNode->next;
	delete firstNode;
	while (current != firstNode) {
		ChainNode<T>* next = current->next;
		delete current;
		current = next;
	}
	firstNode = lastNode = nullptr;
	listSize = 0;
}

template<class T>
void Circular<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
T& Circular<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	ChainNode<T>* current = firstNode;
	int i = 0;
	while (i < theIndex)
	{
		++i;
		current = current->next;
	}
	
	return current->element;
}

template<class T>
ChainNode<T>* Circular<T>::getNode(int theIndex) const
{
	checkIndex(theIndex);

	ChainNode<T>* current = firstNode;
	int i = 0;
	while (i < theIndex)
	{
		++i;
		current = current->next;
	}

	return current;
}

template<class T>
int Circular<T>::indexOf(const T& theElement) const
{
	if (!firstNode) return -1;
	ChainNode<T>* current = firstNode;
	if (current && theElement == current->element) return 0;
	int i = 1;
	current = current->next;
	while (theElement != current->element && current != firstNode)
	{
		current = current->next;
		++i;
	}
	if (current == firstNode) return -1;
	return i;
}

template<class T>
void Circular<T>::output(ostream& out) const
{
	ChainNode<T>* cur = firstNode;
	for (int i=0;i<listSize;i++)
	{
		out << cur->element << " ";
		cur = cur->next;
	}
	
	out << endl;
}

template<class T>
void Circular<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize + 1)	throw OutOfBounds();

	ChainNode<T>* c = new ChainNode<T>;
	c->element = theElement;

	if (theIndex == 0)
	{
		if (listSize == 0)
		{
			c->next = c;
			lastNode = c;
		}
		else c->next = firstNode;
		firstNode = c;
		lastNode->next = c;
	}
	else
	{
		ChainNode<T>* current = firstNode;
		for (int i = 1;i < theIndex ; ++i) current = current->next;
		if (theIndex == listSize) lastNode = c;
		ChainNode<T>* d = current->next;
		current->next = c;
		c->next = d;

	}
	listSize++;
}

template<class T>
void Circular<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	ChainNode<T> * current = firstNode;
	
	for (int i = 0;i < theIndex-1; ++i) current = current->next;
	ChainNode<T> * next = current->next;

	if (theIndex == listSize-1) lastNode = current;

	if (theIndex == 0 && listSize == 1)
	{
		firstNode = lastNode = nullptr;
		delete current;
	}
	else if (theIndex == 0)
	{
		firstNode = current->next;
		lastNode->next = current->next;
		delete current;
	}
	else
	{
		current->next = next->next;
		delete next;
	}
	listSize--;
}

template<class T>
void Circular<T>::push_back(const T& theElement){
	ChainNode<T> * newNode = new ChainNode<T>(theElement, nullptr);
	if(this->firstNode == nullptr){
		this->firstNode = lastNode = newNode;
	}else{
		lastNode->next = newNode;
		lastNode = newNode;
	}
	lastNode->next = firstNode;
	this->listSize++;
}

template<class T>
Circular<T>& Circular<T>::reverse()
{
	if (firstNode == nullptr || firstNode == lastNode) return *this; //empty or 1 node only

	ChainNode<T> * p = lastNode, *q = firstNode, *r = firstNode->next;
	lastNode = firstNode;

	while (r!=firstNode)
	{
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	firstNode = q;
	q->next = p;

	return *this;
}

template<class T>
Circular<T>& Circular<T>::merge(Circular<T>& a, Circular<T>& b)
{
	ChainNode<T>* cur1 = a.firstNode;
	ChainNode<T>* cur2 = b.firstNode;
	ChainNode<T>* cur = nullptr;
	int i = 0, j = 0;
	while (i < a.size() && j < b.size()) {
		if (cur1->element <= cur2->element) {
			if (!firstNode) firstNode = cur1;
			else cur->next = cur1;
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
		if (!firstNode) firstNode = cur1;
		else cur->next = cur1;
		cur = cur1;
		cur1 = cur1->next;
	}
	for (; j < b.size(); j++) {
		if (!firstNode) firstNode = cur2;
		else cur->next = cur2;
		cur = cur2;
		cur2 = cur2->next;
	}
	lastNode = cur;
	if (!cur) cur->next = firstNode;
	listSize = a.listSize + b.listSize;

	a.listSize = b.listSize = 0;
	a.firstNode = a.lastNode = b.firstNode = b.lastNode = nullptr;
	return *this;

}

template<class T>
Circular<T>& Circular<T>::split(Circular<T> & a, Circular<T> & b)
{
	if (listSize == 0) return *this;
	ChainNode<T>* cur1 = nullptr;
	ChainNode<T>* cur2 = nullptr;
	a.firstNode = firstNode;
	cur1 = a.firstNode;
	ChainNode<T>* cur = firstNode->next;
	a.listSize++;

	for (int i = 1; i < listSize && cur != firstNode; i++) {
		if (i % 2 == 0) {
			cur1->next = cur;
			cur1 = cur;
			a.listSize++;
		}
		else {
			if (cur2 == nullptr) b.firstNode = cur;
			else cur2->next = cur;
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
	firstNode = lastNode = nullptr;


	return *this;
}

template<class T>
void Circular<T>::removeNode(ChainNode<T>* x) {
	if (listSize == 1) {
		delete firstNode;
		firstNode = lastNode = nullptr;
		listSize = 0;
		return;
	}

	if (x == lastNode) {
		x->element = firstNode->element;
		x->next = firstNode->next;
		delete firstNode;
		firstNode = x;
		listSize--;
		if (listSize == 1) lastNode = firstNode;
		else {
			for (lastNode = firstNode->next; lastNode->next != firstNode; lastNode = lastNode->next)
				;
		}
	}
	else {
		ChainNode<T>* next = x->next;
		x->element = x->next->element;
		x->next = x->next->next;
		if (next == lastNode) lastNode = x;
		delete next;
		listSize--;
	}
	
}

template<class T>
ostream& operator<<(ostream & out, const Circular<T> & c)
{
	c.output(out);
	return out;
}

template<class T>
void reverse(Circular<T>& c, Circular<T>& d)//Execise 31
{
	for(int i=0;i<c.size();i++)
		d.insert(0, c.get(i));
}

template<class T>
void meld(const Circular<T>& a, const Circular<T>& b, Circular<T>& c){//Exercise 32
	if (a.firstNode) c.push_back(a.firstNode->element);
	if (b.firstNode) c.push_back(b.firstNode->element);
	int smallsize = a.size() <= b.size() ? a.size() : b.size();
	ChainNode<T>* cur1 = a.firstNode->next;
	ChainNode<T>* cur2 = b.firstNode->next;
	for(int i=1;i<smallsize;i++){
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
void merge(const Circular<T>& a, const Circular<T>& b, Circular<T>& c){ //Execise 33
	ChainNode<T>* cur1 = a.firstNode;
	ChainNode<T>* cur2 = b.firstNode;
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
void split(const Circular<T>& c, Circular<T>& a, Circular<T>& b) { //Execise 35
	if (c.size() == 0) return;
	a.push_back(c.firstNode->element);
	ChainNode<T>* cur = c.firstNode->next;

	for (int i = 1; i < c.listSize && cur!=c.firstNode; i++) {
		if (i % 2 == 0)	a.push_back(cur->element);
		else b.push_back(cur->element);
		cur = cur->next;
	}
}

#endif
