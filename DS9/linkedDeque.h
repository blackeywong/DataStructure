#ifndef _LINKEDDEQUE_H
#define _LINKEDDEQUE_H

#include "deque_adt.h"
#include <iostream>
#include <exception>
#include <algorithm>
#include "../DS6/chainnode.h"
//Exercise 16
template<class T>
class linkedDeque : virtual public deque_adt<T> {
public:
	linkedDeque() :queueSize(0), queueFront(nullptr), queueBack(nullptr) {}

	virtual ~linkedDeque() { clear(); }
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
void linkedDeque<T>::clear() {
	while (queueFront) {
		ChainNode<T>* next = queueFront->next;
		delete queueFront;
		queueFront = next;
	}
	queueSize = 0;
	queueFront = nullptr;
	queueBack = nullptr;
}

template<class T>
void linkedDeque<T>::pop_front() {
	if (!queueFront) {
		throw std::underflow_error("empty queue");
	}

	ChainNode<T>* next = queueFront->next;
	delete queueFront;
	queueFront = next;
	--queueSize;

	if (queueSize == 0)
		queueBack = nullptr;
}

template<class T>
void linkedDeque<T>::push_back(const T& theElement) {
	ChainNode<T>* newNode = new ChainNode<T>();
	newNode->element = theElement;
	newNode->next = nullptr;

	if (!queueFront) {
		queueFront = newNode;
	}
	else {
		queueBack->next = newNode;
	}
	queueBack = newNode;
	++queueSize;
}

template<class T>
void linkedDeque<T>::pop_back() {
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
	cur->next = nullptr;
	--queueSize;
}

template<class T>
void linkedDeque<T>::push_front(const T& theElement) {
	ChainNode<T>* newNode = new ChainNode<T>();
	newNode->element = theElement;

	if (!queueFront) {
		queueBack = newNode;
		newNode->next = nullptr;
	}
	else {
		newNode->next = queueFront;
	}
	queueFront = newNode;
	++queueSize;
}
#endif