#ifndef _MOVELEFTANDRIGHTONCHAIN_H
#define _MOVELEFTANDRIGHTONCHAIN_H
#include<iostream>
#include<sstream>
#include<string>
#include "../DS5/linearlist.h"
#include "chainnode.h"
#include "chain.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 24, 25
template<class T>
class MoveLeftAndRightOnChain : public LinearList<T>
{
public:
	MoveLeftAndRightOnChain(int initialCapacity = 10);
	~MoveLeftAndRightOnChain();

	MoveLeftAndRightOnChain<T>& operator=(MoveLeftAndRightOnChain<T>& right);

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void erase(int theIndex);
	void output(ostream& out) const;

	void reset();
	T& current() const;
	T& previous() const;
	bool atEnd() const;
	bool atFront() const;
	void moveToNext();
	void moveToPrevious();

	T& last() const;
	T& lastSecond() const;
protected:
	void checkIndex(int theIndex) const;

	ChainNode<T>* p;
	ChainNode<T>* l;

	int listSize;
	int currentElement;
};


template<class T>
MoveLeftAndRightOnChain<T>::MoveLeftAndRightOnChain(int initialCapacity){
	if(initialCapacity < 1){
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0.";
		throw IllegalParameterValue(s.str());
	}
	p = l = nullptr;
	listSize = 0;
	currentElement = -1;
}

template<class T>
MoveLeftAndRightOnChain<T>::~MoveLeftAndRightOnChain(){
	while(l){
		ChainNode<T> * next = l->next;
		delete l;
		l = next;
	}

	while(p){
		ChainNode<T> * next = p->next;
		delete p;
		p = next;
	}
}

template<class T>
MoveLeftAndRightOnChain<T>& MoveLeftAndRightOnChain<T>::operator=(MoveLeftAndRightOnChain<T>& right) {
	ChainNode<T>* cur = right.l;
	while (cur) {
		insert(0, cur->element);
		cur = cur->next;
	}

	cur = right.p;
	while (cur) {
		insert(listSize, cur->element);
		cur = cur->next;
	}
	return *this;
}

template<class T>
void MoveLeftAndRightOnChain<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
T& MoveLeftAndRightOnChain<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	if(theIndex>=currentElement){
		ChainNode<T>* cur = p;
		int i = currentElement;
		while (i< theIndex && cur)
		{
			++i;
			cur = cur->next;
		}
		return cur->element;
	}else{
		ChainNode<T>* cur = l;
		int i = currentElement-1;
		while (i> theIndex && cur)
		{
			--i;
			cur = cur->next;
		}
		return cur->element;
	}
}

template<class T>
int MoveLeftAndRightOnChain<T>::indexOf(const T& theElement) const
{
	ChainNode<T>* cur = p;
	int i = currentElement;
	while (cur && theElement != cur->element)//add the judgement in condition
	{
		cur = cur->next;
		++i;
	}

	if (cur) return i;

	cur = l;
	i = currentElement-1;
	while (cur && theElement != cur->element)//add the judgement in condition
	{
		cur = cur->next;
		--i;
	}

	if (cur) return i;
	return -1;
}

template<class T>
void MoveLeftAndRightOnChain<T>::output(ostream& out) const
{
	ChainNode<T>* cur = l;
	string s = "";
	ostringstream ss;
	while(cur){
		s.insert(0," ");
		ss.clear();
		ss << cur->element;
		s.insert(0,ss.str());
		cur = cur->next;
	}
	out << s;
	cur = p;
	while (cur)
	{
		out << cur->element << " ";
		cur = cur->next;
	}
	out << endl;
}

