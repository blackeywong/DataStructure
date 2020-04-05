#pragma once
#ifndef _WBLT_H
#define _WBLT_H

#include <algorithm>
#include <xutility>
#include <iostream>

#include "Hblt.h"

template<class T>
class Wblt : public Hblt<T> {
public:
	Wblt() = default;
	//explicit Wblt(T* theElements, int theSize, bool theMaxHblt = true) : Hblt(theElements, theSize, theMaxHblt) {}
	Wblt(T* theElements, int theSize, bool theMaxHblt = true) { this->maxHblt = theMaxHblt;  this->initialize(theElements, theSize); }
	virtual ~Wblt() { this->erase(); }

protected:
	virtual void meld(BinaryTreeNode<std::pair<int, T>>*& x, BinaryTreeNode<std::pair<int, T>>*& y) override;
};

//recursive
//template<class T>
//void Wblt<T>::meld(BinaryTreeNode<std::pair<int, T>>*& x, BinaryTreeNode<std::pair<int, T>>*& y) {
//	if (x == nullptr || y == nullptr)
//		return;
//
//	using std::swap;
//	if (this->maxHblt) {
//		if (x->element.second < y->element.second) {
//			swap(x, y);
//		}
//	}
//	else {
//		if (x->element.second > y->element.second) {
//			swap(x, y);
//		}
//	}
//
//	x->element.first += y->element.first;
//	if (x->leftChild == nullptr) {
//		x->leftChild = y;
//		return;
//	}
//	else if (x->rightChild == nullptr) {
//		x->rightChild = y;
//		if (x->leftChild->element.first < x->rightChild->element.first) {
//			swap(x->leftChild, x->rightChild);
//		}
//		return;
//	}
//	else {
//		meld(x->rightChild, y);
//		if (x->leftChild->element.first < x->rightChild->element.first) {
//			swap(x->leftChild, x->rightChild);
//		}
//	}
//}


template<class T>
void Wblt<T>::meld(BinaryTreeNode<std::pair<int, T>>*& x, BinaryTreeNode<std::pair<int, T>>*& y) {
	auto result = x;

	BinaryTreeNode<std::pair<int, T>>** a = &x;
	BinaryTreeNode<std::pair<int, T>>** b = &y;
	bool getResult = false;
	while (*a != nullptr && *b != nullptr) {
		using std::swap;
		if (this->maxHblt) {
			if ((*a)->element.second < (*b)->element.second) {
				swap(*a, *b);
			}
		}
		else {
			if ((*a)->element.second > (*b)->element.second) {
				swap(*a, *b);
			}
		}

		if (!getResult) {
			result = *a;
			getResult = true;
		}
		(*a)->element.first += (*b)->element.first;
		if ((*a)->leftChild == nullptr) {
			(*a)->leftChild = *b;
			break;
		}
		else if ((*a)->rightChild == nullptr) {
			(*a)->rightChild = *b;
			if ((*a)->leftChild->element.first < (*a)->rightChild->element.first) {
				swap((*a)->leftChild, (*a)->rightChild);
			}
			break;
		}
		else {
			if ((*a)->leftChild->element.first < (*a)->rightChild->element.first + (*b)->element.first) {
				swap((*a)->leftChild, (*a)->rightChild);
				a = &((*a)->leftChild);
			}
			else {
				a = &((*a)->rightChild);
			}
		}
	}
	x = result;
}



#endif 