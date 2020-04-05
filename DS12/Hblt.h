#pragma once
#ifndef _HBLT_H
#define _HBLT_H

#include <algorithm>
#include <xutility>
#include <iostream>

#include "../DS5/changelength.h"
#include "MaxPriorityQueue.h"
#include "../DS11/LinkedBinaryTree.h"
#include "../DS9/arrayQueue.h"

template<class T>
class Hblt :virtual public MaxPriorityQueue<T>, public LinkedBinaryTree<std::pair<int, T>> {
	template <class T> friend std::istream& operator>>(std::istream& in, const Hblt<T>& mh);
	template <class T> friend std::ostream& operator<<(std::ostream& out, const Hblt<T>& mh);
public:
	Hblt() = default;
	explicit Hblt(bool theMaxHblt) :maxHblt(theMaxHblt) {}
	explicit Hblt(T* theElements, int theSize, bool theMaxHblt = true):maxHblt(theMaxHblt) { initialize(theElements, theSize);}
	virtual ~Hblt() { this->erase(); }

	virtual bool empty() const override { return this->treeSize == 0; }
	virtual int size() const override { return this->treeSize; }
	virtual const T& top() override;
	virtual void pop() override;
	virtual void push(const T& theElement) override;
	virtual void meld(Hblt<T>& theHblt);

public:
	class Iterator;//Exercise 22
	friend class Iterator;
	Iterator begin() { return Iterator(*this); }
	Iterator end() { return Iterator(); }

protected:
	void input(std::istream& in);
	void output(std::ostream& out) const;

	virtual void initialize(T* theElements, int theSize);
	virtual void meld(BinaryTreeNode<std::pair<int, T>>*& x, BinaryTreeNode<std::pair<int, T>>*& y);

	bool maxHblt;
};

template <class T>
std::istream& operator>>(std::istream& in, Hblt<T>& mh) {
	mh.input(in);
	return(in);
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Hblt<T>& mh) {
	mh.output(out);
	return out;
}

template<class T>
const T& Hblt<T>::top()
{
	if (this->treeSize == 0)
		throw std::out_of_range("emtpy heap");

	return this->root->element.second;
}

template<class T>
void Hblt<T>::pop()
{
	if (this->treeSize == 0)
		throw std::out_of_range("emtpy heap");

	BinaryTreeNode<std::pair<int, T>>* left = this->root->leftChild;
	BinaryTreeNode<std::pair<int, T>>* right = this->root->rightChild;

	delete(this->root);
	this->root = left;
	meld(this->root, right);
	--this->treeSize;
}

template<class T>
void Hblt<T>::push(const T& theElement)
{
	BinaryTreeNode<std::pair<int, T>>* q = new BinaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElement));

	meld(this->root, q);
	++this->treeSize;
}

template<class T>
void Hblt<T>::meld(Hblt<T>& theHblt) {
	meld(this->root, theHblt.root);
	this->treeSize += theHblt.treeSize;
	theHblt.root = nullptr;
	theHblt.treeSize = 0;
}

template<class T>
void Hblt<T>::input(std::istream& in) {
	int theSize;
	in >> theSize;
	T* theElements = new T[theSize + 1];
	T t;
	int i = 0;
	while (i <= theSize && in >> t) {
		theElements[++i] = t;
	}
	initialize(theElements, theSize);
	delete[]theElements;
}

template<class T>
void Hblt<T>::output(std::ostream& out) const {
	if (this->root) {
		//out << "------"
	}
}

template<class T>
void Hblt<T>::initialize(T* theElements, int theSize)
{
	arrayQueue<BinaryTreeNode<std::pair<int, T>>*> q(theSize);
	this->erase();

	for (int i = 1; i <= theSize; ++i) {
		q.push(new BinaryTreeNode<std::pair<int, T>>(pair<int, T>(1, theElements[i])));
	}

	for (int i = 1; i <= theSize - 1; ++i) {
		BinaryTreeNode<std::pair<int, T>>* b = q.front();
		q.pop();
		BinaryTreeNode<std::pair<int, T>>* c = q.front();
		q.pop();
		meld(b, c);
		q.push(b);
	}

	if (theSize > 0) {
		this->root = q.front();
	}
	this->treeSize = theSize;
}

template<class T>
void Hblt<T>::meld(BinaryTreeNode<std::pair<int, T>>*& x, BinaryTreeNode<std::pair<int, T>>*& y) {
	if (y == nullptr)
		return;

	if (x == nullptr) {
		x = y;
		y = nullptr;
		return;
	}

	using std::swap;
	if (maxHblt) {
		if (x->element.second < y->element.second) {
			swap(x, y);
		}
	}
	else {
		if (x->element.second > y->element.second) {
			swap(x, y);
		}
	}

	meld(x->rightChild, y);

	if (x->leftChild == nullptr) {
		x->leftChild = x->rightChild;
		x->rightChild = nullptr;
		x->element.first = 1;
	}
	else {
		if (x->leftChild->element.first < x->rightChild->element.first) {
			swap(x->leftChild, x->rightChild);
		}
		x->element.first = x->rightChild->element.first + 1;
	}
}

template<class T>
class Hblt<T>::Iterator {
public:
	typedef std::forward_iterator_tag iterator_capacity;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	Iterator() { this->node = nullptr; }
	explicit Iterator(Hblt<T>& t) { this->node = t.root; }

	Iterator(const Iterator& t) { this->node = t.node; stack = t.stack; }

	T& operator*() const { return node->element.second; }
	T* operator->() const { return &node->element.second; }

	Iterator& operator++() {
		if (this->node->rightChild != nullptr) {
			stack.push(this->node->rightChild);
		}
		if (this->node->leftChild != nullptr)
		{
			this->node = this->node->leftChild;
		}
		else {
			if (!stack.empty()) {
				this->node = stack.top();
				stack.pop();
			}
			else {
				this->node = nullptr;
			}
		}
		return *this;
	}
	Iterator operator++(int) { Iterator old = *this; operator++(); return old; }

	bool operator!=(const Iterator& right) const { return node != right.node; }
	bool operator==(const Iterator& right) const { return node == right.node; }

	 void swap(Iterator& right) { 
		 using std::swap; 
		 swap(this->node->element.first, right.node->element.first); 
		 swap(this->node->element.second, right.node->element.second);
	 }
protected:
	BinaryTreeNode<std::pair<int, T>>* node;
	std::stack<BinaryTreeNode<std::pair<int, T>>*> stack;
};

template<class T>
void swap(typename Hblt<T>::Iterator& it1, typename Hblt<T>::Iterator& it2) { it1.swap(it2); }


#endif 