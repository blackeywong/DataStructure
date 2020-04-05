#ifndef _CIRCULARDEQUE_H
#define _CIRCULARDEQUE_H

#include "deque_adt.h"
#include <iostream>
#include <exception>
#include <algorithm>
#include "../DS6/chainnode.h"
//Exercise 16
template<class T>
class circularDeque : virtual public deque_adt<T> {
public:
	circularDeque() :queueSize(0), queueFront(nullptr), queueBack(nullptr) {}

	virtual ~circularDeque() { clear(); }
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
	ChainNode<T>* queueFront;
	ChainNode<T>* queueBack;

};

template<class T>
void circularDeque<T>::clear() {
	for (int i = 0; i < queueSize;i++) {
		ChainNode<T>* next = queueFront->next;
		delete queueFront;
		queueFront = next;
	}
	queueSize = 0;
	queueFront = nullptr;
	queueBack = nullptr;
}

template<class T>
void circularDeque<T>::pop_front() {
	if (!queueFront) {
		throw std::underflow_error("empty queue");
	}

	ChainNode<T>* next = queueFront->next;
	delete queueFront;
	--queueSize;

	if (queueSize == 0) {
		queueFront = queueBack = nullptr;
	}
	else {
		queueFront = next;
		queueBack->next = queueFront;
	}
}

template<class T>
void circularDeque<T>::push_back(const T& theElement) {
	ChainNode<T>* newNode = new ChainNode<T>();
	newNode->element = theElement;

	if (!queueFront) {
		queueFront = newNode;
		newNode->next = newNode;
	}
	else {
		queueBack->next = newNode;
		newNode->next = queueFront;
	}
	queueBack = newNode;
	++queueSize;
}

template<class T>
void circularDeque<T>::pop_back() {
	if (!queueBack) {
		throw std::underflow_error("empty queue");
	}

	if (queueSize == 1) {
		clear();
		return;
	}

	ChainNode<T>* cur = queueFront;
	while (cur->next != queueBack)
		cur = cur->next;

	delete queueBack;
	queueBack = cur;
	cur->next = queueFront;
	--queueSize;
}

template<class T>
void circularDeque<T>::push_front(const T& theElement) {
	ChainNode<T>* newNode = new ChainNode<T>();
	newNode->element = theElement;

	if (!queueFront) {
		queueBack = newNode;
	}
	else {
		newNode->next = queueFront;
	}
	queueFront = newNode;
	queueBack->next = newNode;
	++queueSize;
}
#endif