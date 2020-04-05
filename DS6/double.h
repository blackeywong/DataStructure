#pragma once
#ifndef _DOUBLE_H
#define _DOUBLE_H

#include <iostream>
#include <sstream>
#include <initializer_list>
#include "../DS5/exceptions.h"
#include "../DS5/linearlist.h"
#include "doublenode.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 43-48

template<class T>
class Double : public LinearList<T> {
	template<class T>
	friend void meld(const Double<T>& a, const Double<T>& b, Double<T>& c);//Ecercise 46
	template<class T>
	friend void merge(const Double<T>& a, const Double<T>& b, Double<T>& c);//Ecercise 47
	template<class T>
	friend void split(const Double<T>& c, Double<T>& a, Double<T>& b); //Execise 48
public:
	Double(int initialCapacity = 10);
	Double(const T& element);
	Double(const initializer_list<T>& list);
	~Double();

	Double<T>& operator=(Double<T>& right);

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void erase(int theIndex);
	void output(ostream& out) const;
	void clear();
	void push_back(const T& theElement);

	Double<T>& concat(Double<T>& a); //Exercise 44

	Double<T>& reverse();//Execise 45
	Double<T>& meld(Double<T>& a, Double<T>& b);//Exercise 46
	Double<T>& merge(Double<T>& a, Double<T>& b); //Execise 47
	Double<T>& split(Double<T>& a, Double<T>& b); //Execise 48

public:
	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(nullptr); }
	iterator last() { return iterator(lastNode); }
	void erase(iterator iter);
protected:
	void checkIndex(int theIndex) const;

	DoubleNode<T>* firstNode;
	DoubleNode<T> * lastNode;
	int listSize;
};


template<class T>
class Double<T>::iterator {
public:
	typedef bidirectional_iterator_tag iterator_capacity;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	iterator(DoubleNode<T>* theNode = nullptr) { node = theNode; }

	T& operator*() const { return node->element; }
	T* operator->() const { return &node->element; }

	iterator& operator++() { node = node->right; return *this; }
	iterator operator++(int) { iterator old = *this; node = node->right; return old; }
	iterator& operator--() { node = node->left; return *this; }
	iterator operator--(int) { iterator old = *this; node = node->left; return old; }

	bool operator!=(const iterator right) const { return node != right.node; }
	bool operator==(const iterator right) const { return node == right.node; }

	iterator operator+(const ptrdiff_t diff) {
		DoubleNode<T>* p = node;
		for (int i = 0; i < diff; i++) p = p->right;
		return iterator(p);
	}

	DoubleNode<T>* node;
};

template<class T>
Double<T>::Double(int initialCapacity)
{
	if (initialCapacity < 1) {
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " must be > 0.";
		throw IllegalParameterValue(s.str());
	}
	firstNode = lastNode = nullptr;
	listSize = 0;
}

template<class T>
Double<T>::Double(const T& element)
{
	firstNode = lastNode = nullptr;
	listSize = 0;
	insert(listSize, element);
}

template<class T>
Double<T>::Double(const initializer_list<T>& list)
{
	firstNode = lastNode = nullptr;
	listSize = 0;
	for(auto b=list.begin();b<list.end();b++)
		insert(listSize, *b);
}

template<class T>
Double<T>::~Double() {
	clear();
}

template<class T>
void Double<T>::clear()
{
	if (!firstNode) return;
	DoubleNode<T>* current = firstNode;
	while (current) {
		DoubleNode<T>* right = current->right;
		delete current;
		current = right;
	}
	firstNode = lastNode = nullptr;
	listSize = 0;
}

template<class T>
Double<T>& Double<T>::operator=(Double<T>& right) {
	if (!right.firstNode) return *this;
	DoubleNode<T>* current = right.firstNode;
	while (current) {
		push_back(current->element);
		current = current->right;
	}

	return *this;
}

template<class T>
void Double<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize) {
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw IllegalIndex(s.str());
	}
}

template<class T>
T& Double<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	DoubleNode<T> * current = firstNode;
	int i = 0;
	while (i < theIndex && current)
	{
		++i;
		current = current->right;
	}

	return current->element;
}

template<class T>
int Double<T>::indexOf(const T& theElement) const
{
	if (!firstNode) return -1;
	DoubleNode<T>* current = firstNode;
	int i = 0;
	while (theElement != current->element && current)
	{
		current = current->right;
		++i;
	}
	if (theElement != current->element) return -1;
	return i;
}

template<class T>
void Double<T>::output(ostream & out) const
{
	DoubleNode<T>* current = firstNode;
	while (current)
	{
		out << current->element << " ";
		current = current->right;
	}
	out << endl;
}

template<class T>
void Double<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)	throw OutOfBounds();

	DoubleNode<T> * c = new DoubleNode<T>;
	c->element = theElement;

	DoubleNode<T>* current = firstNode;
	for (int i = 0; i < theIndex-1 && current; ++i) current = current->right;

	if (theIndex == 0){
		if (!firstNode) {
			c->right = nullptr;
			firstNode = lastNode = c;
		}
		else {
			c->right = current;
			current->left = c;
			firstNode = c;
		}
		c->left = nullptr;
	}
	else {
		c->left = current;
		c->right = current->right;
		if(current->right) current->right->left = c;
		current->right = c;
		if (current == lastNode) lastNode = c;
	}
	listSize++;
}

