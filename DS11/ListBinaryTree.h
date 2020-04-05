#pragma once
#ifndef _LISTBINARYTREE_H
#define _LISTBINARYTREE_H

#include <utility>
#include <iostream>
#include <algorithm>

#include "TraverseOrder.h"

template<class T>
class ListBinaryTree {
public:
	explicit ListBinaryTree(int theHeight);
	~ListBinaryTree() { delete[]list; list = nullptr; }
	explicit ListBinaryTree(const ListBinaryTree<T>& right);//Exercise 24

	std::istream& input(std::istream& in);
	std::ostream& output(std::ostream& out, TRAVERSE_ORDER order = INFIX) const;

	void preOrder(int node, std::ostream& out = std::cout) const;//Exercise 20
	void inOrder(int node, std::ostream& out = std::cout) const;//Exercise 21
	void postOrder(int node, std::ostream& out = std::cout) const;//Exercise 22
	void levelOrder(std::ostream& out = std::cout) const;//Exercise 23
	void visit(int node, std::ostream& out = std::cout) const {if(list[node].first) out << list[node].second << " "; }
private:
	std::pair<bool, T>* list;
	int height;
	int last;
};

template<class T>
ListBinaryTree<T>::ListBinaryTree(int theHeight) :height(theHeight) {
	int capacity = (int)std::pow(2, height);
	list = new std::pair<bool, T>[capacity];
	last = 0;
	for (int i = 0; i < capacity; ++i) {
		list[i].first = false;
	}
}

template<class T>
ListBinaryTree<T>::ListBinaryTree(const ListBinaryTree<T>& right) {
	delete list;
	height = right.height;
	last = right.last;
	int capacity = (int)std::pow(2, height);
	list = new std::pair<bool, T>[capacity];
	std::copy(right.list, right.list + capacity, list);
}

template<class T>
std::istream& ListBinaryTree<T>::input(std::istream& in) {
	int num;
	T t;
	int end = (int)std::pow(2, height);
	while (in >> num >> t) {
		list[num].first = true;
		list[num].second = t;
		last = num;
	}
	return in;
}

template<class T>
std::ostream& ListBinaryTree<T>::output(std::ostream& out, TRAVERSE_ORDER order) const{
	switch (order) {
	case PREFIX: preOrder(1, out); break;
	case INFIX: inOrder(1, out); break;
	case POSTFIX: postOrder(1, out); break;
	case LEVEL: levelOrder(out); break;
	}
	return out;
}

template<class T>
void ListBinaryTree<T>::preOrder(int node, std::ostream& out) const {
	if (node <= last && list[node].first == true) {
		visit(node, out);
		preOrder(node * 2, out);
		preOrder(node * 2 + 1, out);
	}
}

template<class T>
void ListBinaryTree<T>::inOrder(int node, std::ostream& out) const {
	if (node <= last && list[node].first == true) {
		inOrder(node * 2, out);
		visit(node, out);
		inOrder(node * 2 + 1, out);
	}
}

template<class T>
void ListBinaryTree<T>::postOrder(int node, std::ostream& out) const {
	if (node <= last && list[node].first == true) {
		postOrder(node * 2, out);
		postOrder(node * 2 + 1, out);
		visit(node, out);
	}
}

template<class T>
void ListBinaryTree<T>::levelOrder(std::ostream& out) const {
	for (int i = 1; i <= last; ++i) {
		visit(i, out);
	}
}

#endif
