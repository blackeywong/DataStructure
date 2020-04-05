#pragma once
#ifndef _SLOWARRAYQUEUE_H
#define _SLOWARRAYQUEUE_H

#include "queue_adt.h"
#include <iostream>
#include <exception>
#include <algorithm>
//Exercise 6
template<class T>
class slowArrayQueue : virtual public queue_adt<T> {
public:
	slowArrayQueue(int initialCapacity = 10);

	virtual ~slowArrayQueue() { delete[] queue; }
	virtual bool empty() const override { return queueFront > queueBack; }
	virtual int size() const override { return queueBack - queueFront + 1; }
	virtual T& front() override { return queue[queueFront]; }
	virtual T& back() override { return queue[queueBack]; }
	virtual void pop() override;
	virtual void push(const T& theElement) override;
protected:
	void copyQueue(T* old, T* queue);

	T* queue;
	int arrayLength;
	int queueFront, queueBack;
};

template<class T>
slowArrayQueue<T>::slowArrayQueue<T>(int initialCapacity) {
	if (initialCapacity <= 0)
		throw std::bad_array_new_length();

	queue = new T[initialCapacity];
	arrayLength = initialCapacity;
	queueFront = 0;
	queueBack = -1;
}

template<class T>
void slowArrayQueue<T>::copyQueue(T* old, T* queue) {
	int sz = size();
	if (sz != 0) {
		std::copy(old + queueFront, old + queueBack + 1, queue);
	}
	queueFront = 0;
	queueBack = sz-1;
}

template<class T>
void slowArrayQueue<T>::pop() {
	queueFront += 1;
	queue[queueFront].~T();

	if (size() < arrayLength / 4) {
		T* old = queue;
		queue = new T[arrayLength / 2];
		copyQueue(old, queue);
		arrayLength /= 2;
	}
}

template<class T>
void slowArrayQueue<T>::push(const T& theElement) {
	if (size() == arrayLength) {
		T* old = queue;
		queue = new T[arrayLength * 2];
		copyQueue(old, queue);
		arrayLength *= 2;
	}
	else if(size() < arrayLength && queueBack == arrayLength - 1){
		std::copy(queue + queueFront, queue + arrayLength, queue);
		queueBack = size() - 1;
		queueFront = 0;
	}

	queueBack += 1;
	queue[queueBack] = theElement;
}

#endif