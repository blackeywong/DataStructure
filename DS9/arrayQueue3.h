#ifndef _ARRAYQUEUE3_H
#define _ARRAYQUEUE3_H

#include "queue_adt.h"
#include <iostream>
#include <exception>
#include <algorithm>
//Exercise 8
template<class T>
class arrayQueue3 : virtual public queue_adt<T> {
public:
	arrayQueue3(int initialCapacity = 10);

	virtual ~arrayQueue3() { delete[] queue; }
	virtual bool empty() const override { return queueFront == queueBack && lastOp == POP; }
	virtual int size() const override;
	virtual T& front() override { return queue[(queueFront+1) % arrayLength]; }
	virtual T& back() override { return queue[queueBack]; }
	virtual void pop() override;
	virtual void push(const T& theElement) override;
protected:
	void copyQueue(T* old, T* queue);

	T* queue;
	int arrayLength;
	int queueFront, queueBack;
	enum { PUSH, POP } lastOp;

};

template<class T>
arrayQueue3<T>::arrayQueue3<T>(int initialCapacity) {
	if (initialCapacity <= 0)
		throw std::bad_array_new_length();

	queue = new T[initialCapacity];
	arrayLength = initialCapacity;
	queueFront = queueBack = -1;
	lastOp = POP;
}

template<class T>
int arrayQueue3<T>::size() const {
	//return queueFront != queueBack ? (queueBack + arrayLength - queueFront) % arrayLength : lastOp == PUSH ? arrayLength : 0;
	if (queueFront != queueBack)
		return (queueBack + arrayLength - queueFront) % arrayLength;
	else if (lastOp == PUSH)
		return arrayLength;
	else
		return 0;
}

template<class T>
void arrayQueue3<T>::copyQueue(T* old, T* queue) {
	int sz = size();
	if (sz != 0) {
		if (queueFront < queueBack) {
			std::copy(old + queueFront + 1, old + queueBack + 1, queue);
		}
		else {
			std::copy(old + queueFront + 1, old + arrayLength, queue);
			std::copy(old, old + queueBack + 1, queue + (arrayLength - 1 - queueFront));
		}
	}
	queueFront = -1;
	queueBack = sz - 1;
}

template<class T>
void arrayQueue3<T>::pop() {
	queueFront = (queueFront + 1) % arrayLength;
	queue[queueFront].~T();
	lastOp = POP;

	if (size() < arrayLength / 4) {
		T* old = queue;
		queue = new T[arrayLength / 2];
		copyQueue(old, queue);
		arrayLength /= 2;
	}
}

template<class T>
void arrayQueue3<T>::push(const T& theElement) {
	if (size() >= arrayLength) {
		T* old = queue;
		queue = new T[arrayLength * 2];
		copyQueue(old, queue);
		arrayLength *= 2;
	}

	queueBack = (queueBack + 1) % arrayLength;
	queue[queueBack] = theElement;
	lastOp = PUSH;
}

#endif