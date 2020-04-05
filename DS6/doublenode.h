#pragma once
#ifndef _DOUBLENODE_H
#define _DOUBLENODE_H
//数据结构算法与应用-C++语言描述 第六章
template<class T>
struct DoubleNode {
	T element;
	DoubleNode<T>* left, *right;

	DoubleNode() {}
	DoubleNode(const T& element){
		this->element = element;
	}
	DoubleNode(const T& element, DoubleNode<T>* left, DoubleNode<T>* right){
		this->element = element;
		this->left = left;
		this->right = right;
	}
};

#endif