template<class T>
void Double<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	DoubleNode<T> * current = firstNode;

	for (int i = 0; i < theIndex && current; ++i) current = current->right;

	if (theIndex == 0)
	{

		if (firstNode == lastNode) firstNode=lastNode = nullptr;
		else {
			current->right->left = nullptr;
			firstNode = current->right;
		}
	}
	else
	{
		current->left->right = current->right;
		if (current == lastNode) {
			current->left->right = nullptr;
			lastNode = current->left;
		}
		else {
			current->right->left = current->left;
		}
	}
	
	delete current;

	listSize--;
}

template<class T>
void Double<T>::erase(Double<T>::iterator iter) {
	if (iter == end()) return;
	if (iter == firstNode) {
		if (firstNode == lastNode) {
			firstNode = lastNode = nullptr;
		}
		else {
			firstNode = iter.node->right;
			iter.node->right->left = iter.node->left;
		}
	}
	else {
		if (iter == lastNode) {
			lastNode = lastNode->left;
		}
		else {
			iter.node->right->left = iter.node->left;
		}
		iter.node->left->right = iter.node->right;
	}
	listSize--;
	delete iter.node;

}

template<class T>
void Double<T>::push_back(const T& theElement){
	DoubleNode<T> * newNode = new DoubleNode<T>(theElement, nullptr, nullptr);
	newNode->left = lastNode;
	if(listSize == 0){
		firstNode = lastNode = newNode;
	}else{
		lastNode->right = newNode;
		lastNode = newNode;
	}
	lastNode->right = nullptr;
	this->listSize++;
}

template<class T>
Double<T>& Double<T>::concat(Double<T>& a)
{
	if (a.listSize == 0) return *this;

	if (listSize == 0) {
		firstNode = a.firstNode;
	}
	else{
		lastNode->right = a.firstNode;
		a.firstNode->left = lastNode;
	}
	lastNode = a.lastNode;
	listSize += a.listSize;

	a.firstNode = a.lastNode = nullptr;
	a.listSize = 0;

	return *this;
}

template<class T>
Double<T>& Double<T>::reverse()
{
	if (listSize <= 1) return *this;

	DoubleNode<T> * p = firstNode;
	firstNode = lastNode;
	lastNode = p;

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
Double<T>& Double<T>::meld(Double<T>& a, Double<T>& b)
{
	DoubleNode<T>* curA = a.firstNode;
	DoubleNode<T>* curB = b.firstNode;
	DoubleNode<T>* cur = nullptr;

	while (curA && curB)
	{
		if (!firstNode) {
			firstNode = curA;
		}
		else{
			cur->right = curA;
			curA->left = cur;
		}
		cur = curA;
		curA = curA->right;
		cur->right = curB;
		curB->left = cur;
		curB = curB->right;
		cur->right->left = cur;
		cur->right->right = nullptr;
		cur = cur->right;
		lastNode = cur;
	}
	
	DoubleNode<T>* left = curA != nullptr ? curA : curB;
	while (left)
	{
		if (!firstNode) {
			firstNode = left;
		}
		else if (cur) {
			cur->right = left;
			left->left = cur;
		}
		cur = left;
		left = left->right;
		cur->right = nullptr;
		lastNode = cur;
	}
	listSize = a.listSize + b.listSize;

	a.firstNode = a.lastNode = b.firstNode = b.lastNode = nullptr;
	a.listSize = b.listSize = 0;
	return *this;
}

template<class T>
Double<T>& Double<T>::merge(Double<T> & a, Double<T> & b)
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
		cur->right = nullptr;
		firstNode->left = nullptr;
	}
	listSize = a.listSize + b.listSize;

	a.firstNode = a.lastNode = b.firstNode = b.lastNode = nullptr;
	a.listSize = b.listSize = 0;
	return *this;
}

template<class T>
Double<T>& Double<T>::split(Double<T> & a, Double<T> & b)
{
	DoubleNode<T> * cur = firstNode;
	DoubleNode<T>* curA = nullptr;
	DoubleNode<T>* curB = nullptr;

	int i = 0;
	while (cur)
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
				cur->left=nullptr;
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
		++i;
	} 
	a.lastNode->right = nullptr;
	b.lastNode->right = nullptr;

	firstNode = lastNode = nullptr;
	listSize = 0;
	return *this;
}

template<class T>
ostream& operator<<(ostream & out, const Double<T> & c)
{
	c.output(out);
	return out;
}

template<class T>
void reverse(Double<T>& c, Double<T>& d)//Execise 45
{
	for(int i=0;i<c.size();i++)
		d.insert(0, c.get(i));
}

template<class T>
void meld(const Double<T>& a, const Double<T>& b, Double<T>& c){
	int smallsize = a.size() <= b.size() ? a.size() : b.size();
	DoubleNode<T>* cur1 = a.firstNode;
	DoubleNode<T>* cur2 = b.firstNode;
	for(int i=0;i<smallsize;i++){
		c.push_back(cur1->element);
		c.push_back(cur2->element);
		cur1 = cur1->right;
		cur2 = cur2->right;
	}
	while(cur1!=nullptr){
		c.push_back(cur1->element);
		cur1 = cur1->right;
	}
	while(cur2 != nullptr){
		c.push_back(cur2->element);
		cur2 = cur2->right;
	}
}

template<class T>
void merge(const Double<T>& a, const Double<T>& b, Double<T>& c){
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
void split(const Double<T>& c, Double<T>& a, Double<T>& b) {
	if (c.size() == 0) return;
	DoubleNode<T>* cur = c.firstNode;

	for (int i = 0; i < c.listSize; i++) {
		if (i % 2 == 0)	a.push_back(cur->element);
		else b.push_back(cur->element);
		cur = cur->right;
	}
}


#endif
