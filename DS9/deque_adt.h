#pragma once
#ifndef _DEQUE_ADT_H
#define _DEQUE_ADT_H

template<class T>
class deque_adt {
public:
	virtual ~deque_adt() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& front() = 0;
	virtual T& back() = 0;
	virtual void pop_front() = 0;
	virtual void pop_back() = 0;
	virtual void push_front(const T& theElement) = 0;
	virtual void push_back(const T& theElement) = 0;
};

#endif