#pragma once
#ifndef _EXTENDEDDOUBLECIRCULAR_H
#define _EXTENDEDDOUBLECIRCULAR_H

#include <iostream>
#include <sstream>
#include "../DS5/exceptions.h"
#include "../DS5/linearlist.h"
#include "doublenode.h"
#include <list>
using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 55-61

template<class T>
class ExtendedDoubleCircular : public LinearList<T> {
	template<class T>
	friend void meld(const ExtendedDoubleCircular<T>& a, const ExtendedDoubleCircular<T>& b, ExtendedDoubleCircular<T>& c);//Ecercise 58
	template<class T>
	friend void merge(const ExtendedDoubleCircular<T>& a, const ExtendedDoubleCircular<T>& b, ExtendedDoubleCircular<T>& c);//Ecercise 59
	template<class T>
	friend void split(const ExtendedDoubleCircular<T>& c, ExtendedDoubleCircular<T>& a, ExtendedDoubleCircular<T>& b); //Execise 60

public:
	ExtendedDoubleCircular(int initialCapacity = 10);
	ExtendedDoubleCircular(const T& element);
	ExtendedDoubleCircular(const initializer_list<T>& list);
	~ExtendedDoubleCircular();

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void erase(int theIndex);
	void output(ostream& out) const;
	void clear();
	void push_back(const T& theElement);

	ExtendedDoubleCircular<T>& concat(ExtendedDoubleCircular<T>& a); //Exercise 57

	ExtendedDoubleCircular<T>& reverse();//Execise 56
	ExtendedDoubleCircular<T>& meld(ExtendedDoubleCircular<T>& a, ExtendedDoubleCircular<T>& b);//Exercise 58
	ExtendedDoubleCircular<T>& merge(ExtendedDoubleCircular<T>& a, ExtendedDoubleCircular<T>& b); //Execise 59
	ExtendedDoubleCircular<T>& split(ExtendedDoubleCircular<T>& a, ExtendedDoubleCircular<T>& b); //Execise 60

public:
	class iterator;
	iterator begin(){return iterator(firstNode->right);}
	iterator end(){return iterator(firstNode);}
	void erase(iterator iter);
protected:
	void checkIndex(int theIndex) const;

	DoubleNode<T>* firstNode;
	int listSize;
};


template<class T>
class ExtendedDoubleCircular<T>::iterator {
public:
	typedef bidirectional_iterator_tag iterator_capacity;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	iterator(DoubleNode<T>* theNode = nullptr) { node = theNode;}

	T& operator*() const { return node->element;}
	T* operator->() const { return &node->element;}

	iterator& operator++() { node = node->right; return * this;}
	iterator operator++(int) {iterator old = *this; node = node->right; return old; }
	iterator& operator--() { node = node->left; return *this; }
	iterator operator--(int) { iterator old = *this; node = node->left; return old; }

	bool operator!=(const iterator right) const {return node != right.node;}
	bool operator==(const iterator right) const {return node == right.node;}

	//bool operator<(const iterator right) const { return node < right.node; }
	iterator operator+(const ptrdiff_t diff) {
		DoubleNode<T>* p = node;
		for (int i = 0; i < diff; i++) p = p->right;
		return iterator(p);
	}

	iterator operator-(const ptrdiff_t diff) {
		DoubleNode<T>* p = node;
		for (int i = 0; i < diff; i++) p = p->left;
		return iterator(p);
	}

	DoubleNode<T>* node;
};


template<class T>
ExtendedDoubleCircular<T>::ExtendedDoubleCircular(int initialCapacity)
{
	if (initialCapacity < 1) {
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0.";
		throw IllegalParameterValue(s.str());
	}
	DoubleNode<T>* t = new DoubleNode<T>;
	t->left = t;
	t->right = t;
	firstNode = t;
	listSize = 0;
}

template<class T>
ExtendedDoubleCircular<T>::ExtendedDoubleCircular(const T& element) : ExtendedDoubleCircular()
{
	insert(listSize, element);
}

template<class T>
ExtendedDoubleCircular<T>::ExtendedDoubleCircular(const initializer_list<T>& list) : ExtendedDoubleCircular()
{
	for (auto b = list.begin(); b < list.end(); b++)
		insert(listSize, *b);
}

