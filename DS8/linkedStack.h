#pragma once
#ifndef _LINKEDSTACK_H
#define _LINKEDSTACK_H
#include "stack.h"
#include "../DS6/chainnode.h"
#include "../DS5/exceptions.h"

template<class T>
class linkedStack : virtual public stack<T> {
public:
	linkedStack() : stackTop(nullptr), stackSize(0){}
	~linkedStack() {
		while (stackTop) {
			ChainNode<T>* temp = stackTop;
			stackTop = stackTop->next;
			delete temp;
		}
	}
	virtual bool empty() const override{ return stackSize == 0; }
	virtual int size() const override { return stackSize; }
	virtual T& top() override {
		if (stackSize == 0)
			throw OutOfBounds();

		return stackTop->element;
	}
	virtual void pop() override {
		if (stackSize == 0)
			throw OutOfBounds();

		ChainNode<T>* temp = stackTop;
		stackTop = stackTop->next;
		delete temp;
		--stackSize;
	}
	virtual void push(const T& t) override {
		ChainNode<T>* newNode = new ChainNode<T>(t, stackTop);
		stackTop = newNode;
		++stackSize;
	}
	//Exercise 12
	void pushNode(ChainNode<T>* theNode) {
		theNode->next = stackTop;
		stackTop = theNode;
		++stackSize;
	}
	ChainNode<T>* popNode() {
		if (stackSize == 0)
			throw OutOfBounds();

		ChainNode<T>* temp = stackTop;
		stackTop = stackTop->next;
		return temp;
	}


protected:
	ChainNode<T>* stackTop;
	int stackSize;
};

#endif
