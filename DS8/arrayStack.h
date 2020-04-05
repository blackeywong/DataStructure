#pragma once
#ifndef _ARRAYSTACK_H
#define _ARRAYSTACK_H
#include "stack.h"
#include "../DS5/exceptions.h"
#include "../DS5/changelength.h"

template<class T>
class arrayStack :virtual public stack<T> {
public:
	arrayStack(int initialCapacity = 10);
	virtual ~arrayStack() { delete[] stack; }
	virtual bool empty() const override { return stackTop == -1; }
	virtual int size() const override { return stackTop + 1; }
	virtual T& top() override {
		if (stackTop == -1)
			throw IllegalIndex("empty stack");
		return *(stack+stackTop); 
	}
	virtual void pop() override {
		if (stackTop == -1)
			throw IllegalIndex("empty stack");
		//return --stackTop;
		stack[stackTop--].~T();
		//Exercise 9.1
		if (stackTop + 1 < arrayLength/4 && arrayLength >= 4) {
			changeLength1D(stack, arrayLength, arrayLength / 2);
			arrayLength /= 2;
		}
	}
	virtual void push(const T& theElement) override {
		if (stackTop + 1 == arrayLength) {
			changeLength1D(stack, arrayLength, arrayLength * 2);
			arrayLength *= 2;
		}
		stack[++stackTop] = theElement;
	}
protected:
	int stackTop;
	int arrayLength;
	T* stack;
};

template<class T>
arrayStack<T>::arrayStack<T>(int initialCapcity) {
	if (initialCapcity <= 0)
		throw IllegalParameterValue("capcity should be > 0");

	stack = new T[initialCapcity];
	stackTop = -1;
	arrayLength = initialCapcity;
}

#endif