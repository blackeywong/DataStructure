#pragma once
#ifndef _RSEBT_H
#define _RSEBT_H
//Right-Skewed Extended Binary Tree, Exercise 40.3
#include "../DS11/LinkedBinaryTree.h"
template<class T>
class Rsebt : public LinkedBinaryTree<T> {
public:
	Rsebt(T weight[], int n) { initialize(weight, n); }
	virtual ~Rsebt() {}
protected:
	void initialize(T weight[], int n);
};

template<class T>
void Rsebt<T>::initialize(T weight[], int n)
{
	this->root = new BinaryTreeNode<T>;
	BinaryTreeNode<T>* curNode = this->root;
	for (int i = n - 1; i >= 1; --i) {
		curNode->leftChild = new BinaryTreeNode<T>(weight[i]);
		curNode->rightChild = new BinaryTreeNode<T>;
		if (i == 1) {
			curNode->rightChild->element = weight[0];
		}
		curNode = curNode->rightChild;
	}
	this->treeSize = n;
}

#endif