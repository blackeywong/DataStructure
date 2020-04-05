#pragma once
#ifndef _EXTENDEDSTACK_H
#define _EXTENDEDSTACK_H
#include "stack.h"
//Exercise 7.1

template <class T>
class extendedStack: public virtual stack<T>{
public:
	virtual std::istream& input(std::istream& in) = 0;
	virtual std::string toString() const = 0;
	virtual void split(extendedStack<T>& st1, extendedStack<T>& st2) const = 0;
	virtual void merge(extendedStack<T>& st2) = 0;
};

#endif