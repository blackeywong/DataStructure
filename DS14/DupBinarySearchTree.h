#ifndef _DUPBINARYSEARCHTREE_H
#define _DUPBINARYSEARCHTREE_H

#include<ctime>
#include<random>

#include "BinarySearchTree.h"

template<class K, class E>
class DupBinarySearchTree : public BinarySearchTree<K, E> {
public:
	DupBinarySearchTree() :BinarySearchTree<K, E>() { e = new std::default_random_engine(static_cast<unsigned int>(time(nullptr))); u = new std::uniform_int_distribution<int>(1, 100); }
	virtual ~DupBinarySearchTree() { delete e; delete u; }
	virtual void insert(const std::pair<K, E>& thePair) override;
protected:
	std::default_random_engine* e;
	std::uniform_int_distribution<int>* u;
};

template<class K, class E>
void DupBinarySearchTree<K, E>::insert(const std::pair<K, E>& thePair)
{
	BinaryTreeNode<std::pair<K, E>>* p = this->root;
	BinaryTreeNode<std::pair<K, E>>* pp = nullptr;
	int r;

	while (p != nullptr) {
		pp = p;
		if (thePair.first < p->element.first) {
			p = p->leftChild;
		}
		else if (thePair.first > p->element.first) {
			p = p->rightChild;
		}
		else {
			r = (*u)(*e);
			if (r % 2 == 1) {
				p = p->leftChild;
			}
			else {
				p = p->rightChild;
			}
		}
	}

	BinaryTreeNode<std::pair<K, E>>* newNode = new BinaryTreeNode<std::pair<K, E>>(thePair);
	if (this->root != nullptr) {
		if (thePair.first < pp->element.first) {
			pp->leftChild = newNode;
		}
		else if (thePair.first > pp->element.first) {
			pp->rightChild = newNode;
		}
		else {//Exercise 17
			if (r % 2 == 1) {
				pp->leftChild = newNode;
			}
			else {
				pp->rightChild = newNode;
			}
		}
	}
	else {
		this->root = newNode;
	}
	++this->treeSize;
}

#endif
