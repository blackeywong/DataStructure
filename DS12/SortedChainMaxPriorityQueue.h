#pragma once
#ifndef _SORTEDCHAINMAXPRIORTYQUEUE_H
#define _SORTEDCHAINMAXPRIORTYQUEUE_H

#include "MaxPriorityQueue.h"
#include "../DS6/chain.h"

template<class T>
class SortedChainMaxPriorityQueue : virtual public MaxPriorityQueue<T>, private Chain<T> {
	template<class T> friend std::ostream& operator<<(std::ostream& out, const SortedChainMaxPriorityQueue<T>& cmpq);
public:
	SortedChainMaxPriorityQueue() :Chain<T>() {}
	virtual ~SortedChainMaxPriorityQueue() {}
	virtual bool empty() const override { return Chain<T>::empty(); }
	virtual int size() const override { return Chain<T>::size(); }
	virtual const T& top() override;
	virtual void pop() override;
	virtual void push(const T& theElement) override;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const SortedChainMaxPriorityQueue<T>& cmpq) {
	cmpq.Chain<T>::output(out);
	return out;
}

template<class T>
const T& SortedChainMaxPriorityQueue<T>::top() {
	if (empty())
		throw std::out_of_range("Empty queue");

	return Chain<T>::firstNode->element;
}

template<class T>
void SortedChainMaxPriorityQueue<T>::pop() {
	if (size() > 0) {
		Chain<T>::firstNode = Chain<T>::firstNode->next;
		--Chain<T>::listSize;
	}
}


template<class T>
void SortedChainMaxPriorityQueue<T>::push(const T& theElement) {
	if (Chain<T>::firstNode == nullptr || Chain<T>::firstNode->element <= theElement) {
		ChainNode<T>* old = Chain<T>::firstNode;
		Chain<T>::firstNode = new ChainNode<T>(theElement, old);
	}
	else {
		ChainNode<T>* cur = Chain<T>::firstNode;
		ChainNode<T>* next = cur->next;
		while (next != nullptr && theElement < next->element) {
			cur = next;
			next = next->next;
		}
		cur->next = new ChainNode<T>(theElement, next);
	}
	++Chain<T>::listSize;
}

#endif