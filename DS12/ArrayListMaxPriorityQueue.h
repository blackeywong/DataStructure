#pragma once
#ifndef _ARRAYLISTMAXPRIORTYQUEUE_H
#define _ARRAYLISTMAXPRIORTYQUEUE_H

#include "MaxPriorityQueue.h"
#include "../DS5/arraylist.h"

template<class T>
class ArrayListMaxPriorityQueue : virtual public MaxPriorityQueue<T>, private ArrayList<T> {
	template<class T> friend std::ostream& operator<<(std::ostream& out, const ArrayListMaxPriorityQueue<T>& almpq);
public:
	ArrayListMaxPriorityQueue() :ArrayList<T>() { maxPriorityNumber = -1; }
	virtual ~ArrayListMaxPriorityQueue() {}
	virtual bool empty() const override { return ArrayList<T>::empty(); }
	virtual int size() const override { return ArrayList<T>::size(); }
	virtual const T& top() override;
	virtual void pop() override;
	virtual void push(const T& theElement) override;
private:
	void locateMaxPriority();

	int maxPriorityNumber;
};

template<class T> 
std::ostream& operator<<(std::ostream& out, const ArrayListMaxPriorityQueue<T>& almpq) {
	almpq.ArrayList<T>::output(out);
	return out;
}

template<class T>
const T& ArrayListMaxPriorityQueue<T>::top() {
	if (empty())
		throw std::out_of_range("Empty queue");

	locateMaxPriority();
	return ArrayList<T>::get(maxPriorityNumber);
}

template<class T>
void ArrayListMaxPriorityQueue<T>::pop() {
	if (maxPriorityNumber != 0) {
		ArrayList<T>::erase(maxPriorityNumber);
		maxPriorityNumber = -1;
	}
	else {
		locateMaxPriority();
		ArrayList<T>::erase(maxPriorityNumber);
	}
}


template<class T>
void ArrayListMaxPriorityQueue<T>::push(const T& theElement) { 
	ArrayList<T>::push_back(theElement); 
	if (maxPriorityNumber != -1 && ArrayList<T>::element[maxPriorityNumber].priority < theElement.priority) {
		maxPriorityNumber = size() - 1;
	}
}

template<class T>
void ArrayListMaxPriorityQueue<T>::locateMaxPriority() {
	if (maxPriorityNumber != -1)
		return;

	maxPriorityNumber = 0;
	int i = 1;
	for (; i < size(); ++i) {
		if (ArrayList<T>::element[maxPriorityNumber] < ArrayList<T>::element[i])
			maxPriorityNumber = i;
	}
}
#endif