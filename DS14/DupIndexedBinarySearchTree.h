#ifndef _DUPINDEXEDBINARYSEARCHTREE_H
#define _DUPINDEXEDBINARYSEARCHTREE_H

#include<ctime>
#include<random>

#include "IndexedBinarySearchTree.h"

template<class K, class E>
class DupIndexedBinarySearchTree : public IndexedBinarySearchTree<K, E> {
public:
	DupIndexedBinarySearchTree() :IndexedBinarySearchTree<K, E>() { e = new std::default_random_engine(static_cast<unsigned int>(time(nullptr))); u = new std::uniform_int_distribution<int>(1, 100); }
	virtual ~DupIndexedBinarySearchTree() { delete e; delete u; }
	virtual void insert(const std::pair<K, E>& thePair) override;
	virtual void erase(const K& theKey) override;
protected:
	std::default_random_engine* e;
	std::uniform_int_distribution<int>* u;
};

template<class K, class E>
void DupIndexedBinarySearchTree<K, E>::insert(const std::pair<K, E>& thePair)
{
	BinaryTreeNode<IndexedBSTreeNode<K, E>>* p = this->root;
	BinaryTreeNode<IndexedBSTreeNode<K, E>>* pp = nullptr;
	int r;

	while (p != nullptr) {
		pp = p;
		if (thePair.first < p->element.keyValue.first) {
			++p->element.leftSize;
			p = p->leftChild;
		}
		else if (thePair.first > p->element.keyValue.first) {
			p = p->rightChild;
		}
		else {
			r = (*u)(*e);
			if (r % 2 == 1) {
				++p->element.leftSize;
				p = p->leftChild;
			}
			else {
				p = p->rightChild;
			}
		}
	}

	BinaryTreeNode<IndexedBSTreeNode<K, E>>* newNode = new BinaryTreeNode<IndexedBSTreeNode<K, E>>(thePair);
	if (this->root != nullptr) {
		if (thePair.first < pp->element.keyValue.first) {
			pp->leftChild = newNode;
		}
		else if (thePair.first > pp->element.keyValue.first) {
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

template<class K, class E>
void DupIndexedBinarySearchTree<K, E>::erase(const K& theKey)
{
	if (IndexedBinarySearchTree<K, E>::find(theKey) == nullptr) return;

	BinaryTreeNode<IndexedBSTreeNode<K, E>>* p = this->root;
	BinaryTreeNode<IndexedBSTreeNode<K, E>>* pp = nullptr;

	//find the node of theKey
	while (p != nullptr && p->element.keyValue.first != theKey) {
		pp = p;
		if (theKey < p->element.keyValue.first) {
			--p->element.leftSize;
			p = p->leftChild;
		}
		else if (theKey > p->element.keyValue.first) {
			p = p->rightChild;
		}
		else {
			return;
		}
	}
	if (p == nullptr)
		return;//cannot find theKey

	//when p has two childs
	if (p->leftChild != nullptr && p->rightChild != nullptr) {
		//find the max in leftChild of p
		BinaryTreeNode<IndexedBSTreeNode<K, E>>* s = p->leftChild;
		BinaryTreeNode<IndexedBSTreeNode<K, E>>* ps = p;

		while (s->rightChild != nullptr) {
			ps = s;
			s = s->rightChild;
		}

		//move max from s to p
		BinaryTreeNode<IndexedBSTreeNode<K, E>>* q = new BinaryTreeNode<IndexedBSTreeNode<K, E>>(s->element, p->leftChild, p->rightChild);
		q->element.leftSize = p->element.leftSize;
		if (pp == nullptr) {
			this->root = q;
		}
		else if (p == pp->leftChild) {
			pp->leftChild = q;
		}
		else {
			pp->rightChild = q;
		}

		if (ps == p) {
			pp = q;
		}
		else {
			pp = ps;
		}
		delete p;
		p = s;
	}

	//p has one child at most
	BinaryTreeNode<IndexedBSTreeNode<K, E>>* c = nullptr;
	if (p->leftChild != nullptr) {
		c = p->leftChild;
	}
	else {
		c = p->rightChild;
	}
	if (p == this->root) {
		this->root = c;
	}
	else {
		if (p == pp->leftChild) {
			pp->leftChild = c;
		}
		else {
			pp->rightChild = c;
		}
		--this->treeSize;
		delete p;
	}

}

#endif
