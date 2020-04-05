#pragma once
#ifndef _TWOSTACKS_H
#define _TWOSTACKS_H

#include "../DS5/exceptions.h"
#include <algorithm>

template<class T>
class twoStacks {
public:
	twoStacks(int initialCapacity = 10);
	~twoStacks() { delete[] stack; }
	bool empty1() const { return stackTop1 == -1; }
	bool empty2() const { return stackTop2 == arrayLength; }
	int size1() const { return stackTop1 + 1; }
	int size2() const { return arrayLength - stackTop2; }
	T& top1() {
		if (stackTop1 == -1)
			throw IllegalIndex("empty stack");
		return *(stack + stackTop1);
	}
	T& top2() {
		if (stackTop2 == arrayLength)
			throw IllegalIndex("empty stack");
		return *(stack + stackTop2);
	}
	void pop1() {
		if (stackTop1 == -1)
			throw IllegalIndex("empty stack");
		
		stack[stackTop1--].~T();
		if (size1() + size2() < arrayLength / 4) {
			decreaseLength();
		}
	}
	void pop2() {
		if (stackTop2 == arrayLength)
			throw IllegalIndex("empty stack");

		stack[stackTop2++].~T();
		if (size1() + size2() < arrayLength / 4) {
			decreaseLength();
		}
	}
	void push1(const T& theElement) {
		if (size1() + size2() == arrayLength) {
			increaseLength();
		}
		stack[++stackTop1] = theElement;
	}
	void push2(const T& theElement) {
		if (size1() + size2() == arrayLength) {
			increaseLength();
		}
		stack[--stackTop2] = theElement;
	}
private:
	void decreaseLength() {
		int sz2 = size2();
		changeLength(false);
		arrayLength /= 2;
		stackTop2 = arrayLength - sz2;
	}
	void increaseLength() {
		int sz2 = size2();
		changeLength(true);
		arrayLength *= 2;
		stackTop2 = arrayLength - sz2;
	}

	void changeLength(bool bigger) {
		int sz1 = size1();
		int sz2 = size2();
		int newLength = arrayLength / 2;
		if(bigger)
			newLength = arrayLength * 2;

		T* temp = new T[newLength];
		
		std::copy(stack, stack + sz1, temp);
		std::copy_backward(stack + arrayLength - sz2, stack+arrayLength, temp + newLength);
		delete[]stack;
		stack = temp;
	}

	int stackTop1, stackTop2;
	int arrayLength;
	T* stack;
};

template<class T>
twoStacks<T>::twoStacks<T>(int initialCapcity) {
	if (initialCapcity <= 0)
		throw IllegalParameterValue("capcity should be > 0");

	stack = new T[initialCapcity];
	stackTop1 = -1;
	stackTop2 = initialCapcity;
	arrayLength = initialCapcity;
}

#endif