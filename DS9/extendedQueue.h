#ifndef _EXTENDEDQUEUE_H
#define _EXTENDEDQUEUE_H

#include "extendedQueue_adt.h"
#include "arrayQueue.h"
#include <iostream>
#include <exception>
#include <algorithm>

template<class T>
class extendedQueue : virtual public arrayQueue<T>, virtual public extendedQueue_adt<T> {
public:
	extendedQueue(int initialCapacity = 10) :arrayQueue<T>() {}

	virtual bool empty() const override { return arrayQueue<T>::empty(); }
	virtual int size() const override { return arrayQueue<T>::size(); }
	virtual T& front() override { return arrayQueue<T>::front(); }
	virtual T& back() override { return arrayQueue<T>::back(); }
	virtual void pop() override { arrayQueue<T>::pop(); }
	virtual void push(const T& theElement) override { arrayQueue<T>::push(theElement); }
	//Exercise 5.2
	virtual std::istream& input(std::istream& in) override;
	virtual std::ostream& output(std::ostream& out) override;
	virtual void split(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) override;
	virtual void merge(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) override;

};

template<class T>
std::istream& operator>>(std::istream& in, extendedQueue<T>& eq) { return eq.input(in); }

template<class T>
std::ostream& operator<<(std::ostream& out, extendedQueue<T>& eq) { return eq.output(out); }

template<class T>
std::istream& extendedQueue<T>::input(std::istream& in) {
	T t;
	while (in >> t) {
		push(t);
	}
	return in;
}

template<class T>
std::ostream& extendedQueue<T>::output(std::ostream& out) {
	for (int i = this->queueFront + 1; i < this->queueBack + 1; ++i) {
		out << this->queue[i] << " ";
	}
	return out;
}

template<class T>
void extendedQueue<T>::split(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) {
	while (size() > 0) {
		q1.push(front());
		pop();
		if (size() == 0)
			break;

		q2.push(front());
		pop();
	}
}

template<class T>
void extendedQueue<T>::merge(extendedQueue_adt<T>& q1, extendedQueue_adt<T>& q2) {
	while (q1.size() > 0 && q2.size() > 0) {
		push(q1.front());
		q1.pop();
		push(q2.front());
		q2.pop();
	}
	while (q1.size() > 0) {
		push(q1.front());
		q1.pop();
	}
	while (q2.size() > 0) {
		push(q2.front());
		q2.pop();
	}
}

#endif