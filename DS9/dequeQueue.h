#ifndef _DEQUEQUEUE_H
#define _DEQUEQUEUE_H

#include "queue_adt.h"
#include "arrayDeque.h"

template<class T>
class dequeQueue : virtual public queue_adt<T>, virtual private arrayDeque<T> {
public:
	dequeQueue(int initialCapacity = 10) :arrayDeque<T>(initialCapacity) {}

	virtual ~dequeQueue() {}
	virtual bool empty() const override { return arrayDeque<T>::empty(); }
	virtual int size() const override { return arrayDeque<T>::size(); }
	virtual T& front() override { return arrayDeque<T>::front(); }
	virtual T& back() override { return arrayDeque<T>::back(); }
	virtual void pop() override { arrayDeque<T>::pop_front(); }
	virtual void push(const T& theElement) override { arrayDeque<T>::push_back(theElement); }
};

#endif