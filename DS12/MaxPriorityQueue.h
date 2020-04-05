#pragma once
#ifndef _MAXPRIORITYQUEUE_H
#define _MAXPRIORITYQUEUE_H
//#include "PriorityElement.h"
template<class T>
class MaxPriorityQueue {
public:
	virtual ~MaxPriorityQueue() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual const T& top() = 0;
	virtual void pop() = 0;
	//virtual void push(const PriorityElement<T>& theElement) = 0;
	virtual void push(const T& theElement) = 0;
};

#endif