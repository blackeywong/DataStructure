#pragma once
#ifndef _STACKWITHARRAYLIST_H
#define _STACKWITHARRAYLIST_H

#include "../DS5/arraylist.h"
#include "stack.h"
//Exercise 10
template<class T>
class stackWithArrayList : public stack<T> {
public:
	stackWithArrayList<T>(int initialCapacity = 10) : list(initialCapacity) {}
	virtual bool empty() const override { return list.empty(); }
	virtual int size() const override { return list.size(); }

	virtual T& top() override {
		if (empty()) { throw OutOfBounds(); }

		return list.get(size() - 1);
	}

	virtual void pop() override {
		if (empty()) { throw OutOfBounds(); }

		list.erase(size() - 1);
	}

	virtual void push(const T& theElement) override {
		list.insert(size(), theElement);
	}
private:
	ArrayList<T> list;
};


#endif