template<class T>
ExtendedDoubleCircular<T>::~ExtendedDoubleCircular() {
	clear();
}

template<class T>
void ExtendedDoubleCircular<T>::clear()
{
	DoubleNode<T>* cur = firstNode->right;

	while (cur != firstNode) {
		DoubleNode<T>* right = cur->right;
		delete cur;
		cur = right;
	}
	firstNode->right = firstNode;
	firstNode->left = firstNode;
	listSize = 0;
}

template<class T>
void ExtendedDoubleCircular<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
T& ExtendedDoubleCircular<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	DoubleNode<T> * cur = firstNode->right;
	for (int i = 0; i < theIndex; ++i) {
		cur = cur->right;
	}

	return cur->element;
}

template<class T>
int ExtendedDoubleCircular<T>::indexOf(const T& theElement) const
{
	if (firstNode == firstNode->right) return -1;
	DoubleNode<T>* cur = firstNode->right;
	int i = 0;
	while (theElement != cur->element && i<listSize)
	{
		cur = cur->right;
		++i;
	}
	if (i == listSize) return -1;
	return i;
}

template<class T>
void ExtendedDoubleCircular<T>::output(ostream & out) const
{
	DoubleNode<T>* cur = firstNode->right;
	while (cur != firstNode)
	{
		out << cur->element << " ";
		cur = cur->right;
	}

	out << endl;
}

template<class T>
void ExtendedDoubleCircular<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)	throw OutOfBounds();

	DoubleNode<T> * c = new DoubleNode<T>;
	c->element = theElement;

	DoubleNode<T>* current = firstNode;
	for (int i = 0; i < theIndex && current; ++i) current = current->right;
	c->left = current;
	c->right = current->right;
	current->right->left = c;
	current->right = c;
	listSize++;
}

template<class T>
void ExtendedDoubleCircular<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	DoubleNode<T> * cur = firstNode->right;
	int i = 0;
	for (; i < theIndex; ++i) cur = cur->right;

	cur->left->right=cur->right;
	cur->right->left=cur->left;
	delete cur;

	listSize--;
}

template<class T>
void ExtendedDoubleCircular<T>::erase(ExtendedDoubleCircular<T>::iterator iter) {
	if (iter == firstNode) return;
	iter.node->left->right = iter.node->right;
	iter.node->right->left = iter.node->left;
	listSize--;
	delete iter.node;

}

template<class T>
void ExtendedDoubleCircular<T>::push_back(const T& theElement){
	DoubleNode<T> * newNode = new DoubleNode<T>(theElement, nullptr, nullptr);
	
	newNode->left = firstNode->left;
	newNode->right = firstNode;
	firstNode->left->right = newNode;
	firstNode->left = newNode;
	
	this->listSize++;
}

template<class T>
ExtendedDoubleCircular<T>& ExtendedDoubleCircular<T>::concat(ExtendedDoubleCircular<T>& a)
{
	if (a.listSize == 0) return *this;

	firstNode->left->right = a.firstNode->right;
	a.firstNode->right->left = firstNode->left;
	firstNode->left = a.firstNode->left;
	a.firstNode->left->right = firstNode;

	listSize += a.listSize;

	a.firstNode->left = a.firstNode->right = a.firstNode;
	a.listSize = 0;

	return *this;
}

template<class T>
ExtendedDoubleCircular<T> & ExtendedDoubleCircular<T>::reverse()
{
	if (listSize <= 1) return *this;

	DoubleNode<T> * p = firstNode;

	for (int i=0;i<=listSize;i++)
	{
		DoubleNode<T> * q = p->right;
		p->right = p->left;
		p->left = q;
		p = q;
	}

	return *this;
}

template<class T>
ExtendedDoubleCircular<T>& ExtendedDoubleCircular<T>::meld(ExtendedDoubleCircular<T> & a, ExtendedDoubleCircular<T> & b)
{
	DoubleNode<T>* curA = a.firstNode->right;
	DoubleNode<T>* curB = b.firstNode->right;
	DoubleNode<T>* cur = firstNode;
	int i=0,j=0;
	for (;i<a.listSize&&j<b.listSize;i++,j++)
	{
		cur->right = curA;
		curA->left = cur;
		cur=curA;
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
	}

	DoubleNode<T>* left = a.listSize >= b.listSize ? curA : curB;
	int leftsize = a.listSize >= b.listSize ? a.listSize : b.listSize;
	for (;i < leftsize;i++)
	{
		cur->right = left;
		cur = left;
		left = left->right;
	}
	if(cur)
	{
		cur->right = firstNode;
		firstNode->left = cur;	
	}
	listSize = a.listSize + b.listSize;
	a.firstNode->left = a.firstNode->right = a.firstNode;
	b.firstNode->left = b.firstNode->right = b.firstNode;
	a.listSize = b.listSize = 0;
	return *this;
}

