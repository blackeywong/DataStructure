#pragma once
#ifndef _QUEUE_ADT_H
#define _QUEUE_ADT_H

template<class T>
class queue_adt {
public:
	virtual ~queue_adt() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& front() = 0;
	virtual T& back() = 0;
	virtual void pop() = 0;
	virtual void push(const T& theElement) = 0;
};

#endif