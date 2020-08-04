#ifndef _LINEARLISTASBINARYTREE_H
#define _LINEARLISTASBINARYTREE_H

#include<algorithm>
#include<ctime>
#include<random>
#include<iostream>

#include "BSTree.h"

template<class K, class E>
struct LinearListAsBinaryTreeNode {
	bool hasValue;
	std::pair<K, E> element;
	LinearListAsBinaryTreeNode() :hasValue(false) {}
	LinearListAsBinaryTreeNode(const std::pair<K, E>& p) :hasValue(true), element(p) {}
};

template<class K, class E>
class LinearListAsBinaryTree : public BSTree<K, E> {
	//using complete tree as store
public:
	LinearListAsBinaryTree() :list(nullptr), treeSize(0), capacity(1) {}
	virtual ~LinearListAsBinaryTree() { delete[] list; }
	virtual bool empty() const  override { return treeSize == 0; }
	virtual int size() const  override { return treeSize; }
	virtual std::pair<K, E>* find(const K& theKey) const override;
	virtual void erase(const K& theKey) override;
	virtual void insert(const std::pair<K, E>& thePair) override;

	virtual void ascend() override;

	std::istream& input(std::istream& in);

	std::ostream& output(std::ostream& out);
protected:
	void inOrder(int node, std::ostream& out) const;

	LinearListAsBinaryTreeNode<K, E>* list;
	int capacity;
	int treeSize;
};


template<class K, class E>
std::pair<K, E>* LinearListAsBinaryTree<K, E>::find(const K& theKey) const
{
	int i = 1;
	while (i <= treeSize && list[i].hasValue) {
		if (theKey < list[i].element.first) {
			i = i * 2;
		}
		else if (theKey > list[i].element.first) {
			i = i * 2 + 1;
		}
		else {
			return &list[i].element;
		}
	}
	return nullptr;
}

template<class K, class E>
void LinearListAsBinaryTree<K, E>::erase(const K& theKey)
{
	int i = 1;
	while (i < capacity && list[i].hasValue && list[i].element.first != theKey) {
		if (theKey < list[i].element.first) {
			i = i * 2;
		}
		else if (theKey > list[i].element.first) {
			i = i * 2 + 1;
		}
	}
	if (i >= capacity || !list[i].hasValue)
		return;//cannot find theKey

	while (i * 2 < capacity && list[i * 2].hasValue || i * 2 + 1 < capacity && list[i * 2 + 1].hasValue) {
		//when i has left child
		if (i * 2 < capacity && list[i * 2].hasValue) {
			//find the max in left tree
			int j = i * 2;
			while (j < capacity && list[j].hasValue) {
				j = j * 2 + 1;
			}
			j = (j - 1) / 2;
			//move max from j to i
			list[i].element = list[j].element;
			i = j;
		}
		else {
			//find the min in right tree
			int j = i * 2 + 1;
			while (j < capacity && list[j].hasValue) {
				j = j * 2;
			}
			j = j / 2;
			//move max from j to i
			list[i].element = list[j].element;
			i = j;
		}
	}
	list[i].hasValue = false;

	--this->treeSize;
}

template<class K, class E>
void LinearListAsBinaryTree<K, E>::insert(const std::pair<K, E>& thePair)
{
	int i = 1;
	while (i < capacity && list[i].hasValue) {
		if (thePair.first < list[i].element.first) {
			i = i * 2;
		}
		else if (thePair.first > list[i].element.first) {
			i = i * 2 + 1;
		}
		else {
			list[i].element.second = thePair.second;
			return;
		}
	}
	if (i >= capacity) {
		capacity *= 2;
		LinearListAsBinaryTreeNode<K, E>* oldlist = list;
		list = new LinearListAsBinaryTreeNode<K, E>[capacity];
		if (oldlist) {
			std::copy(oldlist + 1, oldlist + capacity / 2, list + 1);
		}
		delete[]oldlist;
	}
	list[i].hasValue = true;
	list[i].element = thePair;
	++this->treeSize;
}

template<class K, class E>
void LinearListAsBinaryTree<K, E>::ascend()
{
	output(std::cout);
}

template<class K, class E>
std::istream& LinearListAsBinaryTree<K, E>::input(std::istream& in) {
	int num;
	in >> num;

	for (int i = 0; i < num; ++i) {
		K k;
		E e;
		in >> k >> e;
		std::pair<K, E> p(k, e);
		insert(p);
	}
	return in;
}

template<class K, class E>
std::ostream& LinearListAsBinaryTree<K, E>::output(std::ostream& out)
{
	inOrder(1, out);
	out << std::endl;
	return out;
}

template<class K, class E>
void LinearListAsBinaryTree<K, E>::inOrder(int node, std::ostream& out) const {
	if (node < capacity && list[node].hasValue) {
		inOrder(node * 2, out);
		out << list[node].element.first << " ";
		inOrder(node * 2 + 1, out);
	}
}
#endif
