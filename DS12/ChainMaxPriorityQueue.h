#pragma once
#ifndef _CHAINMAXPRIORTYQUEUE_H
#define _CHAINMAXPRIORTYQUEUE_H

#include "MaxPriorityQueue.h"
#include "../DS6/chain.h"

template<class T>
class ChainMaxPriorityQueue : virtual public MaxPriorityQueue<T>, private Chain<T> {
	template<class T> friend std::ostream& operator<<(std::ostream& out, const ChainMaxPriorityQueue<T>& cmpq);
public:
	ChainMaxPriorityQueue() :Chain<T>() {}
	virtual ~ChainMaxPriorityQueue() {}
	virtual bool empty() const override { return Chain<T>::empty(); }
	virtual int size() const override { return Chain<T>::size(); }
	virtual const T& top() override;
	virtual void pop() override;
	virtual void push(const T& theElement) override;
private:
	ChainNode<T>* locateMaxPriority(int& index);
};

template<class T>
std::ostream& operator<<(std::ostream& out, const ChainMaxPriorityQueue<T>& cmpq) {
	cmpq.Chain<T>::output(out);
	return out;
}

template<class T>
const T& ChainMaxPriorityQueue<T>::top() {
	if (empty())
		throw std::out_of_range("Empty queue");

	int index;
	ChainNode<T>* node = locateMaxPriority(index);
	return node->element;
}

template<class T>
void ChainMaxPriorityQueue<T>::pop() {
	int index;
	locateMaxPriority(index);
	Chain<T>::erase(index);
}


template<class T>
void ChainMaxPriorityQueue<T>::push(const T& theElement) {
	Chain<T>::insert(0, theElement);
}

template<class T>
ChainNode<T>* ChainMaxPriorityQueue<T>::locateMaxPriority(int& index) {
	index = 0;
	ChainNode<T>* maxNode = Chain<T>::firstNode;
	ChainNode<T>* cur = maxNode;
	ChainNode<T>* next = cur->next;
	int i = 1;
	for (; i < size(); ++i) {
		if (cur->element < next->element) {
			index = i;
			maxNode = next;
		}
		cur = next;
		next = next->next;
	}
	return maxNode;
}

#endif