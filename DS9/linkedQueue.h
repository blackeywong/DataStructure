#pragma once
#ifndef _LINKEDQUEUE_H
#define _LINKEDQUEUE_H

#include "queue_adt.h"
#include <iostream>
#include <exception>
#include <algorithm>
#include "../DS6/chainnode.h"

template<class T>
class linkedQueue : virtual public queue_adt<T> {
public:
	linkedQueue():queueSize(0),queueFront(nullptr), queueBack(nullptr) {}

	virtual ~linkedQueue() { clear(); }
	virtual bool empty() const override { return queueSize == 0; }
	virtual int size() const override { return queueSize; }
	virtual T& front() override { return (*queueFront).element; }
	virtual T& back() override { return (*queueBack).element; }
	virtual void pop() override;
	virtual void push(const T& theElement) override;
protected:
	void clear();
	int queueSize;
	ChainNode<T>* queueFront;
	ChainNode<T>* queueBack;

};

template<class T>
void linkedQueue<T>::clear() {
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
void linkedQueue<T>::pop() {
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
void linkedQueue<T>::push(const T& theElement) {
	ChainNode<T>* newNode = new ChainNode<T>();
	newNode->element = theElement;
	newNode->next = nullptr;

	if (!queueFront)
		queueFront = newNode;
	else
		queueBack->next = newNode;

	queueBack = newNode;
	++queueSize;
}

#endif