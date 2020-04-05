#ifndef _ARRAYQUEUE2_H
#define _ARRAYQUEUE2_H

#include "queue_adt.h"
#include <iostream>
#include <exception>
#include <algorithm>
//Exercise 7
template<class T>
class arrayQueue2 : virtual public queue_adt<T> {
public:
	arrayQueue2(int initialCapacity = 10);

	virtual ~arrayQueue2() { delete[] queue; }
	virtual bool empty() const override { return queueSize == 0; }
	virtual int size() const override { return queueSize; }
	virtual T& front() override { return queue[queueFront]; }
	virtual T& back() override { return queue[(queueFront + queueSize - 1) % arrayLength]; }
	virtual void pop() override;
	virtual void push(const T& theElement) override;
protected:
	void copyQueue(T* old, T* queue);

	T* queue;
	int arrayLength;
	int queueFront, queueSize;

};

template<class T>
arrayQueue2<T>::arrayQueue2<T>(int initialCapacity) {
	if (initialCapacity <= 0)
		throw std::bad_array_new_length();

	queue = new T[initialCapacity];
	arrayLength = initialCapacity;
	queueFront = queueSize = 0;
}

template<class T>
void arrayQueue2<T>::copyQueue(T* old, T* queue) {
	if (queueSize != 0) {
		if (queueFront + queueSize <= arrayLength) {
			std::copy(old + queueFront, old + queueFront + queueSize + 1, queue);
		}
		else {
			std::copy(old + queueFront, old + arrayLength, queue);
			std::copy(old, old + queueFront + queueSize - arrayLength, queue + arrayLength - queueFront);
		}
	}
	queueFront = 0;
}

template<class T>
void arrayQueue2<T>::pop() {
	queue[queueFront].~T();
	queueFront = (queueFront + 1) % arrayLength;
	--queueSize;

	if (queueSize < arrayLength / 4) {
		T* old = queue;
		queue = new T[arrayLength / 2];
		copyQueue(old, queue);
		arrayLength /= 2;
	}
}

template<class T>
void arrayQueue2<T>::push(const T& theElement) {
	if (queueSize >= arrayLength) {
		T* old = queue;
		queue = new T[arrayLength * 2];
		copyQueue(old, queue);
		arrayLength *= 2;
	}

	queue[(queueFront + queueSize) % arrayLength] = theElement;
	++queueSize;
}

#endif