#ifndef _ARRAYQUEUE_H
#define _ARRAYQUEUE_H

#include "queue_adt.h"
#include <iostream>
#include <exception>
#include <algorithm>

template<class T>
class arrayQueue : virtual public queue_adt<T> {
public:
	arrayQueue(int initialCapacity = 10);

	virtual ~arrayQueue()  { delete[] queue; }
	virtual bool empty() const override { return queueFront == queueBack; }
	virtual int size() const override { return (queueBack + arrayLength - queueFront) % arrayLength; }
	virtual T& front() override { return queue[(queueFront+1) % arrayLength]; }
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
arrayQueue<T>::arrayQueue(int initialCapacity) {
	if (initialCapacity <= 0)
		throw std::bad_array_new_length();

	queue = new T[initialCapacity];
	arrayLength = initialCapacity;
	queueFront = queueBack = 0;
}

template<class T>
void arrayQueue<T>::copyQueue(T* old, T* queue) {
	int sz = size();
	if (sz != 0) {
		if (queueFront < queueBack) {
			std::copy(old + queueFront + 1, old + queueBack + 1, queue + 1);
		}
		else {
			std::copy(old + queueFront + 1, old + arrayLength, queue + 1);
			std::copy(old, old + queueBack + 1, queue + (arrayLength - 1 - queueFront) + 1);
		}
	}
	queueFront = 0;
	queueBack = sz;
}

template<class T>
void arrayQueue<T>::pop() {
	queueFront = (queueFront + 1) % arrayLength;
	queue[queueFront].~T();

	if (size() < arrayLength / 4) {
		T* old = queue;
		queue = new T[arrayLength / 2];
		copyQueue(old, queue);
		arrayLength /= 2;
	}
}

template<class T>
void arrayQueue<T>::push(const T& theElement) {
	if (size() >= arrayLength - 1) {
		T* old = queue;
		queue = new T[arrayLength * 2];
		copyQueue(old, queue);
		arrayLength *= 2;
	}

	queueBack = (queueBack + 1) % arrayLength;
	queue[queueBack] = theElement;
}

#endif