template<class T>
ExtendedDoubleCircular<T>& ExtendedDoubleCircular<T>::merge(ExtendedDoubleCircular<T> & a, ExtendedDoubleCircular<T> & b)
{
	DoubleNode<T>* curA = a.firstNode->right;
	DoubleNode<T>* curB = b.firstNode->right;
	DoubleNode<T>* cur = firstNode;
	int i = 0, j = 0;
	while (i < a.size() && j < b.size()) {
		if(curA->element <= curB->element){
			cur->right = curA;
			curA->left = cur;
			cur = curA;
			curA = curA->right;
			i++;
		}else{
			cur->right = curB;
			curB->left = cur;
			cur = curB;
			curB = curB->right;
			j++;
		}
	}
	for (; i < a.size();i++) {
		cur->right = curA;
		curA->left = cur;
		cur = curA;
		curA = curA->right;
	}
	for (; j < b.size(); j++) {
		cur->right = curB;
		curB->left = cur;
		cur = curB;
		curB = curB->right;
	}
	if(cur){
		cur->right = firstNode;
		firstNode->left = cur;
	}
	listSize = a.listSize+b.listSize;
	a.firstNode->left = a.firstNode->right = a.firstNode;
	b.firstNode->left = b.firstNode->right = b.firstNode;
	a.listSize = b.listSize = 0;
	return *this;
}


template<class T>
ExtendedDoubleCircular<T>& ExtendedDoubleCircular<T>::split(ExtendedDoubleCircular<T> & a, ExtendedDoubleCircular<T> & b)
{
	DoubleNode<T> * cur = firstNode->right ;
	DoubleNode<T>* curA = a.firstNode;
	DoubleNode<T>* curB = b.firstNode;

	for(int i=0;i<listSize;i++)
	{
		if (i % 2 == 0){
			curA->right = cur;
			cur->left = curA;
			curA = cur;
			a.listSize++;
		}
		else {
			curB->right = cur;
			cur->left=curB;
			curB = cur;
			b.listSize++;
		}
		cur = cur->right;
	} 
	curA->right = a.firstNode;
	a.firstNode->left = curA;
	curB->right = b.firstNode;
	b.firstNode->left = curB;

	firstNode->left = firstNode->right = firstNode;
	listSize = 0;
	return *this;
}

template<class T>
ostream& operator<<(ostream & out, const ExtendedDoubleCircular<T> & c)
{
	c.output(out);
	return out;
}

template<class T>
void reverse(ExtendedDoubleCircular<T>& c, ExtendedDoubleCircular<T>& d)//Execise 56
{
	for(int i=0;i<c.size();i++)
		d.insert(0, c.get(i));
}

template<class T>
void meld(const ExtendedDoubleCircular<T>& a, const ExtendedDoubleCircular<T>& b, ExtendedDoubleCircular<T>& c){
	DoubleNode<T>* cur1 = a.firstNode->right;
	DoubleNode<T>* cur2 = b.firstNode->right;
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
void merge(const ExtendedDoubleCircular<T>& a, const ExtendedDoubleCircular<T>& b, ExtendedDoubleCircular<T>& c){
	DoubleNode<T>* cur1 = a.firstNode->right;
	DoubleNode<T>* cur2 = b.firstNode->right;
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
void split(const ExtendedDoubleCircular<T>& c, ExtendedDoubleCircular<T>& a, ExtendedDoubleCircular<T>& b) {
	if (c.size() == 0) return;
	DoubleNode<T>* cur = c.firstNode->right;

	for (int i = 0; i < c.listSize; i++) {
		if (i % 2 == 0)	a.push_back(cur->element);
		else b.push_back(cur->element);
		cur = cur->right;
	}
}


#endif
