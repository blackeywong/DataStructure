#pragma once
#ifndef _DERIVEDARRAYSTACK_H
#define _DERIVEDARRAYSTACK_H

#include "../DS5/arraylist.h"
#include "stack.h"

template<class T>
class derivedArrayStack : private ArrayList<T>, public virtual stack<T> {
public:
	derivedArrayStack<T>(int initialCapacity = 10) : ArrayList<T>::ArrayList(initialCapacity) {}
	virtual bool empty() const override{ return ArrayList<T>::empty(); }
	virtual int size() const override { return ArrayList<T>::size(); }

	virtual T& top() override {
		if (empty()) { throw OutOfBounds(); }

		return ArrayList<T>::get(size()-1);
	}

	virtual void pop() override {
		if (empty()) { throw OutOfBounds(); }

		ArrayList<T>::erase(size() - 1);
	}

	virtual void push(const T& theElement) override {
		ArrayList<T>::insert(size(),theElement);
	}

};


#endif
