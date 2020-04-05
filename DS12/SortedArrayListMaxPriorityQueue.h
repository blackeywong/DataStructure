#pragma once
#ifndef _SORTEDARRAYLISTMAXPRIORTYQUEUE_H
#define _SORTEDARRAYLISTMAXPRIORTYQUEUE_H

#include "MaxPriorityQueue.h"
#include "../DS10/sortedArrayList.h"

template<class T>
class SortedArrayListMaxPriorityQueue : virtual public MaxPriorityQueue<T>, private sortedArrayList<int, T> {
	template<class T> friend std::ostream& operator<<(std::ostream& out, const SortedArrayListMaxPriorityQueue<T>& salmpq);
public:
	SortedArrayListMaxPriorityQueue() :sortedArrayList<int, T>() {}
	virtual ~SortedArrayListMaxPriorityQueue() {}
	virtual bool empty() const override { return sortedArrayList<int, T>::empty(); }
	virtual int size() const override { return sortedArrayList<int, T>::size(); }
	virtual const T& top() override;
	virtual void pop() override;
	virtual void push(const T& theElement) override;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const SortedArrayListMaxPriorityQueue<T>& salmpq) {
	salmpq.sortedArrayList<int, T>::output(out);
	return out;
}

template<class T>
const T& SortedArrayListMaxPriorityQueue<T>::top() {
	if (empty())
		throw std::out_of_range("Empty queue");

	return sortedArrayList<int, T>::list[size()-1].second;
}

template<class T>
void SortedArrayListMaxPriorityQueue<T>::pop() {
	if(size() > 0)
		--sortedArrayList<int, T>::listSize;
}


template<class T>
void SortedArrayListMaxPriorityQueue<T>::push(const T& theElement) {
	sortedArrayList<int, T>::insert({ theElement.priority, theElement });
}

#endif