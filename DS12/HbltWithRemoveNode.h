#pragma once
#ifndef _HBLTWITHREMOVENODE_H
#define _HBLTWITHREMOVENODE_H

#include "Hblt.h"
//Exercise 23
template<class T>
class HbltWithRemoveNode : public Hblt<T> {
public:
	explicit HbltWithRemoveNode(T* theElements, int theSize, bool theMaxHblt = true) { this->maxHblt = theMaxHblt; this->initialize(theElements, theSize); }
	virtual ~HbltWithRemoveNode() { this->erase(); }

	BinaryTreeNode<std::pair<int, T>>* pushAndReturnNode(const T& theElement);
	T removeElementInNode(BinaryTreeNode<std::pair<int, T>>* theNode);
protected:
	virtual void meld(BinaryTreeNode<std::pair<int, T>>*& x, BinaryTreeNode<std::pair<int, T>>*& y) override;

	BinaryTreeNode<std::pair<int, T>>* parent;
};

template<class T>
void HbltWithRemoveNode<T>::meld(BinaryTreeNode<std::pair<int, T>>*& x, BinaryTreeNode<std::pair<int, T>>*& y) {
	if (x == nullptr || y == nullptr)
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

	if (x->leftChild == nullptr) {
		x->leftChild = y;
		if (x->parent == nullptr && y->parent != nullptr) {
			x->parent = y->parent;
		}
		y->parent = x;
	}
	else if (x->rightChild == nullptr) {
		x->rightChild = y;
		if (x->parent == nullptr && y->parent != nullptr) {
			x->parent = y->parent;
		}
		y->parent = x;
		if (x->leftChild->element.first < x->rightChild->element.first) {
			swap(x->leftChild, x->rightChild);
		}
		x->element.first = x->rightChild->element.first + 1;
	}
	else {
		meld(x->rightChild, y);
		if (x->leftChild->element.first < x->rightChild->element.first) {
			swap(x->leftChild, x->rightChild);
		}
		x->element.first = x->rightChild->element.first + 1;
	}
}

template<class T>
BinaryTreeNode<std::pair<int, T>>* HbltWithRemoveNode<T>::pushAndReturnNode(const T& theElement)
{
	BinaryTreeNode<std::pair<int, T>>* newNode = new BinaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1,theElement));
	auto result = newNode;
	meld(this->root, newNode);
	return result;
}

template<class T>
T HbltWithRemoveNode<T>::removeElementInNode(BinaryTreeNode<std::pair<int, T>>* theNode)
{
	T result = theNode->element.second;
	meld(theNode->leftChild, theNode->rightChild);

	if (theNode == theNode->parent->leftChild) {
		theNode->parent->leftChild = theNode->leftChild;
	}
	else {
		theNode->parent->rightChild = theNode->leftChild;
		theNode->parent->element.first = theNode->leftChild->element.first + 1;
	}
	if (theNode->leftChild) {
		theNode->leftChild->parent = theNode->parent;
	}
	delete theNode;
	return result;
}

#endif
