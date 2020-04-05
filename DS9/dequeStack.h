#pragma once
#ifndef _DEQUESTACK_H
#define _DEQUESTACK_H
#include "../DS8/stack.h"
#include "arrayDeque.h"
//Exercise 10
template<class T>
class dequeStack :virtual public stack<T>, virtual private arrayDeque<T> {
public:
	dequeStack(int initialCapacity = 10) :arrayDeque<T>(initialCapacity) {}
	virtual ~dequeStack() {}
	virtual bool empty() const override { return arrayDeque<T>::empty(); }
	virtual int size() const override { return arrayDeque<T>::size(); }
	virtual T& top() override { return arrayDeque<T>::back(); }
	virtual void pop() override { arrayDeque<T>::pop_back(); }
	virtual void push(const T& theElement) override { arrayDeque<T>::push_back(theElement); }
};

#endif