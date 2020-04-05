#pragma once
#ifndef _DERIVEDLINKEDSTACK_H
#define _DERIVEDLINKEDSTACK_H

#include "../DS6/chain.h"
#include "stack.h"

template<class T>
class derivedLinkedStack : private Chain<T>, public virtual stack<T> {
public:
	derivedLinkedStack<T>() : Chain<T>::Chain() {}
	virtual bool empty() const override { return Chain<T>::empty(); }
	virtual int size() const override { return Chain<T>::size(); }

	virtual T& top() override {
		if (empty()) { throw OutOfBounds(); }

		return Chain<T>::get(0);
	}

	virtual void pop() override {
		if (empty()) { throw OutOfBounds(); }

		Chain<T>::erase(0);
	}

	virtual void push(const T& theElement) override {
		Chain<T>::insert(0, theElement);
	}

};


#endif