template<class T>
void MoveLeftAndRightOnChain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)	throw OutOfBounds();

	ChainNode<T>* c = new ChainNode<T>;
	c->element = theElement;

	if(theIndex >= currentElement){
		ChainNode<T>* cur = p;
		int i = currentElement;
		while (i < theIndex-1 && cur)
		{
			cur = cur->next;
			++i;
		}

		if (theIndex == currentElement||currentElement == -1)
		{
			c->next = p;
			p = c;
			if(currentElement == -1) currentElement = 0;
		}
		else
		{
			ChainNode<T>* d = cur->next;
			cur->next = c;
			c->next = d;
		}
		listSize++;
	}else{
		ChainNode<T>* cur = l;
		int i = currentElement-1;
		while (i > theIndex+1 && cur)
		{
			cur = cur->next;
			--i;
		}

		ChainNode<T>* d = cur->next;
		cur->next = c;
		c->next = d;
		listSize++;	
		currentElement++;
	}
}

template<class T>
void MoveLeftAndRightOnChain<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	if(theIndex >= currentElement){
		ChainNode<T>* cur = p;
		int i = currentElement;
		while (i < theIndex-1 && cur)
		{
			cur = cur->next;
			++i;
		}

		ChainNode<T>* next = cur->next;
		
		if (theIndex == currentElement)
		{
			p = cur->next;
			delete cur;
			if(theIndex == listSize -1) 
				moveToPrevious();
		}
		else
		{
			cur->next = next->next;
			delete next;
		}
	}else{
		ChainNode<T>* cur = l;
		int i = currentElement-1;
		while (i > theIndex+1 && cur)
		{
			cur = cur->next;
			--i;
		}

		ChainNode<T>* next = cur->next;
		
		if (theIndex == currentElement-1)
		{
			l = cur->next;
			delete cur;
		}
		else
		{
			cur->next = next->next;
			delete next;
		}
		currentElement--;
	}
	listSize--;
}

template<class T>
void MoveLeftAndRightOnChain<T>::reset(){
	if(l == nullptr) return;

	for(int i=currentElement;i>0;i--){
		ChainNode<T>* next = l->next;
		l->next = p;
		p = l;
		l = next;
	}
	currentElement = 0;
}

template<class T>
T& MoveLeftAndRightOnChain<T>::current() const{
	if(p) return p->element;
	throw OutOfBounds();
}

template<class T>
T& MoveLeftAndRightOnChain<T>::previous() const{
	if(l) return l->element;
	throw OutOfBounds();
}

template<class T>
bool MoveLeftAndRightOnChain<T>::atEnd() const{
	return p == nullptr || p->next == nullptr;
}

template<class T>
bool MoveLeftAndRightOnChain<T>::atFront() const{
	return l == nullptr;
}

template<class T>
void MoveLeftAndRightOnChain<T>::moveToNext(){
	if(p == nullptr) return;

	ChainNode<T>* next = p->next;
	p->next = l;
	l = p;
	p = next;
	currentElement++;
}

template<class T>
void MoveLeftAndRightOnChain<T>::moveToPrevious(){
	if(l == nullptr) return;

	ChainNode<T>* next = l->next;
	l->next = p;
	p = l;
	l = next;
	currentElement--;
}

template<class T>
T& MoveLeftAndRightOnChain<T>::last() const {
	if (p == nullptr && l == nullptr) throw OutOfBounds();
	if (p == nullptr) return l->element;

	ChainNode<T>* previous = p;
	ChainNode<T>* current = p->next;
	while (current) {
		previous = current;
		current = current->next;
	}
	return previous->element;
}

template<class T>
T& MoveLeftAndRightOnChain<T>::lastSecond() const {
	if(listSize<=1) throw OutOfBounds();
	if (p == nullptr) return l->next->element;
	if (p->next == nullptr) return l->element;

	ChainNode<T>* previousSecond = p;
	ChainNode<T>* previous = previousSecond->next;
	ChainNode<T>* current = previous->next;
	while (current) {
		previousSecond = previous;
		previous = current;
		current = current->next;
	}
	return previousSecond->element;
}

template<class T>
ostream& operator<<(ostream& out, const MoveLeftAndRightOnChain<T>& c)
{
	c.output(out);
	return out;
}


#endif
