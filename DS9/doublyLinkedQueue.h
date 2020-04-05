#ifndef _DOUBLYLINKEDDEQUE_H
#define _DOUBLYLINKEDDEQUE_H

#include "deque_adt.h"
#include <iostream>
#include <exception>
#include <algorithm>
#include "../DS6/doublenode.h"
//Exercise 16
template<class T>
class doublyLinkedDeque : virtual public deque_adt<T> {
public:
	doublyLinkedDeque() :queueSize(0), queueFront(nullptr), queueBack(nullptr) {}

	virtual ~doublyLinkedDeque() { clear(); }
	virtual bool empty() const override { return queueSize == 0; }
	virtual int size() const override { return queueSize; }
	virtual T& front() override { if (queueFront) return queueFront->element; }
	virtual T& back() override { if (queueBack) return queueBack->element; }
	virtual void pop_front() override;
	virtual void push_back(const T& theElement) override;
	virtual void pop_back() override;
	virtual void push_front(const T& theElement) override;

protected:
	void clear();
	int queueSize;
	DoubleNode<T>* queueFront;
	DoubleNode<T>* queueBack;

};

template<class T>
void doublyLinkedDeque<T>::clear() {
	while (queueFront) {
		DoubleNode<T>* right = queueFront->right;
		delete queueFront;
		queueFront = right;
	}
	queueSize = 0;
	queueFront = nullptr;
	queueBack = nullptr;
}

template<class T>
void doublyLinkedDeque<T>::pop_front() {
	if (!queueFront) {
		throw std::underflow_error("empty queue");
	}

	DoubleNode<T>* right = queueFront->right;
	delete queueFront;
	queueFront = right;
	--queueSize;

	if (queueSize == 0)
		queueBack = nullptr;
	else
		right->left = nullptr;
}

template<class T>
void doublyLinkedDeque<T>::push_back(const T& theElement) {
	DoubleNode<T>* newNode = new DoubleNode<T>();
	newNode->element = theElement;
	newNode->right = nullptr;

	if (!queueFront) {
		queueFront = newNode;
		newNode->left = nullptr;
	}
	else {
		queueBack->right = newNode;
		newNode->left = queueBack;
	}
	queueBack = newNode;
	++queueSize;
}

template<class T>
void doublyLinkedDeque<T>::pop_back() {
	if (!queueBack) {
		throw std::underflow_error("empty queue");
	}

	DoubleNode<T>* left = queueBack->left;
	delete queueBack;
	queueBack = left;
	--queueSize;

	if (queueSize == 0)
		queueFront = nullptr;
	else
		left->right = nullptr;
}

template<class T>
void doublyLinkedDeque<T>::push_front(const T& theElement) {
	DoubleNode<T>* newNode = new DoubleNode<T>();
	newNode->element = theElement;
	newNode->left = nullptr;

	if (!queueBack) {
		queueBack = newNode;
		newNode->right = nullptr;
	}
	else {
		queueFront->left = newNode;
		newNode->right = queueFront;
	}
	queueFront = newNode;
	++queueSize;
}
#endif