#pragma once
#ifndef _BINARYTREENODE_H
#define _BINARYTREENODE_H
#include <iostream>
template<class T>
struct BinaryTreeNode {
	T element;
	BinaryTreeNode<T>* leftChild;
	BinaryTreeNode<T>* rightChild;
	BinaryTreeNode<T>* parent;
	int seq_num = 0;

	BinaryTreeNode():leftChild(nullptr), rightChild(nullptr), parent(nullptr){}
	explicit BinaryTreeNode(const T& t) :element(t), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}
	BinaryTreeNode(const T& t, BinaryTreeNode<T>* theLeftChild, BinaryTreeNode<T>* theRightChild)
		:element(t), leftChild(theLeftChild), rightChild(theRightChild), parent(nullptr) {}

	void output(std::ostream& out) { out << static_cast<int>(element); }

	//T operator()() { return element; }
};

template<class T>
std::ostream& operator<<(std::ostream& out, BinaryTreeNode<T>& node) {
	node.output(out);
	return out;
}

#endif 

