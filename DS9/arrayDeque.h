#ifndef _ARRAYDEQUE_H
#define _ARRAYDEQUE_H

#include "deque_adt.h"
#include <iostream>
#include <exception>
#include <algorithm>
//Exercise 9
template<class T>
class arrayDeque : virtual public deque_adt<T> {
public:
	arrayDeque(int initialCapacity = 10);

	virtual ~arrayDeque() { delete[] queue; }
	virtual bool empty() const override { return queueFront == queueBack; }
	virtual int size() const override { return (queueBack + arrayLength - queueFront) % arrayLength; }
	virtual T& front() override { return queue[(queueFront + 1) % arrayLength]; }
	virtual T& back() override { return queue[queueBack]; }
	virtual void pop_front() override;
	virtual void pop_back() override;
	virtual void push_front(const T& theElement) override;
	virtual void push_back(const T& theElement) override;

	 std::ostream& output(std::ostream& out);

protected:
	void copyQueue(T* old, T* queue);

	T* queue;
	int arrayLength;
	int queueFront, queueBack;

};

template<class T>
std::ostream& operator<<(std::ostream& out, arrayDeque<T>& ad) { return ad.output(out); }

template<class T>
std::ostream& arrayDeque<T>::output(std::ostream& out) {
	if (queueFront <= queueBack) {
		for (int i = queueFront + 1; i < queueBack + 1; ++i) {
			out << queue[i] << " ";
		}
	}
	else {
		for (int i = queueFront + 1; i < arrayLength; ++i) {
			out << queue[i] << " ";
		}
		for (int i = 0; i < queueBack + 1; ++i) {
			out << queue[i] << " ";
		}
	}
	return out;
}

template<class T>
arrayDeque<T>::arrayDeque<T>(int initialCapacity) {
	if (initialCapacity <= 0)
		throw std::bad_array_new_length();

	queue = new T[initialCapacity];
	arrayLength = initialCapacity;
	queueFront = queueBack = 0;
}

template<class T>
void arrayDeque<T>::copyQueue(T* old, T* queue) {
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
void arrayDeque<T>::pop_front() {
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
void arrayDeque<T>::pop_back() {
	queue[queueBack].~T();
	queueBack = (queueBack -1 +arrayLength) % arrayLength;

	if (size() < arrayLength / 4) {
		T* old = queue;
		queue = new T[arrayLength / 2];
		copyQueue(old, queue);
		arrayLength /= 2;
	}
}

template<class T>
void arrayDeque<T>::push_front(const T& theElement) {
	if (size() >= arrayLength - 1) {
		T* old = queue;
		queue = new T[arrayLength * 2];
		copyQueue(old, queue);
		arrayLength *= 2;
	}
	queue[queueFront] = theElement;
	queueFront = (queueFront - 1 + arrayLength) % arrayLength;
}

template<class T>
void arrayDeque<T>::push_back(const T& theElement) {
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