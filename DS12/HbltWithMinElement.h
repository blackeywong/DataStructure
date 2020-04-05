#pragma once
#ifndef _HBLTWITHMINELEMENT_H
#define _HBLTWITHMINELEMENT_H

#include "Hblt.h"

template<class T>
class HbltWithMinElement : public Hblt<T> {
public:
	HbltWithMinElement() = default;
	HbltWithMinElement(T* theElements, int theSize, bool theMaxHblt = true) { this->maxHblt = theMaxHblt; initialize(theElements, theSize);}
	virtual ~HbltWithMinElement() { this->erase(); }

	virtual void push(const T& theElement) override;
	virtual void erase() override;
protected:
	virtual void initialize(T* theElements, int theSize) override;
	virtual void meld(BinaryTreeNode<std::pair<int, T>>*& x, BinaryTreeNode<std::pair<int, T>>*& y) override;
	static BinaryTreeNode<std::pair<int, T>>* minElement;

	static void disposeNoMinElement(BinaryTreeNode<std::pair<int, T>>* t) { if(t != minElement) delete t; }
};

template<class T>
BinaryTreeNode<std::pair<int, T>>* HbltWithMinElement<T>::minElement = new BinaryTreeNode<std::pair<int, T>>(pair<int, T>(0, -INT_MAX));

template<class T>
void HbltWithMinElement<T>::push(const T& theElement)
{
	BinaryTreeNode<std::pair<int, T>>* q = new BinaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElement), minElement, minElement);

	meld(this->root, q);
	++this->treeSize;
}

template<class T>
void HbltWithMinElement<T>::erase() {
	this->postOrder(disposeNoMinElement);
	this->root = nullptr; 
	this->treeSize = 0; 
}

template<class T>
void HbltWithMinElement<T>::initialize(T* theElements, int theSize)
{
	//

	arrayQueue<BinaryTreeNode<std::pair<int, T>>*> q(theSize);
	this->erase();

	for (int i = 1; i <= theSize; ++i) {
		q.push(new BinaryTreeNode<std::pair<int, T>>(pair<int, T>(1, theElements[i]), minElement, minElement));
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
void HbltWithMinElement<T>::meld(BinaryTreeNode<std::pair<int, T>>*& x, BinaryTreeNode<std::pair<int, T>>*& y) {
	if (x == minElement && y == minElement)
		return;

	using std::swap;
	if (this->maxHblt) {
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

	if (x->leftChild->element.first < x->rightChild->element.first) {
		swap(x->leftChild, x->rightChild);
	}
	x->element.first = x->rightChild->element.first + 1;
}

#endif 