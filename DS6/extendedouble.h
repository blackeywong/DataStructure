#ifndef _EXTENDEDDOUBLE_H
#define _EXTENDEDDOUBLE_H
#include<iostream>
#include "double.h"
#include "doublenode.h"
//数据结构算法与应用-C++语言描述 第六章

template<class T>
class ExtendedDouble : public Double<T>
{
public:
	ExtendedDouble() :Double<T>() { }

	ExtendedDouble(const Double<T>& t) : Double<T>(t) {}

	void clear();
	void push_back(const T& theElement);

};

template<class T>
void ExtendedDouble<T>::clear() {
	while (this->firstNode) {
		DoubleNode<T>* right = this->firstNode->right;
		delete this->firstNode;
		this->firstNode = right;
	}
	this->listSize = 0;
	this->lastNode = nullptr;
}

template<class T>
void ExtendedDouble<T>::push_back(const T& theElement) {
	DoubleNode<T>* newNode = new DoubleNode<T>(theElement, nullptr, nullptr);
	if (this->firstNode == nullptr) {
		this->firstNode = this->lastNode = newNode;
	}
	else {
		this->lastNode->right = newNode;
		newNode->left = this->lastNode;
		this->lastNode = newNode;
	}
	this->listSize++;
}
#endif